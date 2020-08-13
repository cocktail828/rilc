#include <assert.h>
#include <vector>

#include "ril_commands.h"
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

int RilRequest::get_requestid()
{
    return mRequestId;
}

int RilRequest::get_commandid()
{
    return mCommandId;
}

std::vector<std::string> RilRequest::responseStrings(Parcel &p)
{
    int num;
    std::vector<std::string> response;

    num = p.readInt();
    for (int i = 0; i < num; i++)
    {
        auto str = p.readString();
        response.emplace_back(str);
        p.freeString(str);
    }

    return response;
}

const void *RilRequest::responseString(Parcel &p)
{
    const char *response = p.readString();

    return reinterpret_cast<const void *>(response);
}

std::vector<int> RilRequest::responseInts(Parcel &p)
{
    int numInts;
    std::vector<int> response;

    numInts = p.readInt();

    for (int i = 0; i < numInts; i++)
    {
        response.emplace_back(p.readInt());
    }

    return response;
}

const void *RilRequest::responseVoid(Parcel &p)
{
    return nullptr;
}

void RilRequest::processSolicited(Parcel &p)
{
    int error = p.readInt();
    if (error == 0 || p.dataAvail() > 0)
    {
        // either command succeeds or command fails but with data payload
        switch (get_commandid())
        {
        // case RIL_REQUEST_GET_SIM_STATUS:
        //     responseIccCardStatus(p);
        //     return;
        // case RIL_REQUEST_ENTER_SIM_PIN:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_ENTER_SIM_PUK:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_ENTER_SIM_PIN2:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_ENTER_SIM_PUK2:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_CHANGE_SIM_PIN:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_CHANGE_SIM_PIN2:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_GET_CURRENT_CALLS:
        //     responseCallList(p);
        //     return;
        // case RIL_REQUEST_DIAL:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_GET_IMSI:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_HANGUP:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CONFERENCE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_UDUB:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_LAST_CALL_FAIL_CAUSE:
        //     responseInts(p);
        //     return;
        case RIL_REQUEST_SIGNAL_STRENGTH:
            responseSignalStrength(p);
            return;
        // case RIL_REQUEST_VOICE_REGISTRATION_STATE:
        //     responseStrings(p);
        //     return;
        // case RIL_REQUEST_DATA_REGISTRATION_STATE:
        //     responseStrings(p);
        //     return;
        // case RIL_REQUEST_OPERATOR:
        //     responseStrings(p);
        //     return;
        // case RIL_REQUEST_RADIO_POWER:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_DTMF:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SEND_SMS:
        //     responseSMS(p);
        //     return;
        // case RIL_REQUEST_SEND_SMS_EXPECT_MORE:
        //     responseSMS(p);
        //     return;
        // case RIL_REQUEST_SETUP_DATA_CALL:
        //     responseSetupDataCall(p);
        //     return;
        // case RIL_REQUEST_SIM_IO:
        //     responseICC_IO(p);
        //     return;
        // case RIL_REQUEST_SEND_USSD:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CANCEL_USSD:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_GET_CLIR:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_SET_CLIR:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS:
        //     responseCallForward(p);
        //     return;
        // case RIL_REQUEST_SET_CALL_FORWARD:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_QUERY_CALL_WAITING:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_SET_CALL_WAITING:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SMS_ACKNOWLEDGE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_GET_IMEI:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_GET_IMEISV:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_ANSWER:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_DEACTIVATE_DATA_CALL:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_QUERY_FACILITY_LOCK:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_SET_FACILITY_LOCK:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_CHANGE_BARRING_PASSWORD:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_QUERY_AVAILABLE_NETWORKS:
        //     responseOperatorInfos(p);
        //     return;
        // case RIL_REQUEST_DTMF_START:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_DTMF_STOP:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_BASEBAND_VERSION:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_SEPARATE_CONNECTION:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SET_MUTE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_GET_MUTE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_QUERY_CLIP:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_DATA_CALL_LIST:
        //     responseDataCallList(p);
        //     return;
        // case RIL_REQUEST_RESET_RADIO:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_OEM_HOOK_RAW:
        //     responseRaw(p);
        //     return;
        // case RIL_REQUEST_OEM_HOOK_STRINGS:
        //     responseStrings(p);
        //     return;
        // case RIL_REQUEST_SCREEN_STATE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_WRITE_SMS_TO_SIM:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_DELETE_SMS_ON_SIM:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SET_BAND_MODE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_STK_GET_PROFILE:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_STK_SET_PROFILE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_EXPLICIT_CALL_TRANSFER:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE:
        //     responseGetPreferredNetworkType(p);
        //     return;
        // case RIL_REQUEST_GET_NEIGHBORING_CELL_IDS:
        //     responseCellList(p);
        //     return;
        // case RIL_REQUEST_SET_LOCATION_UPDATES:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_SET_TTY_MODE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_QUERY_TTY_MODE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_CDMA_FLASH:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_BURST_DTMF:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_SEND_SMS:
        //     responseSMS(p);
        //     return;
        // case RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_GSM_GET_BROADCAST_CONFIG:
        //     responseGmsBroadcastConfig(p);
        //     return;
        // case RIL_REQUEST_GSM_SET_BROADCAST_CONFIG:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_GSM_BROADCAST_ACTIVATION:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG:
        //     responseCdmaBroadcastConfig(p);
        //     return;
        // case RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_BROADCAST_ACTIVATION:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_SUBSCRIPTION:
        //     responseStrings(p);
        //     return;
        // case RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_DEVICE_IDENTITY:
        //     responseStrings(p);
        //     return;
        // case RIL_REQUEST_GET_SMSC_ADDRESS:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_SET_SMSC_ADDRESS:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_REPORT_SMS_MEMORY_STATUS:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE:
        //     responseInts(p);
        //     return;
        // case RIL_REQUEST_ISIM_AUTHENTICATION:
        //     responseString(p);
        //     return;
        // case RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU:
        //     responseVoid(p);
        //     return;
        // case RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS:
        //     responseICC_IO(p);
        //     return;
        default:
            LOGW << "currently not supported" << ENDL;
        }
    }
}

