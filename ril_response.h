#ifndef __RIL_RESPONSE
#define __RIL_RESPONSE

#include <string>
#include <vector>

#include "ril.h"
#include "parcel/parcel.h"

typedef enum
{
    RESP_STR,     /* response is string */
    RESP_STR_ARR, /* response is string array */
    RESP_INT,     /* response is int */
    RESP_INT_ARR, /* response is int array */
    RESP_RAWDATA, /* response raw binary data */
    RESP_VOID     /* no response */
} response_type_e;

class RilResponse
{
private:
    std::vector<int> mRespVecInt;
    std::vector<std::string> mRespVecString;
    std::string mRespString;
    uint8_t *mRawdata; /* raw binary data */
    size_t mRawlen;    /* data length */
    response_type_e mRespType;

    /* response info */
    bool mIsURC;
    bool mResponseID;

public:
    RilResponse() : mRawdata(nullptr), mRawlen(0), mRespType(RESP_VOID),
                    mIsURC(false), mResponseID(0)
    {
    }

    ~RilResponse()
    {
        mRawlen = 0;
        if (mRawdata)
            delete mRawdata;
    }

    void setResponseID(int id);

    void setResponseURCInfo(bool isurc);

    /* common use functions */
    std::string responseToString(int respid);

    void responseVoid(Parcel &p);

    void responseInts(Parcel &p);

    void responseString(Parcel &p);

    void responseStrings(Parcel &p);

    /* private process functions */
    void responseIccCardStatus(Parcel &);

    void responseCallList(Parcel &);

    void responseSignalStrength(Parcel &);

    void responseSMS(Parcel &);

    void responseSetupDataCall(Parcel &);

    void responseICC_IO(Parcel &);

    void responseCallForward(Parcel &);

    void responseOperatorInfos(Parcel &);

    void responseDataCallList(Parcel &);

    void responseRaw(Parcel &);

    void responseGetPreferredNetworkType(Parcel &);

    void responseCellList(Parcel &);

    void responseGmsBroadcastConfig(Parcel &);

    void responseCdmaBroadcastConfig(Parcel &);

    void responseSuppServiceNotification(Parcel &);

    void responseCallRing(Parcel &);

    void responseCdmaSms(Parcel &);

    void responseCdmaCallWaiting(Parcel &);

    void responseCdmaInformationRecord(Parcel &);
};

#endif //__RIL_RESPONSE
