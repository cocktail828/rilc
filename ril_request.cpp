#include <assert.h>
#include <vector>

#include "ril_request.h"
#include "logger.h"
#include "ril.h"

DeviceManager *RilRequest::mDeviceMgr = nullptr;
int RilRequest::mGlobalRequestId = 0;
;
bool RilRequest::mReady = false;
std::mutex RilRequest::mGlobalLock;

RilRequest *RilRequest::obtain(int cid, RilResponse *result)
{
    RilRequest *rr = new RilRequest();
    return rr;
}

RilRequest &RilRequest::instance()
{
    static RilRequest instance_;
    return instance_;
}

bool RilRequest::init(const char *device)
{
    assert(device != nullptr);

    mGlobalRequestId = 0;
    if (!mDeviceMgr)
    {
        mDeviceMgr = new (std::nothrow) DeviceManager(device);
        if (!mDeviceMgr)
            return false;
    }

    return mDeviceMgr->openDevice();
}

bool RilRequest::uninit()
{
    if (mDeviceMgr)
    {
        if (mDeviceMgr->closeDevice())
        {
            delete mDeviceMgr;
            return true;
        }
    }
    return false;
}

bool RilRequest::isReady()
{
    mReady = mDeviceMgr && mDeviceMgr->isReady();
    return mReady;
}

void RilRequest::resetRequest()
{
    std::lock_guard<std::mutex> _lk(mGlobalLock);
    mGlobalRequestId = 0;
}

void RilRequest::send(RilRequest *)
{
    if (mDeviceMgr && mDeviceMgr->isReady())
    {
        mDeviceMgr->sendAsync(reinterpret_cast<const void *>(mParcel.data()),
                              mParcel.dataSize());
    }
}

RilRequest::RilRequest()
{
}

RilRequest::~RilRequest()
{
}

/* When get some message from requestid, this function will be called */
void RilRequest::update(void *_arg)
{
    /* oops! device manager is destroyed */
    if (!_arg)
    {
        LOGW << "null response get, device connect may be broken" << ENDL;
        mCond.notify_one();
    }

    Argument *arg = reinterpret_cast<Argument *>(_arg);
    if (arg->type == RESPONSE_SOLICITED)
    {
        processSolicited(arg->parcel);
    }
    else if (arg->type == RESPONSE_UNSOLICITED)
    {
        processUnsolicited(arg->parcel);
    }

    return;
}

std::string RilRequest::serialString()
{
    return "";
}

int RilRequest::get_requestid()
{
    return mRequestId;
}

int RilRequest::get_commandid()
{
    return mCommandId;
}

