#include <thread>
#include <future>

#include "ISubjectObserver.h"

class Parcel;
typedef struct
{
    /* solicited or unsolicited message */
    int type;
    Parcel &parcel;
} Argument;

class DeviceManager final : public ISubject
{
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;

private:
    std::mutex mRWLock;
    std::mutex mListLock;
    std::string mDevice;
    std::future<int> mFuture;
    std::thread::id mPollID;
    bool mQuitFlag;
    bool mReady;
    int mHandle;

public:
    explicit DeviceManager(const char *d);

    ~DeviceManager();

    std::string device();

    bool isReady();

    bool openDevice();

    bool closeDevice();

    bool sendAsync(const void *data, int len);

    int startPooling();

    int stopPooling();

    friend void poolRead(DeviceManager *args);

private:
    bool recvAsync(void *data, int len, int *olen);

    void processResponse(void *data, size_t len);
};
