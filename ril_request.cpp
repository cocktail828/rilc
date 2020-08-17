#include <assert.h>
#include <vector>

#include "ril_request.h"
#include "ril_response.h"
#include "logger.h"
#include "ril.h"

DeviceManager *RilRequest::mDeviceMgr = nullptr;
int RilRequest::mGlobalRequestId = 0;
;
bool RilRequest::mReady = false;
std::mutex RilRequest::mGlobalLock;

static std::string requestidToString(int id)
{
    return std::to_string(id);
}

static std::string commandidToString(int cid)
{
    switch (cid)
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
        return "RIL_REQUEST_CDMA_SET_PREFEthisED_VOICE_PRIVACY_MODE";
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

/**
 * use dto build an new request will only 'command id'
 */
void RilRequest::obtain(int cid)
{
    mRequestId = ++mGlobalRequestId;
    mCommandId = cid;

    /* marshal command id */
    mParcel.writeInt(cid);

    /* marshal request id */
    mParcel.writeInt(mRequestId);
}

/**
 * Notice, the instance is an static variable,
 * which means, it's the same for all instances of the class.
 * for all instances shared the same DevciceManager and mGlobalRequestId
 */
RilRequest &RilRequest::instance()
{
    static RilRequest instance_;
    return instance_;
}

/**
 * start a new polling thread for read.
 * the thread is need for reading response and send requests
 */
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

    if (!mDeviceMgr->openDevice())
        return false;

    for (int times = 0; times < 10; times++)
    {
        if (mDeviceMgr->isReady())
            return true;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return false;
}

/**
 * clean up what is created in 'init' function
 */
bool RilRequest::uninit()
{
    if (mDeviceMgr && mDeviceMgr->closeDevice())
    {
        delete mDeviceMgr;
        return true;
    }

    return false;
}

/**
 * check whether the DeviceManager is ready for send and read
 */
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

/**
 * send requests. if success, the request will be add the observer list
 * so it can be notified, if it's response reachs
 */
bool RilRequest::blockSend(RilRequest *rr)
{
    std::unique_lock<std::mutex> _lk(rr->mRequestLock);

    if (mDeviceMgr && mDeviceMgr->isReady())
    {
        uint8_t dataLength[4];

        // parcel length in big endian
        dataLength[0] = dataLength[1] = 0;
        dataLength[2] = (uint8_t)((rr->mParcel.dataSize() >> 8) & 0xff);
        dataLength[3] = (uint8_t)((rr->mParcel.dataSize()) & 0xff);

        mDeviceMgr->sendAsync(dataLength, 4);

        mDeviceMgr->sendAsync(
            reinterpret_cast<const void *>(rr->mParcel.data()),
            rr->mParcel.dataSize());
        mDeviceMgr->attach(rr);

        if (rr->mRequestCond.wait_for(_lk, std::chrono::seconds(5)) == std::cv_status::timeout)
        {
            LOGE << requestidToString(rr->get_requestid()) << "> "
                 << commandidToString(rr->get_commandid()) << " timeout" << ENDL;
            mDeviceMgr->detach(rr);
        }
        return true;
    }
    else
    {
        LOGE << "device is not ready" << ENDL;
    }
    return false;
}

RilRequest::RilRequest()
{
}

RilRequest::~RilRequest()
{
}

/**
 * When get some message from DeviceManager, this function will be called
 */
void RilRequest::update(Parcel &p)
{
    /* oops! device manager is destroyed */
    if (p.dataSize() == 0)
    {
        LOGW << "null response get, device connect may be broken" << ENDL;
        mRequestCond.notify_one();
        return;
    }
    else
    {
        /**
         * we only process socilited message response here
         * unsolicited message should be processed in DeviceManager
         */
        processSolicited(p);
        mRequestCond.notify_one();
    }
    return;
}

int RilRequest::get_requestid()
{
    return mRequestId;
}

int RilRequest::get_commandid()
{
    return mCommandId;
}

void RilRequest::getIccCardStatus()
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_GET_SIM_STATUS);

    LOGD << requestidToString(get_requestid()) << "> " << commandidToString(get_commandid()) << ENDL;
    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::supplyIccPin(std::string pin)
{
    supplyIccPinForApp(pin, "");
}