std::string RilRequest::requestToString()
{
    switch (mRequestId)
    {
    case RIL_REQUEST_GET_SIM_STATUS:
        return "GET_SIM_STATUS";
    case RIL_REQUEST_ENTER_SIM_PIN:
        return "ENTER_SIM_PIN";
    case RIL_REQUEST_ENTER_SIM_PUK:
        return "ENTER_SIM_PUK";
    case RIL_REQUEST_ENTER_SIM_PIN2:
        return "ENTER_SIM_PIN2";
    case RIL_REQUEST_ENTER_SIM_PUK2:
        return "ENTER_SIM_PUK2";
    case RIL_REQUEST_CHANGE_SIM_PIN:
        return "CHANGE_SIM_PIN";
    case RIL_REQUEST_CHANGE_SIM_PIN2:
        return "CHANGE_SIM_PIN2";
    case RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION:
        return "ENTER_NETWORK_DEPERSONALIZATION";
    case RIL_REQUEST_GET_CURRENT_CALLS:
        return "GET_CURRENT_CALLS";
    case RIL_REQUEST_DIAL:
        return "DIAL";
    case RIL_REQUEST_GET_IMSI:
        return "GET_IMSI";
    case RIL_REQUEST_HANGUP:
        return "HANGUP";
    case RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND:
        return "HANGUP_WAITING_OR_BACKGROUND";
    case RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND:
        return "HANGUP_FOREGROUND_RESUME_BACKGROUND";
    case RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE:
        return "REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE";
    case RIL_REQUEST_CONFERENCE:
        return "CONFERENCE";
    case RIL_REQUEST_UDUB:
        return "UDUB";
    case RIL_REQUEST_LAST_CALL_FAIL_CAUSE:
        return "LAST_CALL_FAIL_CAUSE";
    case RIL_REQUEST_SIGNAL_STRENGTH:
        return "SIGNAL_STRENGTH";
    case RIL_REQUEST_VOICE_REGISTRATION_STATE:
        return "VOICE_REGISTRATION_STATE";
    case RIL_REQUEST_DATA_REGISTRATION_STATE:
        return "DATA_REGISTRATION_STATE";
    case RIL_REQUEST_OPERATOR:
        return "OPERATOR";
    case RIL_REQUEST_RADIO_POWER:
        return "RADIO_POWER";
    case RIL_REQUEST_DTMF:
        return "DTMF";
    case RIL_REQUEST_SEND_SMS:
        return "SEND_SMS";
    case RIL_REQUEST_SEND_SMS_EXPECT_MORE:
        return "SEND_SMS_EXPECT_MORE";
    case RIL_REQUEST_SETUP_DATA_CALL:
        return "SETUP_DATA_CALL";
    case RIL_REQUEST_SIM_IO:
        return "SIM_IO";
    case RIL_REQUEST_SEND_USSD:
        return "SEND_USSD";
    case RIL_REQUEST_CANCEL_USSD:
        return "CANCEL_USSD";
    case RIL_REQUEST_GET_CLIR:
        return "GET_CLIR";
    case RIL_REQUEST_SET_CLIR:
        return "SET_CLIR";
    case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS:
        return "QUERY_CALL_FORWARD_STATUS";
    case RIL_REQUEST_SET_CALL_FORWARD:
        return "SET_CALL_FORWARD";
    case RIL_REQUEST_QUERY_CALL_WAITING:
        return "QUERY_CALL_WAITING";
    case RIL_REQUEST_SET_CALL_WAITING:
        return "SET_CALL_WAITING";
    case RIL_REQUEST_SMS_ACKNOWLEDGE:
        return "SMS_ACKNOWLEDGE";
    case RIL_REQUEST_GET_IMEI:
        return "GET_IMEI";
    case RIL_REQUEST_GET_IMEISV:
        return "GET_IMEISV";
    case RIL_REQUEST_ANSWER:
        return "ANSWER";
    case RIL_REQUEST_DEACTIVATE_DATA_CALL:
        return "DEACTIVATE_DATA_CALL";
    case RIL_REQUEST_QUERY_FACILITY_LOCK:
        return "QUERY_FACILITY_LOCK";
    case RIL_REQUEST_SET_FACILITY_LOCK:
        return "SET_FACILITY_LOCK";
    case RIL_REQUEST_CHANGE_BARRING_PASSWORD:
        return "CHANGE_BARRING_PASSWORD";
    case RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE:
        return "QUERY_NETWORK_SELECTION_MODE";
    case RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC:
        return "SET_NETWORK_SELECTION_AUTOMATIC";
    case RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL:
        return "SET_NETWORK_SELECTION_MANUAL";
    case RIL_REQUEST_QUERY_AVAILABLE_NETWORKS:
        return "QUERY_AVAILABLE_NETWORKS ";
    case RIL_REQUEST_DTMF_START:
        return "DTMF_START";
    case RIL_REQUEST_DTMF_STOP:
        return "DTMF_STOP";
    case RIL_REQUEST_BASEBAND_VERSION:
        return "BASEBAND_VERSION";
    case RIL_REQUEST_SEPARATE_CONNECTION:
        return "SEPARATE_CONNECTION";
    case RIL_REQUEST_SET_MUTE:
        return "SET_MUTE";
    case RIL_REQUEST_GET_MUTE:
        return "GET_MUTE";
    case RIL_REQUEST_QUERY_CLIP:
        return "QUERY_CLIP";
    case RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE:
        return "LAST_DATA_CALL_FAIL_CAUSE";
    case RIL_REQUEST_DATA_CALL_LIST:
        return "DATA_CALL_LIST";
    case RIL_REQUEST_RESET_RADIO:
        return "RESET_RADIO";
    case RIL_REQUEST_OEM_HOOK_RAW:
        return "OEM_HOOK_RAW";
    case RIL_REQUEST_OEM_HOOK_STRINGS:
        return "OEM_HOOK_STRINGS";
    case RIL_REQUEST_SCREEN_STATE:
        return "SCREEN_STATE";
    case RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION:
        return "SET_SUPP_SVC_NOTIFICATION";
    case RIL_REQUEST_WRITE_SMS_TO_SIM:
        return "WRITE_SMS_TO_SIM";
    case RIL_REQUEST_DELETE_SMS_ON_SIM:
        return "DELETE_SMS_ON_SIM";
    case RIL_REQUEST_SET_BAND_MODE:
        return "SET_BAND_MODE";
    case RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE:
        return "QUERY_AVAILABLE_BAND_MODE";
    case RIL_REQUEST_STK_GET_PROFILE:
        return "REQUEST_STK_GET_PROFILE";
    case RIL_REQUEST_STK_SET_PROFILE:
        return "REQUEST_STK_SET_PROFILE";
    case RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND:
        return "REQUEST_STK_SEND_ENVELOPE_COMMAND";
    case RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE:
        return "REQUEST_STK_SEND_TERMINAL_RESPONSE";
    case RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM:
        return "REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM";
    case RIL_REQUEST_EXPLICIT_CALL_TRANSFER:
        return "REQUEST_EXPLICIT_CALL_TRANSFER";
    case RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE:
        return "REQUEST_SET_PREFERRED_NETWORK_TYPE";
    case RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE:
        return "REQUEST_GET_PREFERRED_NETWORK_TYPE";
    case RIL_REQUEST_GET_NEIGHBORING_CELL_IDS:
        return "REQUEST_GET_NEIGHBORING_CELL_IDS";
    case RIL_REQUEST_SET_LOCATION_UPDATES:
        return "REQUEST_SET_LOCATION_UPDATES";
    case RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE:
        return "RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE";
    case RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE:
        return "RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE";
    case RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE:
        return "RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE";
    case RIL_REQUEST_SET_TTY_MODE:
        return "RIL_REQUEST_SET_TTY_MODE";
    case RIL_REQUEST_QUERY_TTY_MODE:
        return "RIL_REQUEST_QUERY_TTY_MODE";
    case RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE:
        return "RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE";
    case RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE:
        return "RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE";
    case RIL_REQUEST_CDMA_FLASH:
        return "RIL_REQUEST_CDMA_FLASH";
    case RIL_REQUEST_CDMA_BURST_DTMF:
        return "RIL_REQUEST_CDMA_BURST_DTMF";
    case RIL_REQUEST_CDMA_SEND_SMS:
        return "RIL_REQUEST_CDMA_SEND_SMS";
    case RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE:
        return "RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE";
    case RIL_REQUEST_GSM_GET_BROADCAST_CONFIG:
        return "RIL_REQUEST_GSM_GET_BROADCAST_CONFIG";
    case RIL_REQUEST_GSM_SET_BROADCAST_CONFIG:
        return "RIL_REQUEST_GSM_SET_BROADCAST_CONFIG";
    case RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG:
        return "RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG";
    case RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG:
        return "RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG";
    case RIL_REQUEST_GSM_BROADCAST_ACTIVATION:
        return "RIL_REQUEST_GSM_BROADCAST_ACTIVATION";
    case RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY:
        return "RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY";
    case RIL_REQUEST_CDMA_BROADCAST_ACTIVATION:
        return "RIL_REQUEST_CDMA_BROADCAST_ACTIVATION";
    case RIL_REQUEST_CDMA_SUBSCRIPTION:
        return "RIL_REQUEST_CDMA_SUBSCRIPTION";
    case RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM:
        return "RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM";
    case RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM:
        return "RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM";
    case RIL_REQUEST_DEVICE_IDENTITY:
        return "RIL_REQUEST_DEVICE_IDENTITY";
    case RIL_REQUEST_GET_SMSC_ADDRESS:
        return "RIL_REQUEST_GET_SMSC_ADDRESS";
    case RIL_REQUEST_SET_SMSC_ADDRESS:
        return "RIL_REQUEST_SET_SMSC_ADDRESS";
    case RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE:
        return "REQUEST_EXIT_EMERGENCY_CALLBACK_MODE";
    case RIL_REQUEST_REPORT_SMS_MEMORY_STATUS:
        return "RIL_REQUEST_REPORT_SMS_MEMORY_STATUS";
    case RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING:
        return "RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING";
    case RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE:
        return "RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE";
    case RIL_REQUEST_ISIM_AUTHENTICATION:
        return "RIL_REQUEST_ISIM_AUTHENTICATION";
    case RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU:
        return "RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU";
    case RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS:
        return "RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS";
    default:
        return "<unknown request>";
    }
}

void RilRequest::getIccCardStatus(RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_SIM_STATUS, result);

    LOGV << rr->serialString() << "> " << rr->requestToString() << ENDL;
    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::supplyIccPin(std::string pin, RilResponse *result)
{
    supplyIccPinForApp(pin, "", result);
}

