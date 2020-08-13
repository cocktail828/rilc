#ifndef __RIL_REQUEST
#define __RIL_REQUEST

#include <mutex>

#include "ISubjectObserver.h"
#include "DeviceManager.h"
#include "parcel/parcel.h"
#include "ril_response.h"

#define RIL_MAX_BUFSIZE (1024 * 8)
class RilRequest final : public IObserver
{
private:
    /* class variables */
    static DeviceManager *mDeviceMgr;
    static int mGlobalRequestId;
    static bool mReady;

public:
    static std::mutex mGlobalLock;
    static const int RIL_MAX_COMMAND_BYTES = (8 * 1024);
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;

private:
    /* instance variables */
    int mRequestId;
    int mCommandId;

public:
    static RilRequest &instance();

    static RilRequest *obtain(int cid, RilResponse *);

    static bool init(const char *device);

    static bool uninit();

    static bool isReady();

    static void resetRequest();

    static void send(RilRequest *);

public:
    explicit RilRequest();

    ~RilRequest();

    /* When get some message from serial, this function will be called */
    void update(void *data);

    std::string serialString();

    std::string requestToString();

    int get_requestid();

    int get_commandid();

private:
    void processUnsolicited(Parcel &);

    void processSolicited(Parcel &);

    const void *responseVoid(Parcel &p);

    std::vector<int> responseInts(Parcel &p);

    const void *responseString(Parcel &p);

    std::vector<std::string> responseStrings(Parcel &p);
};

typedef RilRequest RILREQUEST;

#endif //__RIL_REQUEST