void RilRequest::supplyIccPinForApp(std::string pin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PIN);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(2);
    mParcel.writeString(pin.c_str());
    mParcel.writeString(aid.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::supplyIccPuk(std::string puk, std::string newPin)
{
    supplyIccPukForApp(puk, newPin, "");
}

void RilRequest::supplyIccPukForApp(std::string puk, std::string newPin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PUK);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(3);
    mParcel.writeString(puk.c_str());
    mParcel.writeString(newPin.c_str());
    mParcel.writeString(aid.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::supplyIccPin2(std::string pin)
{
    supplyIccPin2ForApp(pin, "");
}

void RilRequest::supplyIccPin2ForApp(std::string pin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PIN2);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(2);
    mParcel.writeString(pin.c_str());
    mParcel.writeString(aid.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::supplyIccPuk2(std::string puk2, std::string newPin2)
{
    supplyIccPuk2ForApp(puk2, newPin2, "");
}

void RilRequest::supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PUK2);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(3);
    mParcel.writeString(puk.c_str());
    mParcel.writeString(newPin2.c_str());
    mParcel.writeString(aid.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::changeIccPin(std::string oldPin, std::string newPin)
{
    changeIccPinForApp(oldPin, newPin, "");
}

void RilRequest::changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_CHANGE_SIM_PIN);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(3);
    mParcel.writeString(oldPin.c_str());
    mParcel.writeString(newPin.c_str());
    mParcel.writeString(aid.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::changeIccPin2(std::string oldPin2, std::string newPin2)
{
    changeIccPin2ForApp(oldPin2, newPin2, "");
}

void RilRequest::changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_CHANGE_SIM_PIN2);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(3);
    mParcel.writeString(oldPin2.c_str());
    mParcel.writeString(newPin2.c_str());
    mParcel.writeString(aid.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd)
{
    obtain(RIL_REQUEST_CHANGE_BARRING_PASSWORD);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(3);
    mParcel.writeString(facility.c_str());
    mParcel.writeString(oldPwd.c_str());
    mParcel.writeString(newPwd.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::supplyNetworkDepersonalization(std::string netpin)
{
    obtain(RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeInt(1);
    mParcel.writeString(netpin.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getCurrentCalls()
{
    obtain(RIL_REQUEST_GET_CURRENT_CALLS);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

__attribute_deprecated__ void RilRequest::getPDPContextList()
{
    getDataCallList();
}

void RilRequest::getDataCallList()
{
    obtain(RIL_REQUEST_DATA_CALL_LIST);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

// void RilRequest::dial(std::string address, int clirMode)
// {
//     dial(address, clirMode, "");
// }

// void RilRequest::dial(std::string address, int clirMode, UUSInfo *uusInfo)
// {
//     obtain(//              RIL_REQUEST_DIAL);

//     mParcel.writeString(address.c_str());
//     mParcel.writeInt(clirMode);
//     mParcel.writeInt(0); // UUS information is absent

//     if (uusInfo == nullptr)
//     {
//         mParcel.writeInt(0); // UUS information is absent
//     }
//     else
//     {
//         mParcel.writeInt(1); // UUS information is present
//         mParcel.writeInt(uusInfo.getType());
//         mParcel.writeInt(uusInfo.getDcs());
//         mParcel.writeByteAthisay(uusInfo.getUserData());
//     }

//     LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

void RilRequest::getIMSI()
{
    obtain(RIL_REQUEST_GET_IMSI);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getIMEI()
{
    obtain(RIL_REQUEST_GET_IMEI);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getIMEISV()
{
    obtain(RIL_REQUEST_GET_IMEISV);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::hangupConnection(int gsmIndex)
{
    LOGFW("hangupConnection: gsmIndex = ", gsmIndex);

    obtain(RIL_REQUEST_HANGUP);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << gsmIndex << ENDL;

    mParcel.writeInt(1);
    mParcel.writeInt(gsmIndex);

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::hangupWaitingOrBackground()
{
    obtain(RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::hangupForegroundResumeBackground()
{
    obtain(RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::switchWaitingOrHoldingAndActive()
{
    obtain(RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::conference()
{
    obtain(RIL_REQUEST_CONFERENCE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setPreferredVoicePrivacy(bool enable)
{
    obtain(RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE);

    mParcel.writeInt(1);
    mParcel.writeInt(enable ? 1 : 0);

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getPreferredVoicePrivacy()
{
    obtain(RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE);
    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::separateConnection(int gsmIndex)
{
    obtain(RIL_REQUEST_SEPARATE_CONNECTION);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << gsmIndex << ENDL;

    mParcel.writeInt(1);
    mParcel.writeInt(gsmIndex);

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::acceptCall()
{
    obtain(RIL_REQUEST_ANSWER);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::rejectCall()
{
    obtain(RIL_REQUEST_UDUB);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::explicitCallTransfer()
{
    obtain(RIL_REQUEST_EXPLICIT_CALL_TRANSFER);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getLastCallFailCause()
{
    obtain(RIL_REQUEST_LAST_CALL_FAIL_CAUSE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

__attribute_deprecated__ void RilRequest::getLastPdpFailCause()
{
    getLastDataCallFailCause();
}

/**
 * The prefethised new(std::nothrow) alternative to getLastPdpFailCause
 */
void RilRequest::getLastDataCallFailCause()
{
    obtain(RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setMute(bool enableMute)
{
    obtain(RIL_REQUEST_SET_MUTE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << enableMute << ENDL;

    mParcel.writeInt(1);
    mParcel.writeInt(enableMute ? 1 : 0);

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getMute()
{
    obtain(RIL_REQUEST_GET_MUTE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getSignalStrength()
{
    obtain(RIL_REQUEST_SIGNAL_STRENGTH);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getVoiceRegistrationState()
{
    obtain(RIL_REQUEST_VOICE_REGISTRATION_STATE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getDataRegistrationState()
{
    obtain(RIL_REQUEST_DATA_REGISTRATION_STATE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getOperator()
{
    obtain(RIL_REQUEST_OPERATOR);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::sendDtmf(char c)
{
    obtain(RIL_REQUEST_DTMF);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeString(std::to_string(int(c)).c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::startDtmf(char c)
{
    obtain(RIL_REQUEST_DTMF_START);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeString(std::to_string(int(c)).c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::stopDtmf()
{
    obtain(RIL_REQUEST_DTMF_STOP);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::sendBurstDtmf(std::string dtmfString, int on, int off)
{
    obtain(RIL_REQUEST_CDMA_BURST_DTMF);

    mParcel.writeInt(3);
    mParcel.writeString(dtmfString.c_str());
    mParcel.writeString(std::to_string(on).c_str());
    mParcel.writeString(std::to_string(off).c_str());

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << dtmfString << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::sendSMS(std::string smscPDU, std::string pdu)
{
    obtain(RIL_REQUEST_SEND_SMS);

    mParcel.writeInt(2);
    mParcel.writeString(smscPDU.c_str());
    mParcel.writeString(pdu.c_str());

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

// void RilRequest::sendCdmaSms(uint8_t *pdu)
// {
//     int address_nbr_of_digits;
//     int subaddr_nbr_of_digits;
//     int bearerDataLength;
//     ByteAthisayInputStream bais = new(std::nothrow) ByteAthisayInputStream(pdu);
//     DataInputStream dis = new(std::nothrow) DataInputStream(bais);

//     obtain(//            RIL_REQUEST_CDMA_SEND_SMS,
//            result);

//     try
//     {
//         mParcel.writeInt(dis.readInt());        //teleServiceId
//         mParcel.writeByte((byte)dis.readInt()); //servicePresent
//         mParcel.writeInt(dis.readInt());        //serviceCategory
//         mParcel.writeInt(dis.read());           //address_digit_mode
//         mParcel.writeInt(dis.read());           //address_nbr_mode
//         mParcel.writeInt(dis.read());           //address_ton
//         mParcel.writeInt(dis.read());           //address_nbr_plan
//         address_nbr_of_digits = (byte)dis.read();
//         mParcel.writeByte((byte)address_nbr_of_digits);
//         for (int i = 0; i < address_nbr_of_digits; i++)
//         {
//             mParcel.writeByte(dis.readByte()); // address_orig_bytes[i]
//         }
//         mParcel.writeInt(dis.read());        //subaddressType
//         mParcel.writeByte((byte)dis.read()); //subaddr_odd
//         subaddr_nbr_of_digits = (byte)dis.read();
//         mParcel.writeByte((byte)subaddr_nbr_of_digits);
//         for (int i = 0; i < subaddr_nbr_of_digits; i++)
//         {
//             mParcel.writeByte(dis.readByte()); //subaddr_orig_bytes[i]
//         }

//         bearerDataLength = dis.read();
//         mParcel.writeInt(bearerDataLength);
//         for (int i = 0; i < bearerDataLength; i++)
//         {
//             mParcel.writeByte(dis.readByte()); //bearerData[i]
//         }
//     }
//     catch (IOException ex)
//     {

//         riljLog("sendSmsCdma: conversion from input stream to object failed: " + ex);
//     }

//     LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
//     mResponse = result;
// }

void RilRequest::deleteSmsOnSim(int index)
{
    obtain(RIL_REQUEST_DELETE_SMS_ON_SIM);

    mParcel.writeInt(1);
    mParcel.writeInt(index);

    if (false)
        LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << index << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::deleteSmsOnRuim(int index)
{
    obtain(RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM);

    mParcel.writeInt(1);
    mParcel.writeInt(index);

    if (false)
        LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << index << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
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

void RilRequest::writeSmsToSim(int status, std::string smsc, std::string pdu)
{
    status = translateStatus(status);

    obtain(RIL_REQUEST_WRITE_SMS_TO_SIM);

    mParcel.writeInt(status);
    mParcel.writeString(pdu.c_str());
    mParcel.writeString(smsc.c_str());

    if (false)
        LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << status << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::writeSmsToRuim(int status, std::string pdu)
{
    status = translateStatus(status);

    obtain(RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM);

    mParcel.writeInt(status);
    mParcel.writeString(pdu.c_str());

    if (false)
        LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << status << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
                               std::string user, std::string password, std::string authType, std::string protocol)
{
    obtain(RIL_REQUEST_SETUP_DATA_CALL);

    mParcel.writeInt(7);

    mParcel.writeString(radioTechnology.c_str());
    mParcel.writeString(profile.c_str());
    mParcel.writeString(apn.c_str());
    mParcel.writeString(user.c_str());
    mParcel.writeString(password.c_str());
    mParcel.writeString(authType.c_str());
    mParcel.writeString(protocol.c_str());

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " "
         << radioTechnology + " " + profile + " " + apn + " " + user + " "
         << password + " " + authType + " " + protocol << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::deactivateDataCall(int cid, int reason)
{
    obtain(RIL_REQUEST_DEACTIVATE_DATA_CALL);

    mParcel.writeInt(2);
    mParcel.writeString(std::to_string(cid).c_str());
    mParcel.writeString(std::to_string(reason).c_str());

    LOGD << requestidToString(get_requestid()) + "> "
         << commandidToString(get_commandid()) << " " << cid << " " << reason << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setRadioPower(bool on)
{
    obtain(RIL_REQUEST_RADIO_POWER);

    mParcel.writeInt(1);
    mParcel.writeInt(on ? 1 : 0);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << (on ? " on" : " off") << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setSuppServiceNotifications(bool enable)
{
    obtain(RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION);

    mParcel.writeInt(1);
    mParcel.writeInt(enable ? 1 : 0);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::acknowledgeLastIncomingGsmSms(bool success, int cause)
{
    obtain(RIL_REQUEST_SMS_ACKNOWLEDGE);

    mParcel.writeInt(2);
    mParcel.writeInt(success ? 1 : 0);
    mParcel.writeInt(cause);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " " << success << " " << cause << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::acknowledgeLastIncomingCdmaSms(bool success, int cause)
{
    obtain(RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE);

    mParcel.writeInt(success ? 0 : 1); //RIL_CDMA_SMS_EthisorClass
    // cause code according to X.S004-550E
    mParcel.writeInt(cause);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " " << success << " " << cause << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu)
{
    obtain(RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU);

    mParcel.writeInt(2);
    mParcel.writeString(success ? "1" : "0");
    mParcel.writeString(ackPdu.c_str());

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ' ' << success << " [" + ackPdu + ']' << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
                       std::string data, std::string pin2)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_SIM_IO);

    mParcel.writeInt(command);
    mParcel.writeInt(fileid);
    mParcel.writeString(path.c_str());
    mParcel.writeInt(p1);
    mParcel.writeInt(p2);
    mParcel.writeInt(p3);
    mParcel.writeString(data.c_str());
    mParcel.writeString(pin2.c_str());

    LOGD << requestidToString(get_requestid()) + "> iccIO: " << commandidToString(get_commandid())
         << " 0x" << std::hex << command << " 0x" << fileid << " "
         << " path: " << path << "," << p1 << "," << p2 << "," << p3 << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getCLIR()
{
    obtain(RIL_REQUEST_GET_CLIR);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setCLIR(int clirMode)
{
    obtain(RIL_REQUEST_SET_CLIR);

    // count ints
    mParcel.writeInt(1);

    mParcel.writeInt(clirMode);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " " << clirMode << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::queryCallWaiting(int serviceClass)
{
    obtain(RIL_REQUEST_QUERY_CALL_WAITING);

    mParcel.writeInt(1);
    mParcel.writeInt(serviceClass);

    LOGD << requestidToString(get_requestid()) + "> "
         << commandidToString(get_commandid()) << " " << serviceClass << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setCallWaiting(bool enable, int serviceClass)
{
    obtain(RIL_REQUEST_SET_CALL_WAITING);

    mParcel.writeInt(2);
    mParcel.writeInt(enable ? 1 : 0);
    mParcel.writeInt(serviceClass);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " " << enable << ", " << serviceClass << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setNetworkSelectionModeAutomatic()
{
    obtain(RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setNetworkSelectionModeManual(std::string operatorNumeric)
{
    obtain(RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " " + operatorNumeric << ENDL;

    mParcel.writeString(operatorNumeric.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getNetworkSelectionMode()
{
    obtain(RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getAvailableNetworks()
{
    obtain(RIL_REQUEST_QUERY_AVAILABLE_NETWORKS);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setCallForward(int action, int cfReason, int serviceClass,
                                std::string number, int timeSeconds)
{
    obtain(RIL_REQUEST_SET_CALL_FORWARD);

    mParcel.writeInt(action);
    mParcel.writeInt(cfReason);
    mParcel.writeInt(serviceClass);
    mParcel.writeInt(number.length());
    mParcel.writeString(number.c_str());
    mParcel.writeInt(timeSeconds);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " "
         << action << " " << cfReason << " " << serviceClass << timeSeconds << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::queryCallForwardStatus(int cfReason, int serviceClass,
                                        std::string number)
{
    obtain(RIL_REQUEST_QUERY_CALL_FORWARD_STATUS);

    mParcel.writeInt(2); // 2 is for query action, not in used anyway
    mParcel.writeInt(cfReason);
    mParcel.writeInt(serviceClass);
    mParcel.writeInt(number.length());
    mParcel.writeString(number.c_str());
    mParcel.writeInt(0);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " "
         << cfReason << " " << serviceClass << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::queryCLIP()
{
    obtain(RIL_REQUEST_QUERY_CLIP);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getBasebandVersion()
{
    obtain(RIL_REQUEST_BASEBAND_VERSION);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::queryFacilityLock(std::string facility, std::string password, int serviceClass)
{
    queryFacilityLockForApp(facility, password, serviceClass, "");
}

void RilRequest::queryFacilityLockForApp(std::string facility, std::string password,
                                         int serviceClass, std::string appId)
{
    obtain(RIL_REQUEST_QUERY_FACILITY_LOCK);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    // count strings
    mParcel.writeInt(4);

    mParcel.writeString(facility.c_str());
    mParcel.writeString(password.c_str());

    mParcel.writeString(std::to_string(serviceClass).c_str());
    mParcel.writeString(appId.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setFacilityLock(std::string facility, bool lockState, std::string password,
                                 int serviceClass)
{
    setFacilityLockForApp(facility, lockState, password, serviceClass, "");
}

void RilRequest::setFacilityLockForApp(std::string facility, bool lockState, std::string password,
                                       int serviceClass, std::string appId)
{
    std::string lockString;
    obtain(RIL_REQUEST_SET_FACILITY_LOCK);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    // count strings
    mParcel.writeInt(5);

    mParcel.writeString(facility.c_str());
    lockString = (lockState) ? "1" : "0";
    mParcel.writeString(lockString.c_str());
    mParcel.writeString(password.c_str());
    mParcel.writeString(std::to_string(serviceClass).c_str());
    mParcel.writeString(appId.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::sendUSSD(std::string ussdString)
{
    obtain(RIL_REQUEST_SEND_USSD);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " " + ussdString << ENDL;

    mParcel.writeString(ussdString.c_str());

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::cancelPendingUssd()
{
    obtain(RIL_REQUEST_CANCEL_USSD);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::resetRadio()
{
    obtain(RIL_REQUEST_RESET_RADIO);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

// void RilRequest::invokeOemRilRequestRaw(uint8_t *data)
// {
//     obtain(//               RIL_REQUEST_OEM_HOOK_RAW,
//               result);

//     LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << "[" + IccUtils.bytesToHexString(data) + "]" << ENDL;

//     mParcel.writeByteAthisay(data);
//     if (!blockSend(this)){
//     mResponse = result;
// }

// void RilRequest::invokeOemRilRequestStrings(std::string[] strings)
// {
//     obtain(//                 RIL_REQUEST_OEM_HOOK_STRINGS);

//     LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

//     mParcel.writeStringAthisay(std::strings);
//     if (!blockSend(this)){
//     mResponse = result;
// }

/**
 * Assign a specified band for RF configuration.
 *
 * @param bandMode one of BM_*_BAND
 * @param response is callback message
 */
void RilRequest::setBandMode(int bandMode)
{
    obtain(RIL_REQUEST_SET_BAND_MODE);

    mParcel.writeInt(1);
    mParcel.writeInt(bandMode);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " " << bandMode << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

/**
 * Query the list of band mode supported by 
 * std::unique_lock<std::mutex> _lk(mRequestLock);RF.
 *
 * @param response is callback message
 *        ((AsyncResult)response.obj).result  is an int[] with every
 *        element representing one avialable BM_*_BAND
 */
void RilRequest::queryAvailableBandMode()
{
    obtain(RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::sendTerminalResponse(std::string contents)
{
    obtain(RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeString(contents.c_str());
    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::sendEnvelope(std::string contents)
{
    obtain(RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    mParcel.writeString(contents.c_str());
    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::sendEnvelopeWithStatus(std::string contents)
{
    obtain(RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << '[' + contents + ']' << ENDL;

    mParcel.writeString(contents.c_str());
    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

// void RilRequest::handleCallSetupRequestFromSim(
//     bool accept)
// {

//     obtain(//         RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM,
//         result);

//     LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

//     int[] param = new(std::nothrow) int[1];
//     param[0] = accept ? 1 : 0;
//     mParcel.writeIntthisay(param);
//     if (!blockSend(this)){
//     mResponse = result;
// }

// void RilRequest::setPrefethisedNetworkType(int networkType)
// {
//     obtain(//         RIL_REQUEST_SET_PREFEthisED_NETWORK_TYPE,
//         result);

//     mParcel.writeInt(1);
//     mParcel.writeInt(networkType);

//     mSetPrefethisedNetworkType = networkType;
//     mPrefethisedNetworkType = networkType;

//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) <<  " : " + networkType);
//         if (!blockSend(this)){
//         mResponse = result;
// }

void RilRequest::getPreferredNetworkType()
{
    obtain(RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getNeighboringCids()
{
    obtain(RIL_REQUEST_GET_NEIGHBORING_CELL_IDS);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setLocationUpdates(bool enable)
{
    obtain(RIL_REQUEST_SET_LOCATION_UPDATES);
    mParcel.writeInt(1);
    mParcel.writeInt(enable ? 1 : 0);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ": " << enable << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getSmscAddress()
{
    obtain(RIL_REQUEST_GET_SMSC_ADDRESS);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::setSmscAddress(std::string address)
{
    obtain(RIL_REQUEST_SET_SMSC_ADDRESS);

    mParcel.writeString(address.c_str());

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << " : " + address << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::reportSmsMemoryStatus(bool available)
{
    obtain(RIL_REQUEST_REPORT_SMS_MEMORY_STATUS);
    mParcel.writeInt(1);
    mParcel.writeInt(available ? 1 : 0);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ": " << available << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::reportStkServiceIsRunning()
{
    obtain(RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

void RilRequest::getGsmBroadcastConfig()
{
    obtain(RIL_REQUEST_GSM_GET_BROADCAST_CONFIG);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

// void RilRequest::setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config)
// {
//     obtain(//           RIL_REQUEST_GSM_SET_BROADCAST_CONFIG,
//           result);

//     int numOfConfig = config.length;
//     mParcel.writeInt(numOfConfig);

//     for (int i = 0; i < numOfConfig; i++)
//     {
//         mParcel.writeInt(config[i].getFromServiceId());
//         mParcel.writeInt(config[i].getToServiceId());
//         mParcel.writeInt(config[i].getFromCodeScheme());
//         mParcel.writeInt(config[i].getToCodeScheme());
//         mParcel.writeInt(config[i].isSelected() ? 1 : 0);
//     }

//     {
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) <<  " with " + numOfConfig + " configs : ");
//         for (int i = 0; i < numOfConfig; i++)
//         {
//             riljLog(config[i].toString());
//         }
//     }
//     if (!blockSend(this)){
//     mResponse = result;
// }

void RilRequest::setGsmBroadcastActivation(bool activate)
{
    obtain(RIL_REQUEST_GSM_BROADCAST_ACTIVATION);

    mParcel.writeInt(1);
    mParcel.writeInt(activate ? 0 : 1);

    LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;

    if (!blockSend(this))
    {
        LOGE << "send request failed" << ENDL;
        return;
    }
}

// //***** Private Methods
// private
// void sendScreenState(bool on)
// {
//     obtain(//         RIL_REQUEST_SCREEN_STATE, null);
//     mParcel.writeInt(1);
//     mParcel.writeInt(on ? 1 : 0);
//
//         LOGD << equestidString(get_requestid()) + "> " << commandidToString(get_commandid()) <<  ": " + on);
// if (!blockSend(this)){
// mResponse = result;
// }

// // ***** Methods for CDMA support
// public
// void getDeviceIdentity(RilResponse *response)
// {
//     obtain(IL_REQUEST_DEVICE_IDENTITY);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

// public
// void getCDMASubscription(RilResponse *response)
// {
//     obtain(IL_REQUEST_CDMA_SUBSCRIPTION);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
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
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaRoamingPreference(int cdmaRoamingType)
// {
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE);

//     this.mp.writeInt(1);
//     this.mp.writeInt(cdmaRoamingType);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL+ " : " + cdmaRoamingType);
//     if (!blockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaSubscriptionSource(int cdmaSubscription)
// {
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE);

//     this.mp.writeInt(1);
//     this.mp.writeInt(cdmaSubscription);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL+ " : " + cdmaSubscription);
//     if (!blockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// void getCdmaSubscriptionSource(RilResponse *response)
// {
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void queryTTYMode(RilResponse *response)
// {
//     obtain(//         RILConstants.RIL_REQUEST_QUERY_TTY_MODE);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setTTYMode(int ttyMode)
// {
//     obtain(//         RILConstants.RIL_REQUEST_SET_TTY_MODE);

//     this.mp.writeInt(1);
//     this.mp.writeInt(ttyMode);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL+ " : " + ttyMode);
//     if (!blockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void sendCDMAFeatureCode(String FeatureCode)
// {
//     obtain(IL_REQUEST_CDMA_FLASH);

//     this.mp.writeString(FeatureCode);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL+ " : " + FeatureCode);
//     if (!blockSend(this)){
// }

// public
// void getCdmaBroadcastConfig(RilResponse *response)
// {
//     obtain(IL_REQUEST_CDMA_GET_BROADCAST_CONFIG);
//     if (!blockSend(this)){
// }

// // TODO: Change the configValuesAthisay to a RIL_BroadcastSMSConfig
// public
// void setCdmaBroadcastConfig(int[] configValuesAthisay)
// {
//     obtain(IL_REQUEST_CDMA_SET_BROADCAST_CONFIG);

//     for (int i = 0; i < configValuesAthisay.length; i++)
//     {
//         this.mp.writeInt(configValuesAthisay[i]);
//     }

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

// public
// void setCdmaBroadcastActivation(boolean activate)
// {
//     obtain(IL_REQUEST_CDMA_BROADCAST_ACTIVATION);

//     this.mp.writeInt(1);
//     this.mp.writeInt(activate ? 0 : 1);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void exitEmergencyCallbackMode(RilResponse *response)
// {
//     obtain(IL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }

// public
// void requestIsimAuthentication(String nonce)
// {
//     obtain(IL_REQUEST_ISIM_AUTHENTICATION);

//     this.mp.writeString(nonce);

//
//         LOGD << requestidToString(get_requestid()) + "> " << commandidToString(get_commandid()) << ENDL;
//     if (!blockSend(this)){
// }
// }

void RilRequest::processSolicited(Parcel &p)
{
    int error = p.readInt();

    RilResponse resp;

    resp.setResponseID(get_commandid());
    resp.setResponseURCInfo(false);

    if (error == 0 || p.dataAvail() > 0)
    {
        // either command succeeds or command fails but with data payload
        LOGD << "RESP for < " << commandidToString(get_commandid()) << ENDL;
        switch (get_commandid())
        {
        case RIL_REQUEST_GET_SIM_STATUS:
            resp.responseIccCardStatus(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PIN:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PUK:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PIN2:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_ENTER_SIM_PUK2:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_CHANGE_SIM_PIN:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_CHANGE_SIM_PIN2:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_GET_CURRENT_CALLS:
            resp.responseCallList(p);
            return;
        case RIL_REQUEST_DIAL:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_GET_IMSI:
            resp.responseString(p);
            return;
        case RIL_REQUEST_HANGUP:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CONFERENCE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_UDUB:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_LAST_CALL_FAIL_CAUSE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_SIGNAL_STRENGTH:
            resp.responseSignalStrength(p);
            return;
        case RIL_REQUEST_VOICE_REGISTRATION_STATE:
            resp.responseStrings(p);
            return;
        case RIL_REQUEST_DATA_REGISTRATION_STATE:
            resp.responseStrings(p);
            return;
        case RIL_REQUEST_OPERATOR:
            resp.responseStrings(p);
            return;
        case RIL_REQUEST_RADIO_POWER:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_DTMF:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SEND_SMS:
            resp.responseSMS(p);
            return;
        case RIL_REQUEST_SEND_SMS_EXPECT_MORE:
            resp.responseSMS(p);
            return;
        case RIL_REQUEST_SETUP_DATA_CALL:
            resp.responseSetupDataCall(p);
            return;
        case RIL_REQUEST_SIM_IO:
            resp.responseICC_IO(p);
            return;
        case RIL_REQUEST_SEND_USSD:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CANCEL_USSD:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_GET_CLIR:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_SET_CLIR:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS:
            resp.responseCallForward(p);
            return;
        case RIL_REQUEST_SET_CALL_FORWARD:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_CALL_WAITING:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_SET_CALL_WAITING:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SMS_ACKNOWLEDGE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_GET_IMEI:
            resp.responseString(p);
            return;
        case RIL_REQUEST_GET_IMEISV:
            resp.responseString(p);
            return;
        case RIL_REQUEST_ANSWER:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_DEACTIVATE_DATA_CALL:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_FACILITY_LOCK:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_SET_FACILITY_LOCK:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_CHANGE_BARRING_PASSWORD:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_AVAILABLE_NETWORKS:
            resp.responseOperatorInfos(p);
            return;
        case RIL_REQUEST_DTMF_START:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_DTMF_STOP:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_BASEBAND_VERSION:
            resp.responseString(p);
            return;
        case RIL_REQUEST_SEPARATE_CONNECTION:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SET_MUTE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_GET_MUTE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_QUERY_CLIP:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_DATA_CALL_LIST:
            resp.responseDataCallList(p);
            return;
        case RIL_REQUEST_RESET_RADIO:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_OEM_HOOK_RAW:
            resp.responseRaw(p);
            return;
        case RIL_REQUEST_OEM_HOOK_STRINGS:
            resp.responseStrings(p);
            return;
        case RIL_REQUEST_SCREEN_STATE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_WRITE_SMS_TO_SIM:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_DELETE_SMS_ON_SIM:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SET_BAND_MODE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_STK_GET_PROFILE:
            resp.responseString(p);
            return;
        case RIL_REQUEST_STK_SET_PROFILE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND:
            resp.responseString(p);
            return;
        case RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_EXPLICIT_CALL_TRANSFER:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE:
            resp.responseGetPreferredNetworkType(p);
            return;
        case RIL_REQUEST_GET_NEIGHBORING_CELL_IDS:
            resp.responseCellList(p);
            return;
        case RIL_REQUEST_SET_LOCATION_UPDATES:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_SET_TTY_MODE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_QUERY_TTY_MODE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_CDMA_FLASH:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_BURST_DTMF:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SEND_SMS:
            resp.responseSMS(p);
            return;
        case RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_GSM_GET_BROADCAST_CONFIG:
            resp.responseGmsBroadcastConfig(p);
            return;
        case RIL_REQUEST_GSM_SET_BROADCAST_CONFIG:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_GSM_BROADCAST_ACTIVATION:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG:
            resp.responseCdmaBroadcastConfig(p);
            return;
        case RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_BROADCAST_ACTIVATION:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_SUBSCRIPTION:
            resp.responseStrings(p);
            return;
        case RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_DEVICE_IDENTITY:
            resp.responseStrings(p);
            return;
        case RIL_REQUEST_GET_SMSC_ADDRESS:
            resp.responseString(p);
            return;
        case RIL_REQUEST_SET_SMSC_ADDRESS:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_REPORT_SMS_MEMORY_STATUS:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE:
            resp.responseInts(p);
            return;
        case RIL_REQUEST_ISIM_AUTHENTICATION:
            resp.responseString(p);
            return;
        case RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU:
            resp.responseVoid(p);
            return;
        case RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS:
            resp.responseICC_IO(p);
            return;
        default:
            LOGW << "cuthisently not supported" << ENDL;
        }
    }
    mRequestCond.notify_one();
}

void RilRequest::processUnsolicited(Parcel &p)
{
    int cmdid = p.readInt();
    RilResponse TMPResponse;

    // resp.setResponseID(cmdid);
    // resp.setResponseURCInfo(true);

    LOGD << "RESP < " << RilResponse::responseToString(cmdid) << ENDL;
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
        //     std::string a[] = new(std::nothrow) std::string[2];

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
        //             new(std::nothrow) AsyncResult(null, ret, null));
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
        //             riljLog(" NEW_SMS_ON_SIM ErrOR with wrong length " + smsIndex.length);
        //     }
        //     break;
        // case RIL_UNSOL_ON_USSD:
        //     std::string[] resp = (std::string[])ret;

        //     if (resp.length < 2)
        //     {
        //         resp = new(std::nothrow) std::string[2];
        //         resp[0] = ((std::string[])ret)[0];
        //         resp[1] = null;
        //     }
        //     if (RILJ_LOGD)
        //         unsljLogMore(response, resp[0]);
        //     if (mUSSDRegistrant != null)
        //     {
        //         mUSSDRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, resp, null));
        //     }
        //     break;
        // case RIL_UNSOL_NITZ_TIME_RECEIVED:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     // has bonus long containing milliseconds since boot that the NITZ
        //     // time was received
        //     long nitzReceiveTime = p.readLong();

        //     Object[] result = new(std::nothrow) Object[2];

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
        //     if (RILJ_LOGD)
        //         unsljLOGDRet(response, ret);

        //     if (mSignalStrengthRegistrant != null)
        //     {
        //         mSignalStrengthRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, ret, null));
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
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_SESSION_END:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     if (mCatSessionEndRegistrant != null)
        //     {
        //         mCatSessionEndRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_PROACTIVE_COMMAND:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCatProCmdRegistrant != null)
        //     {
        //         mCatProCmdRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_EVENT_NOTIFY:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCatEventRegistrant != null)
        //     {
        //         mCatEventRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_STK_CALL_SETUP:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCatCallSetUpRegistrant != null)
        //     {
        //         mCatCallSetUpRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, ret, null));
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
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CALL_RING:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mRingRegistrant != null)
        //     {
        //         mRingRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLOGDRet(response, ret);
        //     if (mRestrictedStateRegistrant != null)
        //     {
        //         mRestrictedStateRegistrant.notifyRegistrant(
        //             new(std::nothrow) AsyncResult(null, ret, null));
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
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mOtaProvisionRegistrants != null)
        //     {
        //         mOtaProvisionRegistrants.notifyRegistrants(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_INFO_REC:
        //     AthisayList<CdmaInformationRecords> listInfoRecs;

        //     try
        //     {
        //         listInfoRecs = (AthisayList<CdmaInformationRecords>)ret;
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
        //         unsljLOGDRet(response, IccUtils.bytesToHexString((byte[])ret));
        //     if (mUnsolOemHookRawRegistrant != null)
        //     {
        //         mUnsolOemHookRawRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_RINGBACK_TONE:
        //     if (RILJ_LOGD)
        //         unsljLOGDRet(response, ret);
        //     if (mRingbackToneRegistrants != null)
        //     {
        //         bool playtone = (((int[])ret)[0] == 1);
        //         mRingbackToneRegistrants.notifyRegistrants(
        //             new(std::nothrow) AsyncResult(null, playtone, null));
        //     }
        //     break;

        // case RIL_UNSOL_RESEND_INCALL_MUTE:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mResendIncallMuteRegistrants != null)
        //     {
        //         mResendIncallMuteRegistrants.notifyRegistrants(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCdmaSubscriptionChangedRegistrants != null)
        //     {
        //         mCdmaSubscriptionChangedRegistrants.notifyRegistrants(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOl_CDMA_PRL_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mCdmaPrlChangedRegistrants != null)
        //     {
        //         mCdmaPrlChangedRegistrants.notifyRegistrants(
        //             new(std::nothrow) AsyncResult(null, ret, null));
        //     }
        //     break;

        // case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     if (mExitEmergencyCallbackModeRegistrants != null)
        //     {
        //         mExitEmergencyCallbackModeRegistrants.notifyRegistrants(
        //             new(std::nothrow) AsyncResult(null, nullptr, null));
        //     }
        //     break;

        // case RIL_UNSOL_RIL_CONNECTED:
        // {
        //     if (RILJ_LOGD)
        //         unsljLogRet(response, ret);

        //     // Initial conditions
        //     setRadioPower(false, null);
        //     setPrefethisedNetworkType(mPrefethisedNetworkType, null);
        //     setCdmaSubscriptionSource(mCdmaSubscription, null);
        //     notifyRegistrantsRilConnectionChanged(((int[])ret)[0]);
        //     break;
        // }
    }
}
