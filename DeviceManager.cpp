
#include <chrono>

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "logger.h"
#include "DeviceManager.h"
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
                    break;
                }

                if (events[i].events & (EPOLLERR | EPOLLHUP))
                {
                    break;
                }

                if (events[i].events & EPOLLIN)
                {
                    int olen = 0;
                    static uint8_t recvBuff[1024 * 30];
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

bool DeviceManager::openDevice()
{
    int fd = open(mDevice.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd < 0)
        return false;

    mHandle = fd;
    startPooling();
    return true;
}

bool DeviceManager::closeDevice()
{
    /* remove all the ovservers */
    for (auto o : mObservers)
    {
        o->update(nullptr);
    }

    for (auto iter = mObservers.begin();
         iter < mObservers.end(); iter++)
    {
        delete *iter;
    }
    mObservers.clear();
    stopPooling();
    return true;
}

bool DeviceManager::sendAsync(void *data, int len)
{
    std::lock_guard<std::mutex> _lk(mRWLock);

    if (!mReady)
        return false;

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
    {
        return false;
    }

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
    Argument arg = {type, p};

    if (type == RESPONSE_UNSOLICITED)
    {
        for (auto o : mObservers)
        {
            o->update(reinterpret_cast<void *>(&arg));
        }
    }
    else if (type == RESPONSE_SOLICITED)
    {
        int requestid = p.readInt();
        for (auto o : mObservers)
        {
            if (o->get_requestid() == requestid)
                o->update(reinterpret_cast<void *>(&arg));
        }
    }
}
