
#include <chrono>

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <termio.h>
#include <endian.h>

#include "logger.h"
#include "DeviceManager.h"
#include "ril_request.h"
#include "parcel/parcel.h"

#define MAX_TRY 5
void pollingRead(DeviceManager *args)
{
    int epfd = epoll_create(10);

    epoll_event event;
    event.data.fd = args->mPollingHandle;
    event.events = EPOLLIN | EPOLLRDHUP;
    epoll_ctl(epfd, EPOLL_CTL_ADD, args->mPollingHandle, &event);

    std::thread::id mPollID = std::this_thread::get_id();

    LOGI << "polling thread start polling, thread id " << mPollID << ENDL;
    epoll_event events[10];
    do
    {
        args->mReady = true;
        int num = epoll_wait(epfd, events, 10, 2000);
        if (num < 0)
        {
            LOGE << "epoll_wait get error: " << strerror(errno) << ENDL;
            goto quit_polling;
        }
        else if (num == 0)
        {
            if (args->mQuitFlag)
            {
                goto quit_polling;
            }
        }
        else
        {
            for (int i = 0; i < num; i++)
            {
                // serial closed?
                if (events[i].events & EPOLLRDHUP)
                {
                    LOGE << "peer close device" << ENDL;
                    goto quit_polling;
                }

                if (events[i].events & (EPOLLERR | EPOLLHUP))
                {
                    LOGE << "epoll error, event = " << events[i].events << ENDL;
                    goto quit_polling;
                }

                if (events[i].events & EPOLLIN)
                {
                    int olen = 0;
                    static uint8_t recvBuff[MAX_RILD_DATA_SIZE]; // RIL message has max size of 8K
                    int length = 0;

                    // read message length
                    if (args->recvAsync(&length, 4, &olen))
                    {
                        length = be32toh(length);
                        LOGD << "response length = " << length << ENDL;

                        if (length > MAX_RILD_DATA_SIZE)
                        {
                            LOGE << "error, message lenth too long" << ENDL;
                            length = MAX_RILD_DATA_SIZE - 1;
                        }

                        // read message body
                        int expect_len = length;
                        int read_len = 0;
                        int try_time = 0;
                        const int max_try = 10;
                        do
                        {
                            if (args->recvAsync((uint8_t *)recvBuff + read_len, length, &olen) && olen > 0)
                            {
                                expect_len -= olen;
                                read_len += olen;
                            }
                            else
                            {
                                std::this_thread::sleep_for(std::chrono::microseconds(3000));
                                try_time++;
                            }

                            if (expect_len == 0 || try_time == max_try)
                                break;
                        } while (1);

                        if (expect_len == 0)
                            args->processResponse(recvBuff, length);
                        else
                            LOGE << "read response data failed" << ENDL;
                    }
                    else
                        LOGE << "read response data failed" << ENDL;
                }
            }
        }
    } while (1);

quit_polling:
    epoll_ctl(epfd, EPOLL_CTL_DEL, args->mPollingHandle, &event);
    close(epfd);
    close(args->mPollingHandle);
    LOGW << "polling thread quit polling" << ENDL;
    args->mReady = false;
    args->processResponse(nullptr, 0);
}

DeviceManager::DeviceManager(const char *d)
    : mDevice(d), mPollingHandle(0), mQuitFlag(false), mReady(false)
{
}

DeviceManager::~DeviceManager()
{
    mPollingHandle = 0;
    mReady = false;
}

std::string DeviceManager::device()
{
    std::string device_(mDevice);
    return device_;
}

bool DeviceManager::isReady()
{
    return mReady;
}

static int open_tty(const char *d)
{
    int fd = open(d, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd < 0)
    {
        LOGE << "fail to open " << d << " for " << strerror(errno) << ENDL;
        return fd;
    }

    struct termios tio;
    struct termios settings;
    int retval;
    memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL; // 8n1, see termios.h for more information
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 5;
    cfsetospeed(&tio, B115200); // 115200 baud
    cfsetispeed(&tio, B115200); // 115200 baud
    tcsetattr(fd, TCSANOW, &tio);
    retval = tcgetattr(fd, &settings);
    if (-1 == retval)
    {
        LOGE << "setUart error" << ENDL;
    }
    cfmakeraw(&settings);
    settings.c_cflag |= CREAD | CLOCAL;
    tcflush(fd, TCIOFLUSH);
    tcsetattr(fd, TCSANOW, &settings);

    return fd;
}

