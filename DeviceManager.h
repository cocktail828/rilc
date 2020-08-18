#ifndef __DEVICEMANAGER
#define __DEVICEMANAGER

#include <thread>
#include <future>

#include "ISubjectObserver.h"

#define MAX_RILD_DATA_SIZE (8 * 1024)
class DeviceManager : public ISubject
{
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;

private:
    std::mutex mRWLock;
    std::future<int> mPollingFuture;
    std::string mDevice;
    int mPollingHandle;
    bool mQuitFlag;
    bool mReady;

public:
    explicit DeviceManager(const char *d);

    ~DeviceManager();

    std::string device();

    bool isReady();

    bool openDevice();

    bool closeDevice();

    int sendAsync(const void *data, int len);

    int recvAsync(void *data, int len, int *olen);

    int startPolling();

    int stopPolling();

    friend void pollingRead(DeviceManager *args);

private:
    void processResponse(void *data, size_t len);
};

#endif //__DEVICEMANAGER