void RilRequest::supplyIccPinForApp(std::string pin, std::string aid, RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_ENTER_SIM_PIN, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(2);
    rr->mParcel.writeString(pin.c_str());
    rr->mParcel.writeString(aid.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::supplyIccPuk(std::string puk, std::string newPin, RilResponse *result)
{
    supplyIccPukForApp(puk, newPin, "", result);
}

void RilRequest::supplyIccPukForApp(std::string puk, std::string newPin, std::string aid, RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_ENTER_SIM_PUK, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(3);
    rr->mParcel.writeString(puk.c_str());
    rr->mParcel.writeString(newPin.c_str());
    rr->mParcel.writeString(aid.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::supplyIccPin2(std::string pin, RilResponse *result)
{
    supplyIccPin2ForApp(pin, "", result);
}

void RilRequest::supplyIccPin2ForApp(std::string pin, std::string aid, RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_ENTER_SIM_PIN2, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(2);
    rr->mParcel.writeString(pin.c_str());
    rr->mParcel.writeString(aid.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::supplyIccPuk2(std::string puk2, std::string newPin2, RilResponse *result)
{
    supplyIccPuk2ForApp(puk2, newPin2, "", result);
}

void RilRequest::supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid, RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_ENTER_SIM_PUK2, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(3);
    rr->mParcel.writeString(puk.c_str());
    rr->mParcel.writeString(newPin2.c_str());
    rr->mParcel.writeString(aid.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::changeIccPin(std::string oldPin, std::string newPin, RilResponse *result)
{
    changeIccPinForApp(oldPin, newPin, "", result);
}

void RilRequest::changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid, RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CHANGE_SIM_PIN, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(3);
    rr->mParcel.writeString(oldPin.c_str());
    rr->mParcel.writeString(newPin.c_str());
    rr->mParcel.writeString(aid.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::changeIccPin2(std::string oldPin2, std::string newPin2, RilResponse *result)
{
    changeIccPin2ForApp(oldPin2, newPin2, "", result);
}

void RilRequest::changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid, RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CHANGE_SIM_PIN2, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(3);
    rr->mParcel.writeString(oldPin2.c_str());
    rr->mParcel.writeString(newPin2.c_str());
    rr->mParcel.writeString(aid.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CHANGE_BARRING_PASSWORD, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(3);
    rr->mParcel.writeString(facility.c_str());
    rr->mParcel.writeString(oldPwd.c_str());
    rr->mParcel.writeString(newPwd.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::supplyNetworkDepersonalization(std::string netpin, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeInt(1);
    rr->mParcel.writeString(netpin.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getCurrentCalls(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_CURRENT_CALLS, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

__attribute_deprecated__ void RilRequest::getPDPContextList(RilResponse *result)
{
    getDataCallList(result);
}

void RilRequest::getDataCallList(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_DATA_CALL_LIST, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

// void RilRequest::dial(std::string address, int clirMode, RilResponse *result)
// {
//     dial(address, clirMode, "", result);
// }

// void RilRequest::dial(std::string address, int clirMode, UUSInfo *uusInfo, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//              RIL_REQUEST_DIAL, result);

//     rr->mParcel.writeString(address.c_str());
//     rr->mParcel.writeInt(clirMode);
//     rr->mParcel.writeInt(0); // UUS information is absent

//     if (uusInfo == nullptr)
//     {
//         rr->mParcel.writeInt(0); // UUS information is absent
//     }
//     else
//     {
//         rr->mParcel.writeInt(1); // UUS information is present
//         rr->mParcel.writeInt(uusInfo.getType());
//         rr->mParcel.writeInt(uusInfo.getDcs());
//         rr->mParcel.writeByteArray(uusInfo.getUserData());
//     }

//     LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
//     mResponse = result;
// }

void RilRequest::getIMSI(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_IMSI, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getIMEI(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_IMEI, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getIMEISV(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_IMEISV, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::hangupConnection(int gsmIndex, RilResponse *result)
{
    LOGFW("hangupConnection: gsmIndex = ", gsmIndex);

    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_HANGUP, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << gsmIndex << ENDL;

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(gsmIndex);

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::hangupWaitingOrBackground(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::hangupForegroundResumeBackground(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::switchWaitingOrHoldingAndActive(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::conference(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CONFERENCE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setPreferredVoicePrivacy(bool enable, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE,
        result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(enable ? 1 : 0);

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getPreferredVoicePrivacy(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE,
        result);
    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::separateConnection(int gsmIndex, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SEPARATE_CONNECTION, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << gsmIndex << ENDL;

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(gsmIndex);

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::acceptCall(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_ANSWER, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::rejectCall(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_UDUB, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::explicitCallTransfer(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_EXPLICIT_CALL_TRANSFER, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getLastCallFailCause(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_LAST_CALL_FAIL_CAUSE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

__attribute_deprecated__ void RilRequest::getLastPdpFailCause(RilResponse *result)
{
    getLastDataCallFailCause(result);
}

/**
 * The preferred new alternative to getLastPdpFailCause
 */
void RilRequest::getLastDataCallFailCause(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setMute(bool enableMute, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_MUTE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << enableMute << ENDL;

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(enableMute ? 1 : 0);

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getMute(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_MUTE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getSignalStrength(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SIGNAL_STRENGTH, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getVoiceRegistrationState(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_VOICE_REGISTRATION_STATE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getDataRegistrationState(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_DATA_REGISTRATION_STATE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
}

void RilRequest::getOperator(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_OPERATOR, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::sendDtmf(char c, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_DTMF, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeString(std::to_string(int(c)).c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::startDtmf(char c, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_DTMF_START, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeString(std::to_string(int(c)).c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::stopDtmf(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_DTMF_STOP, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::sendBurstDtmf(std::string dtmfString, int on, int off, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CDMA_BURST_DTMF, result);

    rr->mParcel.writeInt(3);
    rr->mParcel.writeString(dtmfString.c_str());
    rr->mParcel.writeString(std::to_string(on).c_str());
    rr->mParcel.writeString(std::to_string(off).c_str());

    LOGV << rr->serialString() + "> " << rr->requestToString() << dtmfString << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::sendSMS(std::string smscPDU, std::string pdu, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SEND_SMS, result);

    rr->mParcel.writeInt(2);
    rr->mParcel.writeString(smscPDU.c_str());
    rr->mParcel.writeString(pdu.c_str());

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

// void RilRequest::sendCdmaSms(uint8_t *pdu, RilResponse *result)
// {
//     int address_nbr_of_digits;
//     int subaddr_nbr_of_digits;
//     int bearerDataLength;
//     ByteArrayInputStream bais = new ByteArrayInputStream(pdu);
//     DataInputStream dis = new DataInputStream(bais);

//     RilRequest *rr = RILREQUEST::obtain(
//            RIL_REQUEST_CDMA_SEND_SMS, result);

//     try
//     {
//         rr->mParcel.writeInt(dis.readInt());        //teleServiceId
//         rr->mParcel.writeByte((byte)dis.readInt()); //servicePresent
//         rr->mParcel.writeInt(dis.readInt());        //serviceCategory
//         rr->mParcel.writeInt(dis.read());           //address_digit_mode
//         rr->mParcel.writeInt(dis.read());           //address_nbr_mode
//         rr->mParcel.writeInt(dis.read());           //address_ton
//         rr->mParcel.writeInt(dis.read());           //address_nbr_plan
//         address_nbr_of_digits = (byte)dis.read();
//         rr->mParcel.writeByte((byte)address_nbr_of_digits);
//         for (int i = 0; i < address_nbr_of_digits; i++)
//         {
//             rr->mParcel.writeByte(dis.readByte()); // address_orig_bytes[i]
//         }
//         rr->mParcel.writeInt(dis.read());        //subaddressType
//         rr->mParcel.writeByte((byte)dis.read()); //subaddr_odd
//         subaddr_nbr_of_digits = (byte)dis.read();
//         rr->mParcel.writeByte((byte)subaddr_nbr_of_digits);
//         for (int i = 0; i < subaddr_nbr_of_digits; i++)
//         {
//             rr->mParcel.writeByte(dis.readByte()); //subaddr_orig_bytes[i]
//         }

//         bearerDataLength = dis.read();
//         rr->mParcel.writeInt(bearerDataLength);
//         for (int i = 0; i < bearerDataLength; i++)
//         {
//             rr->mParcel.writeByte(dis.readByte()); //bearerData[i]
//         }
//     }
//     catch (IOException ex)
//     {

//         riljLog("sendSmsCdma: conversion from input stream to object failed: " + ex);
//     }

//     LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
//     mResponse = result;
// }

void RilRequest::deleteSmsOnSim(int index, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_DELETE_SMS_ON_SIM,
        result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(index);

    if (false)
        LOGV << rr->serialString() + "> " << rr->requestToString() << index << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::deleteSmsOnRuim(int index, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM,
        result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(index);

    if (false)
        LOGV << rr->serialString() + "> " << rr->requestToString() << index << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

/** Free space (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_FREE = 0;

/** Received and read (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_READ = 1;

/** Received and unread (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_UNREAD = 3;

/** Stored and sent (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_SENT = 5;

/** Stored and unsent (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_UNSENT = 7;
int RilRequest::translateStatus(int status)
{
    switch (status & 0x7)
    {
    case STATUS_ON_ICC_READ:
        return 1;
    case STATUS_ON_ICC_UNREAD:
        return 0;
    case STATUS_ON_ICC_SENT:
        return 3;
    case STATUS_ON_ICC_UNSENT:
        return 2;
    }

    // Default to READ.
    return 1;
}

void RilRequest::writeSmsToSim(int status, std::string smsc, std::string pdu, RilResponse *result)
{
    status = translateStatus(status);

    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_WRITE_SMS_TO_SIM,
        result);

    rr->mParcel.writeInt(status);
    rr->mParcel.writeString(pdu.c_str());
    rr->mParcel.writeString(smsc.c_str());

    if (false)
        LOGV << rr->serialString() + "> " << rr->requestToString() << status << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::writeSmsToRuim(int status, std::string pdu, RilResponse *result)
{
    status = translateStatus(status);

    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM,
        result);

    rr->mParcel.writeInt(status);
    rr->mParcel.writeString(pdu.c_str());

    if (false)
        LOGV << rr->serialString() + "> " << rr->requestToString() << status << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
                               std::string user, std::string password, std::string authType, std::string protocol,
                               RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SETUP_DATA_CALL, result);

    rr->mParcel.writeInt(7);

    rr->mParcel.writeString(radioTechnology.c_str());
    rr->mParcel.writeString(profile.c_str());
    rr->mParcel.writeString(apn.c_str());
    rr->mParcel.writeString(user.c_str());
    rr->mParcel.writeString(password.c_str());
    rr->mParcel.writeString(authType.c_str());
    rr->mParcel.writeString(protocol.c_str());

    LOGV << rr->serialString() + "> " << rr->requestToString() << " "
         << radioTechnology + " " + profile + " " + apn + " " + user + " "
         << password + " " + authType + " " + protocol << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::deactivateDataCall(int cid, int reason, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_DEACTIVATE_DATA_CALL, result);

    rr->mParcel.writeInt(2);
    rr->mParcel.writeString(std::to_string(cid).c_str());
    rr->mParcel.writeString(std::to_string(reason).c_str());

    LOGV << rr->serialString() + "> " << requestToString() << " " << cid + " " << reason << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setRadioPower(bool on, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_RADIO_POWER, result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(on ? 1 : 0);

    LOGV << rr->serialString() + "> " << rr->requestToString() << (on ? " on" : " off") << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setSuppServiceNotifications(bool enable, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION, result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(enable ? 1 : 0);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::acknowledgeLastIncomingGsmSms(bool success, int cause, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SMS_ACKNOWLEDGE, result);

    rr->mParcel.writeInt(2);
    rr->mParcel.writeInt(success ? 1 : 0);
    rr->mParcel.writeInt(cause);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " << success << " " << cause << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::acknowledgeLastIncomingCdmaSms(bool success, int cause, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE, result);

    rr->mParcel.writeInt(success ? 0 : 1); //RIL_CDMA_SMS_ErrorClass
    // cause code according to X.S004-550E
    rr->mParcel.writeInt(cause);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " << success << " " << cause << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU, result);

    rr->mParcel.writeInt(2);
    rr->mParcel.writeString(success ? "1" : "0");
    rr->mParcel.writeString(ackPdu.c_str());

    LOGV << rr->serialString() + "> " << rr->requestToString() << ' ' << success << " [" + ackPdu + ']' << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
                       std::string data, std::string pin2, RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SIM_IO, result);

    rr->mParcel.writeInt(command);
    rr->mParcel.writeInt(fileid);
    rr->mParcel.writeString(path.c_str());
    rr->mParcel.writeInt(p1);
    rr->mParcel.writeInt(p2);
    rr->mParcel.writeInt(p3);
    rr->mParcel.writeString(data.c_str());
    rr->mParcel.writeString(pin2.c_str());

    LOGV << serialString() + "> iccIO: " << rr->requestToString()
         << " 0x" << std::hex << command << " 0x" << fileid << " "
         << " path: " << path << "," << p1 << "," << p2 << "," << p3 << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getCLIR(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_CLIR, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setCLIR(int clirMode, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_CLIR, result);

    // count ints
    rr->mParcel.writeInt(1);

    rr->mParcel.writeInt(clirMode);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " << clirMode << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::queryCallWaiting(int serviceClass, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_QUERY_CALL_WAITING, result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(serviceClass);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " + serviceClass << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setCallWaiting(bool enable, int serviceClass, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_CALL_WAITING, result);

    rr->mParcel.writeInt(2);
    rr->mParcel.writeInt(enable ? 1 : 0);
    rr->mParcel.writeInt(serviceClass);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " << enable << ", " << serviceClass << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setNetworkSelectionModeAutomatic(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setNetworkSelectionModeManual(std::string operatorNumeric, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " + operatorNumeric << ENDL;

    rr->mParcel.writeString(operatorNumeric.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getNetworkSelectionMode(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getAvailableNetworks(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_QUERY_AVAILABLE_NETWORKS,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setCallForward(int action, int cfReason, int serviceClass,
                                std::string number, int timeSeconds, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_CALL_FORWARD, result);

    rr->mParcel.writeInt(action);
    rr->mParcel.writeInt(cfReason);
    rr->mParcel.writeInt(serviceClass);
    rr->mParcel.writeInt(number.length());
    rr->mParcel.writeString(number.c_str());
    rr->mParcel.writeInt(timeSeconds);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " "
         << action + " " << cfReason << " " << serviceClass << timeSeconds << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::queryCallForwardStatus(int cfReason, int serviceClass,
                                        std::string number, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_QUERY_CALL_FORWARD_STATUS, result);

    rr->mParcel.writeInt(2); // 2 is for query action, not in used anyway
    rr->mParcel.writeInt(cfReason);
    rr->mParcel.writeInt(serviceClass);
    rr->mParcel.writeInt(number.length());
    rr->mParcel.writeString(number.c_str());
    rr->mParcel.writeInt(0);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " "
         << cfReason << " " << serviceClass << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::queryCLIP(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_QUERY_CLIP, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getBasebandVersion(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_BASEBAND_VERSION, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::queryFacilityLock(std::string facility, std::string password, int serviceClass,
                                   RilResponse *response)
{
    queryFacilityLockForApp(facility, password, serviceClass, "", response);
}

void RilRequest::queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId,
                                         RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_QUERY_FACILITY_LOCK, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    // count strings
    rr->mParcel.writeInt(4);

    rr->mParcel.writeString(facility.c_str());
    rr->mParcel.writeString(password.c_str());

    rr->mParcel.writeString(std::to_string(serviceClass).c_str());
    rr->mParcel.writeString(appId.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setFacilityLock(std::string facility, bool lockState, std::string password,
                                 int serviceClass, RilResponse *response)
{
    setFacilityLockForApp(facility, lockState, password, serviceClass, "", response);
}

void RilRequest::setFacilityLockForApp(std::string facility, bool lockState, std::string password,
                                       int serviceClass, std::string appId, RilResponse *result)
{
    std::string lockString;
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_FACILITY_LOCK, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    // count strings
    rr->mParcel.writeInt(5);

    rr->mParcel.writeString(facility.c_str());
    lockString = (lockState) ? "1" : "0";
    rr->mParcel.writeString(lockString.c_str());
    rr->mParcel.writeString(password.c_str());
    rr->mParcel.writeString(std::to_string(serviceClass).c_str());
    rr->mParcel.writeString(appId.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::sendUSSD(std::string ussdString, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SEND_USSD, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " + ussdString << ENDL;

    rr->mParcel.writeString(ussdString.c_str());

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::cancelPendingUssd(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_CANCEL_USSD, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::resetRadio(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_RESET_RADIO, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

// void RilRequest::invokeOemRilRequestRaw(uint8_t *data, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//               RIL_REQUEST_OEM_HOOK_RAW, result);

//     LOGV << rr->serialString() + "> " << rr->requestToString() << "[" + IccUtils.bytesToHexString(data) + "]" << ENDL;

//     rr->mParcel.writeByteArray(data);

//     RILREQUEST::send(rr);
//     mResponse = result;
// }

// void RilRequest::invokeOemRilRequestStrings(std::string[] strings, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//                 RIL_REQUEST_OEM_HOOK_STRINGS, response);

//     LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr->mParcel.writeStringArray(std::strings);

//     RILREQUEST::send(rr);
//     mResponse = result;
// }

/**
 * Assign a specified band for RF configuration.
 *
 * @param bandMode one of BM_*_BAND
 * @param response is callback message
 */
void RilRequest::setBandMode(int bandMode, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_BAND_MODE, result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(bandMode);

    LOGV << rr->serialString() + "> " << rr->requestToString() << " " << bandMode << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

/**
 * Query the list of band mode supported by RF.
 *
 * @param response is callback message
 *        ((AsyncResult)response.obj).result  is an int[] with every
 *        element representing one avialable BM_*_BAND
 */
void RilRequest::queryAvailableBandMode(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::sendTerminalResponse(std::string contents, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeString(contents.c_str());
    RILREQUEST::send(rr);

    mResponse = result;
}

void RilRequest::sendEnvelope(std::string contents, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    rr->mParcel.writeString(contents.c_str());
    RILREQUEST::send(rr);

    mResponse = result;
}

void RilRequest::sendEnvelopeWithStatus(std::string contents, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << '[' + contents + ']' << ENDL;

    rr->mParcel.writeString(contents.c_str());
    RILREQUEST::send(rr);

    mResponse = result;
}

// void RilRequest::handleCallSetupRequestFromSim(
//     bool accept, RilResponse *result)
// {

//     RilRequest *rr = RILREQUEST::obtain(
//         RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM,
//         result);

//     LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     int[] param = new int[1];
//     param[0] = accept ? 1 : 0;
//     rr->mParcel.writeIntArray(param);
//     RILREQUEST::send(rr);

//     mResponse = result;
// }

// void RilRequest::setPreferredNetworkType(int networkType, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE, result);

//     rr->mParcel.writeInt(1);
//     rr->mParcel.writeInt(networkType);

//     mSetPreferredNetworkType = networkType;
//     mPreferredNetworkType = networkType;

//         LOGV << rr->serialString() + "> " << rr->requestToString() <<  " : " + networkType);

//         RILREQUEST::send(rr);
//         mResponse = result;
// }

void RilRequest::getPreferredNetworkType(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getNeighboringCids(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_NEIGHBORING_CELL_IDS,
        result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setLocationUpdates(bool enable, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_LOCATION_UPDATES, result);
    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(enable ? 1 : 0);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ": " << enable << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getSmscAddress(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GET_SMSC_ADDRESS, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::setSmscAddress(std::string address, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_SET_SMSC_ADDRESS, result);

    rr->mParcel.writeString(address.c_str());

    LOGV << rr->serialString() + "> " << rr->requestToString() << " : " + address << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::reportSmsMemoryStatus(bool available, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_REPORT_SMS_MEMORY_STATUS, result);
    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(available ? 1 : 0);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ": " << available << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::reportStkServiceIsRunning(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

void RilRequest::getGsmBroadcastConfig(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GSM_GET_BROADCAST_CONFIG, result);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

// void RilRequest::setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//           RIL_REQUEST_GSM_SET_BROADCAST_CONFIG, result);

//     int numOfConfig = config.length;
//     rr->mParcel.writeInt(numOfConfig);

//     for (int i = 0; i < numOfConfig; i++)
//     {
//         rr->mParcel.writeInt(config[i].getFromServiceId());
//         rr->mParcel.writeInt(config[i].getToServiceId());
//         rr->mParcel.writeInt(config[i].getFromCodeScheme());
//         rr->mParcel.writeInt(config[i].getToCodeScheme());
//         rr->mParcel.writeInt(config[i].isSelected() ? 1 : 0);
//     }

//     {
//         LOGV << rr->serialString() + "> " << rr->requestToString() <<  " with " + numOfConfig + " configs : ");
//         for (int i = 0; i < numOfConfig; i++)
//         {
//             riljLog(config[i].toString());
//         }
//     }

//     RILREQUEST::send(rr);
//     mResponse = result;
// }

void RilRequest::setGsmBroadcastActivation(bool activate, RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(
        RIL_REQUEST_GSM_BROADCAST_ACTIVATION, result);

    rr->mParcel.writeInt(1);
    rr->mParcel.writeInt(activate ? 0 : 1);

    LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
    mResponse = result;
}

// //***** Private Methods

// private
// void sendScreenState(bool on)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RIL_REQUEST_SCREEN_STATE, null);
//     rr->mParcel.writeInt(1);
//     rr->mParcel.writeInt(on ? 1 : 0);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() <<  ": " + on);

// RILREQUEST::send(rr);
// mResponse = result;
// }

// // ***** Methods for CDMA support
// public
// void getDeviceIdentity(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DEVICE_IDENTITY, response);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getCDMASubscription(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_SUBSCRIPTION, response);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// void setPhoneType(int phoneType)
// { // Called by CDMAPhone and GSMPhone constructor
//
//         riljLog("setPhoneType=" + phoneType + " old value=" + mPhoneType);
//     mPhoneType = phoneType;
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void queryCdmaRoamingPreference(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE, response);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaRoamingPreference(int cdmaRoamingType, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(cdmaRoamingType);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + cdmaRoamingType);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaSubscriptionSource(int cdmaSubscription, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(cdmaSubscription);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + cdmaSubscription);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// void getCdmaSubscriptionSource(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE, response);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void queryTTYMode(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_QUERY_TTY_MODE, response);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setTTYMode(int ttyMode, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_SET_TTY_MODE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(ttyMode);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + ttyMode);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void sendCDMAFeatureCode(String FeatureCode, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_FLASH, response);

//     rr.mp.writeString(FeatureCode);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + FeatureCode);

//     RILREQUEST::send(rr);
// }

// public
// void getCdmaBroadcastConfig(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG, response);

//     RILREQUEST::send(rr);
// }

// // TODO: Change the configValuesArray to a RIL_BroadcastSMSConfig
// public
// void setCdmaBroadcastConfig(int[] configValuesArray, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG, response);

//     for (int i = 0; i < configValuesArray.length; i++)
//     {
//         rr.mp.writeInt(configValuesArray[i]);
//     }

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void setCdmaBroadcastActivation(boolean activate, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_BROADCAST_ACTIVATION, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(activate ? 0 : 1);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void exitEmergencyCallbackMode(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE, response);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void requestIsimAuthentication(String nonce, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ISIM_AUTHENTICATION, response);

//     rr.mp.writeString(nonce);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }
// }

void RilRequest::processSolicited(Parcel &p)
{
    int error = p.readInt();

    mResponse->setResponseID(get_commandid());
    mResponse->setResponseURCInfo(false);

    if (error == 0 || p.dataAvail() > 0)
    {
        // either command succeeds or command fails but with data payload
        switch (get_commandid())
        {
        case RIL_REQUEST_GET_SIM_STATUS:
            mResponse->responseIccCardStatus(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PIN:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PUK:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PIN2:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PUK2:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_CHANGE_SIM_PIN:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_CHANGE_SIM_PIN2:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_GET_CURRENT_CALLS:
            mResponse->responseCallList(p);
            return;
        case RIL_REQUEST_DIAL:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_GET_IMSI:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_HANGUP:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CONFERENCE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_UDUB:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_LAST_CALL_FAIL_CAUSE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_SIGNAL_STRENGTH:
            mResponse->responseSignalStrength(p);
            return;
        case RIL_REQUEST_VOICE_REGISTRATION_STATE:
            mResponse->responseStrings(p);
            return;
        case RIL_REQUEST_DATA_REGISTRATION_STATE:
            mResponse->responseStrings(p);
            return;
        case RIL_REQUEST_OPERATOR:
            mResponse->responseStrings(p);
            return;
        case RIL_REQUEST_RADIO_POWER:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_DTMF:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SEND_SMS:
            mResponse->responseSMS(p);
            return;
        case RIL_REQUEST_SEND_SMS_EXPECT_MORE:
            mResponse->responseSMS(p);
            return;
        case RIL_REQUEST_SETUP_DATA_CALL:
            mResponse->responseSetupDataCall(p);
            return;
        case RIL_REQUEST_SIM_IO:
            mResponse->responseICC_IO(p);
            return;
        case RIL_REQUEST_SEND_USSD:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CANCEL_USSD:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_GET_CLIR:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_SET_CLIR:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS:
            mResponse->responseCallForward(p);
            return;
        case RIL_REQUEST_SET_CALL_FORWARD:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_CALL_WAITING:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_SET_CALL_WAITING:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SMS_ACKNOWLEDGE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_GET_IMEI:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_GET_IMEISV:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_ANSWER:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_DEACTIVATE_DATA_CALL:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_FACILITY_LOCK:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_SET_FACILITY_LOCK:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_CHANGE_BARRING_PASSWORD:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_AVAILABLE_NETWORKS:
            mResponse->responseOperatorInfos(p);
            return;
        case RIL_REQUEST_DTMF_START:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_DTMF_STOP:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_BASEBAND_VERSION:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_SEPARATE_CONNECTION:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SET_MUTE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_GET_MUTE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_QUERY_CLIP:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_DATA_CALL_LIST:
            mResponse->responseDataCallList(p);
            return;
        case RIL_REQUEST_RESET_RADIO:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_OEM_HOOK_RAW:
            mResponse->responseRaw(p);
            return;
        case RIL_REQUEST_OEM_HOOK_STRINGS:
            mResponse->responseStrings(p);
            return;
        case RIL_REQUEST_SCREEN_STATE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_WRITE_SMS_TO_SIM:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_DELETE_SMS_ON_SIM:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SET_BAND_MODE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_STK_GET_PROFILE:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_STK_SET_PROFILE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_EXPLICIT_CALL_TRANSFER:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE:
            mResponse->responseGetPreferredNetworkType(p);
            return;
        case RIL_REQUEST_GET_NEIGHBORING_CELL_IDS:
            mResponse->responseCellList(p);
            return;
        case RIL_REQUEST_SET_LOCATION_UPDATES:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_SET_TTY_MODE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_TTY_MODE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_CDMA_FLASH:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_BURST_DTMF:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SEND_SMS:
            mResponse->responseSMS(p);
            return;
        case RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_GSM_GET_BROADCAST_CONFIG:
            mResponse->responseGmsBroadcastConfig(p);
            return;
        case RIL_REQUEST_GSM_SET_BROADCAST_CONFIG:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_GSM_BROADCAST_ACTIVATION:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG:
            mResponse->responseCdmaBroadcastConfig(p);
            return;
        case RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_BROADCAST_ACTIVATION:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SUBSCRIPTION:
            mResponse->responseStrings(p);
            return;
        case RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_DEVICE_IDENTITY:
            mResponse->responseStrings(p);
            return;
        case RIL_REQUEST_GET_SMSC_ADDRESS:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_SET_SMSC_ADDRESS:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_REPORT_SMS_MEMORY_STATUS:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE:
            mResponse->responseInts(p);
            return;
        case RIL_REQUEST_ISIM_AUTHENTICATION:
            mResponse->responseString(p);
            return;
        case RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU:
            mResponse->responseVoid(p);
            return;
        case RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS:
            mResponse->responseICC_IO(p);
            return;
        default:
            LOGW << "currently not supported" << ENDL;
        }
    }
}

void RilRequest::processUnsolicited(Parcel &p)
{
    int cmdid = p.readInt();
    RilResponse TMPResponse;

    mResponse->setResponseID(cmdid);
    mResponse->setResponseURCInfo(true);

    // either command succeeds or command fails but with data payload
    switch (cmdid)
    {
    case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_RESPONSE_NEW_SMS:
        TMPResponse.responseString(p);
        break;
    case RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT:
        TMPResponse.responseString(p);
        break;
    case RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOL_ON_USSD:
        TMPResponse.responseStrings(p);
        break;
    case RIL_UNSOL_NITZ_TIME_RECEIVED:
        TMPResponse.responseString(p);
        break;
    case RIL_UNSOL_SIGNAL_STRENGTH:
        TMPResponse.responseSignalStrength(p);
        break;
    case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
        TMPResponse.responseDataCallList(p);
        break;
    case RIL_UNSOL_SUPP_SVC_NOTIFICATION:
        TMPResponse.responseSuppServiceNotification(p);
        break;
    case RIL_UNSOL_STK_SESSION_END:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_STK_PROACTIVE_COMMAND:
        TMPResponse.responseString(p);
        break;
    case RIL_UNSOL_STK_EVENT_NOTIFY:
        TMPResponse.responseString(p);
        break;
    case RIL_UNSOL_STK_CALL_SETUP:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOL_SIM_SMS_STORAGE_FULL:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_SIM_REFRESH:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOL_CALL_RING:
        TMPResponse.responseCallRing(p);
        break;
    case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
        TMPResponse.responseCdmaSms(p);
        break;
    case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
        TMPResponse.responseRaw(p);
        break;
    case RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_CDMA_CALL_WAITING:
        TMPResponse.responseCdmaCallWaiting(p);
        break;
    case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOL_CDMA_INFO_REC:
        TMPResponse.responseCdmaInformationRecord(p);
        break;
    case RIL_UNSOL_OEM_HOOK_RAW:
        TMPResponse.responseRaw(p);
        break;
    case RIL_UNSOL_RINGBACK_TONE:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOL_RESEND_INCALL_MUTE:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOl_CDMA_PRL_CHANGED:
        TMPResponse.responseInts(p);
        break;
    case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
        TMPResponse.responseVoid(p);
        break;
    case RIL_UNSOL_RIL_CONNECTED:
        TMPResponse.responseInts(p);
        break;
    default:
        LOGE << "un recognized commandid" << ENDL;
    }

    switch (cmdid)
    {
        // case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
        //     /* has bonus radio state int */
        //     RadioState newState = getRadioStateFromInt(p.readInt());
        //     if (RILJ_LOGD)
        //         unsljLogMore(response, newState.toString());

        //     switchToRadioState(newState);
        //     break;
        // case RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     mCallStateRegistrants
        //         .notifyRegistrants(new AsyncResult(null, nullptr, null));
        //     break;
        // case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     mVoiceNetworkStateRegistrants
        //         .notifyRegistrants(new AsyncResult(null, nullptr, null));
        //     break;
        // case RIL_UNSOL_RESPONSE_NEW_SMS:
        // {
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     // FIXME this should move up a layer
        //     std::string a[] = new std::string[2];

        //     a[1] = (std::string)ret;

        //     SmsMessage sms;

        //     sms = SmsMessage.newFromCMT(a);
        //     if (mGsmSmsRegistrant != null)
        //     {
        //         mGsmSmsRegistrant
        //             .notifyRegistrant(new AsyncResult(null, sms, null));
        //     }
        //     break;
        // }
        // case RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mSmsStatusRegistrant != null)
        //     {
        //         mSmsStatusRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;
        // case RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     int[] smsIndex = (int[])ret;

        //     if (smsIndex.length == 1)
        //     {
        //         if (mSmsOnSimRegistrant != null)
        //         {
        //             mSmsOnSimRegistrant.notifyRegistrant(new AsyncResult(null, smsIndex, null));
        //         }
        //     }
        //     else
        //     {
        //         if (RILJ_LOGD)
        //             riljLog(" NEW_SMS_ON_SIM ERROR with wrong length " + smsIndex.length);
        //     }
        //     break;
        // case RIL_UNSOL_ON_USSD:
        //     std::string[] resp = (std::string[])ret;

        //     if (resp.length < 2)
        //     {
        //         resp = new std::string[2];
        //         resp[0] = ((std::string[])ret)[0];
        //         resp[1] = null;
        //     }
        //     if (RILJ_LOGD)
        //         unsljLogMore(response, resp[0]);
        //     if (mUSSDRegistrant != null)
        //     {
        //         mUSSDRegistrant.notifyRegistrant(
        //             new AsyncResult(null, resp, null));
        //     }
        //     break;
        // case RIL_UNSOL_NITZ_TIME_RECEIVED:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     // has bonus long containing milliseconds since boot that the NITZ
        //     // time was received
        //     long nitzReceiveTime = p.readLong();

        //     Object[] result = new Object[2];

        //     result[0] = ret;
        //     result[1] = Long.valueOf(nitzReceiveTime);

        //     if (mNITZTimeRegistrant != null)
        //     {

        //         mNITZTimeRegistrant
        //             .notifyRegistrant(new AsyncResult(null, result, null));
        //     }
        //     else
        //     {
        //         // in case NITZ time registrant isnt registered yet
        //         mLastNITZTimeInfo = result;
        //     }
        //     break;

        // case RIL_UNSOL_SIGNAL_STRENGTH:
        //     // Note this is set to "verbose" because it happens
        //     // frequently
        //     if (RILJ_LOGV)
        //         unsljLogvRet(response, ret);

        //     if (mSignalStrengthRegistrant != null)
        //     {
        //         mSignalStrengthRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;
        // case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     mDataNetworkStateRegistrants.notifyRegistrants(new AsyncResult(null, ret, null));
        //     break;

        // case RIL_UNSOL_SUPP_SVC_NOTIFICATION:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mSsnRegistrant != null)
        //     {
        //         mSsnRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_SESSION_END:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     if (mCatSessionEndRegistrant != null)
        //     {
        //         mCatSessionEndRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_PROACTIVE_COMMAND:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCatProCmdRegistrant != null)
        //     {
        //         mCatProCmdRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_EVENT_NOTIFY:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCatEventRegistrant != null)
        //     {
        //         mCatEventRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_CALL_SETUP:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCatCallSetUpRegistrant != null)
        //     {
        //         mCatCallSetUpRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_SIM_SMS_STORAGE_FULL:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     if (mIccSmsFullRegistrant != null)
        //     {
        //         mIccSmsFullRegistrant.notifyRegistrant();
        //     }
        //     break;

        // case RIL_UNSOL_SIM_REFRESH:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mIccRefreshRegistrants != null)
        //     {
        //         mIccRefreshRegistrants.notifyRegistrants(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CALL_RING:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mRingRegistrant != null)
        //     {
        //         mRingRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLogvRet(response, ret);
        //     if (mRestrictedStateRegistrant != null)
        //     {
        //         mRestrictedStateRegistrant.notifyRegistrant(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     if (mIccStatusChangedRegistrants != null)
        //     {
        //         mIccStatusChangedRegistrants.notifyRegistrants();
        //     }
        //     break;

        // case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     SmsMessage sms = (SmsMessage)ret;

        //     if (mCdmaSmsRegistrant != null)
        //     {
        //         mCdmaSmsRegistrant
        //             .notifyRegistrant(new AsyncResult(null, sms, null));
        //     }
        //     break;

        // case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     if (mGsmBroadcastSmsRegistrant != null)
        //     {
        //         mGsmBroadcastSmsRegistrant
        //             .notifyRegistrant(new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     if (mIccSmsFullRegistrant != null)
        //     {
        //         mIccSmsFullRegistrant.notifyRegistrant();
        //     }
        //     break;

        // case RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     if (mEmergencyCallbackModeRegistrant != null)
        //     {
        //         mEmergencyCallbackModeRegistrant.notifyRegistrant();
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_CALL_WAITING:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCallWaitingInfoRegistrants != null)
        //     {
        //         mCallWaitingInfoRegistrants.notifyRegistrants(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mOtaProvisionRegistrants != null)
        //     {
        //         mOtaProvisionRegistrants.notifyRegistrants(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_INFO_REC:
        //     ArrayList<CdmaInformationRecords> listInfoRecs;

        //     try
        //     {
        //         listInfoRecs = (ArrayList<CdmaInformationRecords>)ret;
        //     }
        //     catch (ClassCastException e)
        //     {
        //         Log.e(LOG_TAG, "Unexpected exception casting to listInfoRecs", e);
        //         break;
        //     }

        //     for (CdmaInformationRecords rec : listInfoRecs)
        //     {
        //         if (RILJ_LOGD)
        //             unsljLogRet(response, rec);
        //         notifyRegistrantsCdmaInfoRec(rec);
        //     }
        //     break;

        // case RIL_UNSOL_OEM_HOOK_RAW:
        //     if (RILJ_LOGD)
        //         unsljLogvRet(response, IccUtils.bytesToHexString((byte[])ret));
        //     if (mUnsolOemHookRawRegistrant != null)
        //     {
        //         mUnsolOemHookRawRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_RINGBACK_TONE:
        //     if (RILJ_LOGD)
        //         unsljLogvRet(response, ret);
        //     if (mRingbackToneRegistrants != null)
        //     {
        //         bool playtone = (((int[])ret)[0] == 1);
        //         mRingbackToneRegistrants.notifyRegistrants(
        //             new AsyncResult(null, playtone, null));
        //     }
        //     break;

        // case RIL_UNSOL_RESEND_INCALL_MUTE:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mResendIncallMuteRegistrants != null)
        //     {
        //         mResendIncallMuteRegistrants.notifyRegistrants(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCdmaSubscriptionChangedRegistrants != null)
        //     {
        //         mCdmaSubscriptionChangedRegistrants.notifyRegistrants(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOl_CDMA_PRL_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCdmaPrlChangedRegistrants != null)
        //     {
        //         mCdmaPrlChangedRegistrants.notifyRegistrants(
        //             new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mExitEmergencyCallbackModeRegistrants != null)
        //     {
        //         mExitEmergencyCallbackModeRegistrants.notifyRegistrants(
        //             new AsyncResult(null, nullptr, null));
        //     }
        //     break;

        // case RIL_UNSOL_RIL_CONNECTED:
        // {
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     // Initial conditions
        //     setRadioPower(false, null);
        //     setPreferredNetworkType(mPreferredNetworkType, null);
        //     setCdmaSubscriptionSource(mCdmaSubscription, null);
        //     notifyRegistrantsRilConnectionChanged(((int[])ret)[0]);
        //     break;
        // }
    }
}