static int open_unix_sock(const char *d)
{
    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sockfd < 0)
        return -1;

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(sockaddr));
    addr.sun_family = AF_LOCAL;

    /* do not generate socket file */
    // memcpy(addr.sun_path + 1, d, strlen(d));
    // socklen_t slen = offsetof(sockaddr_un, sun_path) + strlen(d) + 1;
    memcpy(addr.sun_path, d, strlen(d));
    socklen_t slen = offsetof(sockaddr_un, sun_path) + strlen(d);
    if (connect(sockfd, (struct sockaddr *)&addr, slen) < 0)
        return -1;

    int soflag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &soflag, sizeof(soflag));
    return sockfd;
}

bool DeviceManager::openDevice()
{
    int fd;
    if (mDevice.find("socket") != std::string::npos)
        fd = open_unix_sock(mDevice.c_str());
    else
        fd = open_tty(mDevice.c_str());

    if (fd < 0)
    {
        LOGE << "open " << mDevice << " failed" << ENDL;
        return false;
    }
    LOGI << "open " << mDevice << " successfully, fd = " << fd << ENDL;

    mPollingHandle = fd;
    startPolling();
    return true;
}

bool DeviceManager::closeDevice()
{
    LOGD << "closeDevice fd = " << mPollingHandle << ENDL;
    /* close file descriper first, for we do not care the follwing messages */
    close(mPollingHandle);
    /* set quit flag so polling thread will quit */
    mQuitFlag = true;

    LOGD << "closeDevice successfully" << ENDL;
    detachAll();
    stopPolling();
    return true;
}

static void dump_msg(const void *data, int len, const char *direction)
{
    // static char _msg[16 * 1024];
    // memset(_msg, 0, sizeof(_msg));

    // const uint8_t *ptr = reinterpret_cast<const uint8_t *>(data);
    // for (int i = 0; i < len; i++)
    //     snprintf(_msg + strlen(_msg), 8 * 1024, "%02x ", ptr[i]);

    // LOGD << "(" + std::to_string(len) + "): " + direction + " " << _msg << ENDL;
}

int DeviceManager::sendAsync(const void *data, int len)
{
    std::lock_guard<std::mutex> _lk(mRWLock);

    if (!mReady)
        return false;

    dump_msg(data, len, ">>>>>>");

    ssize_t ret;
    do
    {
        ret = write(mPollingHandle, data, len);
    } while (ret < 0 && (errno == EINTR || errno == EAGAIN));

    if (ret < 0)
    {
        LOGE << "send message failed" << ENDL;
        return false;
    }
    return true;
}

int DeviceManager::recvAsync(void *data, int len, int *olen)
{
    std::lock_guard<std::mutex> _lk(mRWLock);

    if (olen)
        *olen = 0;
    if (!mReady)
        return false;

    ssize_t ret;
    do
    {
        ret = read(mPollingHandle, data, len);
    } while (ret < 0 && (errno == EINTR || errno == EAGAIN));

    if (ret < 0)
    {
        LOGE << "recv message failed" << ENDL;
        return false;
    }

    dump_msg(data, ret, "<<<<<<");
    if (olen)
        *olen = ret;
    return true;
}

int DeviceManager::startPolling()
{
    mPollingFuture = std::async(std::launch::async, [&] {
        pollingRead(this);
        mReady = false;
        return 0;
    });
    return true;
}

int DeviceManager::stopPolling()
{
    const int max_wait = 10;
    int wait = 0;
    while (wait < max_wait)
    {
        auto status = mPollingFuture.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::ready)
        {
            auto ret = mPollingFuture.get();
            LOGI << "polling thread exit with code " << ret << ENDL;
            break;
        }
        LOGI << "stop pooling try time = " << wait << ENDL;
        wait++;
    }
    LOGI << "polling thread exit " << ENDL;
    return true;
}

void DeviceManager::processResponse(void *data, size_t len)
{
    Parcel p;

    if (len == 0)
    {
        LOGD << "polling thread may quit" << ENDL;
        mQuitFlag = true;
        return;
    }

    p.setData(reinterpret_cast<uint8_t *>(data), len);
    int type = p.readInt32();
    if (type == RESPONSE_UNSOLICITED)
    {
        LOGD << "process unsocilited message" << ENDL;
        RILREQUEST::processUnsolicited(p);
    }
    else if (type == RESPONSE_SOLICITED)
    {
        LOGD << "process socilited message" << ENDL;
        /* find the observer and notice him */
        int rid = p.readInt32();
        notify(rid, p);
    }
    else
    {
        LOGE << "oops, unknow the message type!!! type = " << type << ENDL;
        LOGE << "Malformation message!!!" << ENDL;
    }
}