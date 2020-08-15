
#include <chrono>

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <linux/un.h>
#include <fcntl.h>
#include <unistd.h>

#include "logger.h"
#include "DeviceManager.h"
#include "ril_request.h"
#include "parcel/parcel.h"

void poolRead(DeviceManager *args)
{
    int epfd = epoll_create(10);

    epoll_event event;
    event.data.fd = args->mHandle;
    event.events = EPOLLIN | EPOLLRDHUP;
    epoll_ctl(epfd, EPOLL_CTL_ADD, args->mHandle, &event);

    args->mPollID = std::this_thread::get_id();

    LOGI << "polling thread start polling, thread id " << args->mPollID << ENDL;
    epoll_event events[10];
    do
    {
        args->mReady = true;
        if (args->mQuitFlag)
            break;

        int num = epoll_wait(epfd, events, 10, 3000);
        if (num < 0)
            break;
        else if (num == 0)
            continue;
        else
        {
            for (int i = 0; i < num; i++)
            {
                // serial closed?
                if (events[i].events & EPOLLRDHUP)
                {
                    LOGE << "peer close device" << ENDL;
                    break;
                }

                if (events[i].events & (EPOLLERR | EPOLLHUP))
                {
                    LOGE << "epoll error, event = " << events[i].events << ENDL;
                    break;
                }

                if (events[i].events & EPOLLIN)
                {
                    LOGD << "epoll get in event" << ENDL;
                    int olen = 0;
                    static uint8_t recvBuff[1024 * 8]; // RIL message has max size of 8K
                    size_t len = args->recvAsync(recvBuff, sizeof(recvBuff), &olen);
                    args->processResponse(recvBuff, len);
                }
            }
        }
    } while (1);
    LOGW << "polling thread quit polling" << ENDL;
    args->mReady = false;
}

DeviceManager::DeviceManager(const char *d)
    : mDevice(d), mPollID(0), mQuitFlag(false),
      mReady(false), mHandle(0)
{
}

DeviceManager::~DeviceManager()
{
    close(mHandle);
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
    return open(d, O_RDWR | O_NOCTTY | O_NONBLOCK);
}

static int open_unix_sock(const char *d)
{
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0)
        return -1;

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(sockaddr));
    addr.sun_family = AF_UNIX;

    /* do not generate socket file */
    memcpy(addr.sun_path + 1, d, strlen(d));
    socklen_t slen = offsetof(sockaddr_un, sun_path) + strlen(d) + 1;
    if (connect(sockfd, (struct sockaddr *)&addr, slen) < 0)
        return -1;

    int soflag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &soflag, sizeof(soflag));
    return sockfd;
}

bool DeviceManager::openDevice()
{
    int fd;
    if (mDevice.find("/dev") != std::string::npos)
        fd = open_tty(mDevice.c_str());
    else
        fd = open_unix_sock(mDevice.c_str());

    if (fd < 0)
    {
        LOGE << "open " << mDevice << " failed" << ENDL;
        return false;
    }

    mHandle = fd;
    startPooling();
    return true;
}

bool DeviceManager::closeDevice()
{
    /* close file descriper first, so polling thread will quit */
    close(mHandle);

    detachAll();
    stopPooling();
    return true;
}

static void dump_msg(const void *data, int len)
{
    static char _msg[16 * 1024];
    memset(_msg, 0, sizeof(_msg));

    const uint8_t *ptr = reinterpret_cast<const uint8_t *>(data);
    for (int i = 0; i < len; i++)
        snprintf(_msg + strlen(_msg), 8 * 1024, "%02x ", ptr[i]);

    LOGD << "dump_msg: " << _msg << ENDL;
}

bool DeviceManager::sendAsync(const void *data, int len)
{
    std::lock_guard<std::mutex> _lk(mRWLock);

    if (!mReady)
        return false;

    dump_msg(data, len);
    ssize_t ret = write(mHandle, data, len);
    if (ret < 0)
    {
        return false;
    }
    return true;
}

bool DeviceManager::recvAsync(void *data, int len, int *olen)
{
    std::lock_guard<std::mutex> _lk(mRWLock);

    if (!mReady)
        return false;

    ssize_t ret = read(mHandle, data, len);
    if (ret < 0)
        return false;

    dump_msg(data, *olen);
    if (olen)
        *olen = ret;
    return true;
}

int DeviceManager::startPooling()
{
    // std::thread pooling(poolRead, this);
    // pooling.detach();
    // return true;

    mFuture = std::async(std::launch::async, [&] {
        poolRead(this);
        mReady = false;
        return 0;
    });
    return true;
}

int DeviceManager::stopPooling()
{
    mQuitFlag = true;
    // TODO;

    const int max_wait = 10;
    int wait = 0;
    while (wait < max_wait)
    {
        auto status = mFuture.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::ready)
        {
            auto ret = mFuture.get();
            LOGI << "polling thread exit with code " << ret << ENDL;
            break;
        }
        wait++;
    }
    return true;
}

void DeviceManager::processResponse(void *data, size_t len)
{
    Parcel p;

    p.setData(reinterpret_cast<uint8_t *>(data), len);
    int type = p.readInt();

    // process unsolicited myself */
    if (type == RESPONSE_UNSOLICITED)
    {
        RILREQUEST::processUnsolicited(p);
    }
    else if (type == RESPONSE_SOLICITED)
    {
        /* find the observer and notice him */
        int requestid = p.readInt();
        for (auto o : mObservers)
        {
            if (o->get_requestid() == requestid)
            {
                o->update(p);
                detach(o);
            }
        }
    }
}
