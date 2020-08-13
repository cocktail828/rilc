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

RilRequest *RilRequest::obtain(int cid, Response *result)
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
    bool ret = false;
    if (mDeviceMgr)
    {
        if (mDeviceMgr->closeDevice())
        {
            delete mDeviceMgr;
            ret = true;
        }
    }
    return ret;
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

    // Argument *arg = reinterpret_cast<Argument *>(_arg);
    // if (arg->type == RESPONSE_SOLICITED)
    // {
    //     processSolicited(arg->parcel);
    // }
    // else if (arg->type == RESPONSE_UNSOLICITED)
    // {
    //     processUnsolicited(arg->parcel);
    // }

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
        int i = 0;
        // either command succeeds or command fails but with data payload
        do
        {
            if (ril_commands[i].commandid == get_commandid())
            {
                ril_commands[i].response_function(p);
                return;
            }
            i++;
        } while (1);
    }
}

void RilRequest::processUnsolicited(Parcel &p)
{
    int cmdid = p.readInt();

    int i = 0;
    // either command succeeds or command fails but with data payload
    do
    {
        if (ril_commands[i].commandid == cmdid)
        {
            ril_commands[i].response_function(p);
            break;
        }
        i++;
    } while (1);

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
