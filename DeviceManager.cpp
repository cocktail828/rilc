
#include <chrono>

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <linux/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <termio.h>
#include <linux/usbdevice_fs.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 20)
#include <linux/usb/ch9.h>
#else
#include <linux/usb_ch9.h>
#endif

#include "logger.h"
#include "DeviceManager.h"
#include "ril_request.h"
#include "parcel/parcel.h"

static usb_handle handle;

void poolRead(DeviceManager *args)
{
    int epfd = epoll_create(10);

    epoll_event event;
    event.data.fd = args->mHandle;
    event.events = EPOLLIN | EPOLLRDHUP;
    epoll_ctl(epfd, EPOLL_CTL_ADD, args->mHandle, &event);

    std::thread::id mPollID = std::this_thread::get_id();

    LOGI << "polling thread start polling, thread id " << mPollID << ENDL;
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
                    goto quit_polling;
                }

                if (events[i].events & (EPOLLERR | EPOLLHUP))
                {
                    LOGE << "epoll error, event = " << events[i].events << ENDL;
                    goto quit_polling;
                }

                if (events[i].events & EPOLLIN)
                {
#define MAX_RD_SIZE (8 * 1024)
                    int olen = 0;
                    static uint8_t recvBuff[MAX_RD_SIZE]; // RIL message has max size of 8K
                    int length = 0;

                    // read message length
                    if (args->recvAsync(&length, 4, &olen))
                    {
                        length = be32toh(length);
                        LOGD << "response length = " << length << ENDL;
                        if (length > MAX_RD_SIZE)
                        {
                            LOGE << "error, message lenth too long" << ENDL;
                            length = MAX_RD_SIZE - 1;
                        }
                        // read message body
                        if (args->recvAsync(recvBuff, length, &olen))
                            args->processResponse(recvBuff, olen);
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
    LOGW << "polling thread quit polling" << ENDL;
    args->mReady = false;
}

DeviceManager::DeviceManager(const char *d)
    : mDevice(d), mQuitFlag(false),
      mReady(false), mHandle(0)
{
}

DeviceManager::~DeviceManager()
{
    mHandle = 0;
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

int open_usbfs(const char *d)
{
    int fd = open(d, O_RDWR);
    if (fd < 0)
    {
        LOGE << "fail to open usbfs " << d << ENDL;
        return fd;
    }

    int ifc = 6;
    if (ioctl(fd, USBDEVFS_CLAIMINTERFACE, &ifc))
    {
        LOGE << "usbfs fail to claim interface: " << ifc << ENDL;
        close(fd);
        return 0;
    }
    handle.desc = fd;
    handle.ep_in = 0x87;
    handle.ep_out = 0x06;
    handle.ep_in_maxpkt = 1024;
    handle.ep_out_maxpkt = 1024;
    strcpy(handle.fname, d);

    return fd;
}

int usb_close(usb_handle *h)
{
    int fd;
    int ifc = 6;

    fd = handle.desc;
    handle.desc = -1;
    if (fd >= 0)
    {
        ioctl(fd, USBDEVFS_RELEASEINTERFACE, &ifc);
        close(fd);
        fd = -1;
    }

    return 0;
}

#define MAX_USBFS_BULK_SIZE (16 * 1024)
int usb_write(const void *_data, int len)
{
    unsigned char *data = (unsigned char *)_data;
    unsigned count = 0;
    struct usbdevfs_bulktransfer bulk;
    int n;

    if (handle.ep_out == 0 || handle.desc == -1)
    {
        return -1;
    }

    do
    {
        int xfer;
        xfer = (len > MAX_USBFS_BULK_SIZE) ? MAX_USBFS_BULK_SIZE : len;

        bulk.ep = handle.ep_out;
        bulk.len = xfer;
        bulk.data = data;
        bulk.timeout = 0;

        n = ioctl(handle.desc, USBDEVFS_BULK, &bulk);
        if (n != xfer)
        {
            LOGFE("ERROR: n = %d, xfer = %d, errno = %d (%s)\n", n, xfer, errno, strerror(errno));
            return -1;
        }

        count += xfer;
        len -= xfer;
        data += xfer;
    } while (len > 0);

    return count;
}

#define MAX_RETRIES 5
int usb_read(void *_data, int len)
{
    unsigned char *data = (unsigned char *)_data;
    unsigned count = 0;
    struct usbdevfs_bulktransfer bulk;
    int n, retry;

    if (handle.ep_in == 0 || handle.desc == -1)
    {
        return -1;
    }

    while (len > 0)
    {
        int xfer = (len > MAX_USBFS_BULK_SIZE) ? MAX_USBFS_BULK_SIZE : len;

        bulk.ep = handle.ep_in;
        bulk.len = xfer;
        bulk.data = data;
        bulk.timeout = 0;
        retry = 0;

        do
        {
            LOGFI("[ usb read %d fd = %d], fname=%s\n", xfer, handle.desc, handle.fname);
            n = ioctl(handle.desc, USBDEVFS_BULK, &bulk);
            LOGFI("[ usb read %d ] = %d, fname=%s, Retry %d \n", xfer, n, handle.fname, retry);

            if (n < 0)
            {
                LOGFE("ERROR: n = %d, errno = %d (%s)\n", n, errno, strerror(errno));
                if (++retry > MAX_RETRIES)
                    return -1;
                sleep(1);
            }
        } while (n < 0);

        count += n;
        len -= n;
        data += n;

        if (n < xfer)
        {
            break;
        }
    }

    return count;
}

static int open_tty(const char *d)
{
    int fd = open(d, O_RDWR | O_NOCTTY | O_NONBLOCK);
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
    else if (mDevice.find("/dev/bus/usb") != std::string::npos)
        fd = open_usbfs(mDevice.c_str());
    else
        fd = open_tty(mDevice.c_str());

    if (fd < 0)
    {
        LOGE << "open " << mDevice << " failed" << ENDL;
        return false;
    }
    LOGI << "open " << mDevice << " successfully, fd = " << fd << ENDL;

    mHandle = fd;
    startPooling();
    return true;
}

bool DeviceManager::closeDevice()
{
    LOGD << "closeDevice fd = " << mHandle << ENDL;
    /* close file descriper first, so polling thread will quit */
    close(mHandle);
    mHandle = 0;

    LOGD << "closeDevice successfully" << ENDL;
    detachAll();
    stopPooling();
    return true;
}

static void dump_msg(const void *data, int len, const char *direction)
{
    static char _msg[16 * 1024];
    memset(_msg, 0, sizeof(_msg));

    const uint8_t *ptr = reinterpret_cast<const uint8_t *>(data);
    for (int i = 0; i < len; i++)
        snprintf(_msg + strlen(_msg), 8 * 1024, "%02x ", ptr[i]);

    LOGD << "(" + std::to_string(len) + "): " + direction + " " << _msg << ENDL;
}

bool DeviceManager::sendAsync(const void *data, int len)
{
    std::lock_guard<std::mutex> _lk(mRWLock);

    if (!mReady)
        return false;

    dump_msg(data, len, ">>>>>>");

    // ssize_t ret = write(mHandle, data, len);
    int ret = usb_write(data, len);
    if (ret < 0)
    {
        LOGE << "send message failed" << ENDL;
        return false;
    }
    return true;
}

bool DeviceManager::recvAsync(void *data, int len, int *olen)
{
    std::lock_guard<std::mutex> _lk(mRWLock);

    if (olen)
        *olen = 0;
    if (!mReady)
        return false;

    // ssize_t ret = read(mHandle, data, len);
    int ret = usb_read(data, len);
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
        LOGI << "stopPooling try time = " << wait << ENDL;
        wait++;
    }
    return true;
}

void DeviceManager::processResponse(void *data, size_t len)
{
    Parcel p;

    if (len == 0)
    {
        LOGD << "response should not has length of zero" << ENDL;
        return;
    }

    p.setData(reinterpret_cast<uint8_t *>(data), len);

    int type = p.readInt();

    // process unsolicited myself */
    if (type == RESPONSE_UNSOLICITED)
    {
        LOGD << "process unsocilited message" << ENDL;
        RILREQUEST::processUnsolicited(p);
    }
    else if (type == RESPONSE_SOLICITED)
    {
        LOGD << "process socilited message" << ENDL;
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
    else
    {
        LOGE << "oops, unknow the message type!!! type = " << type << ENDL;
        LOGE << "Malformation message!!!" << ENDL;
    }
}