void RilRequest::processUnsolicited(Parcel &p)
{
    int cmdid = p.readInt();

    // either command succeeds or command fails but with data payload
    switch (cmdid)
    {
    // case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_NEW_SMS:
    //     ret = responseString(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT:
    //     ret = responseString(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOL_ON_USSD:
    //     ret = responseStrings(p);
    //     break;
    // case RIL_UNSOL_NITZ_TIME_RECEIVED:
    //     ret = responseString(p);
    //     break;
    // case RIL_UNSOL_SIGNAL_STRENGTH:
    //     ret = responseSignalStrength(p);
    //     break;
    // case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
    //     ret = responseDataCallList(p);
    //     break;
    // case RIL_UNSOL_SUPP_SVC_NOTIFICATION:
    //     ret = responseSuppServiceNotification(p);
    //     break;
    // case RIL_UNSOL_STK_SESSION_END:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_STK_PROACTIVE_COMMAND:
    //     ret = responseString(p);
    //     break;
    // case RIL_UNSOL_STK_EVENT_NOTIFY:
    //     ret = responseString(p);
    //     break;
    // case RIL_UNSOL_STK_CALL_SETUP:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOL_SIM_SMS_STORAGE_FULL:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_SIM_REFRESH:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOL_CALL_RING:
    //     ret = responseCallRing(p);
    //     break;
    // case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
    //     ret = responseCdmaSms(p);
    //     break;
    // case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
    //     ret = responseRaw(p);
    //     break;
    // case RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_CDMA_CALL_WAITING:
    //     ret = responseCdmaCallWaiting(p);
    //     break;
    // case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOL_CDMA_INFO_REC:
    //     ret = responseCdmaInformationRecord(p);
    //     break;
    // case RIL_UNSOL_OEM_HOOK_RAW:
    //     ret = responseRaw(p);
    //     break;
    // case RIL_UNSOL_RINGBACK_TONE:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOL_RESEND_INCALL_MUTE:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOl_CDMA_PRL_CHANGED:
    //     ret = responseInts(p);
    //     break;
    // case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
    //     ret = responseVoid(p);
    //     break;
    // case RIL_UNSOL_RIL_CONNECTED:
    //     ret = responseInts(p);
    //     break;
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
        //         .notifyRegistrants(new AsyncResult(null, null, null));
        //     break;
        // case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     mVoiceNetworkStateRegistrants
        //         .notifyRegistrants(new AsyncResult(null, null, null));
        //     break;
        // case RIL_UNSOL_RESPONSE_NEW_SMS:
        // {
        //     if (RILJ_LOGD)
        //         unsljLog(response);

        //     // FIXME this should move up a layer
        //     String a[] = new String[2];

        //     a[1] = (String)ret;

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
        //     String[] resp = (String[])ret;

        //     if (resp.length < 2)
        //     {
        //         resp = new String[2];
        //         resp[0] = ((String[])ret)[0];
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
        //         boolean playtone = (((int[])ret)[0] == 1);
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
        //             new AsyncResult(null, null, null));
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
