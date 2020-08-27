#include <thread>
#include <chrono>
#include <cassert>
#include <vector>

#include <stdarg.h>

#include "ril_request.h"
#include "ril_response.h"
#include "rilc_api.h"
#include "logger.h"

#define NULLSTR(str) (str == NULL ? "" : str)

int RILC_init(const char *device)
{
    const int max_try = 10;
    int try_time;

    /* another thread is doing init? */
    if (!RILREQUEST::mGlobalLock.try_lock())
        return EBUSY;

    if (RILREQUEST::isReady())
    {
        RILREQUEST::mGlobalLock.unlock();
        return 0;
    }

    for (try_time = 0; try_time < max_try; try_time++)
    {
        if (RILREQUEST::instance().init(device))
            break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        LOGI << "start polling thread fail, times = " << try_time << ENDL;
    }

    bool ret = RILREQUEST::instance().isReady();
    if (ret)
    {
        LOGI << "init successfully " << ENDL;
    }
    else
    {
        LOGI << "init failed " << ENDL;
    }

    RILREQUEST::mGlobalLock.unlock();

    return ret;
}

int RILC_uninit()
{
    if (!RILREQUEST::mGlobalLock.try_lock())
        return EBUSY;

    if (!RILREQUEST::isReady())
    {
        RILREQUEST::mGlobalLock.unlock();
        return 0;
    }

    int ret = RILREQUEST::uninit();
    RILREQUEST::mGlobalLock.unlock();
    return ret;
}

/**********************************************************************************/
/************************** RILC UNSOCILITED PROCESSERS ***************************/
/**********************************************************************************/
void rilc_unsocilited_register(int cmdid, void (*cb)(RILResponse *))
{
    auto processer = UnSocilitedResponseProcesser.find(cmdid);
    if (processer != UnSocilitedResponseProcesser.end())
    {
        processer->second.callback = cb;
        LOGI << "register callback for unsocilited: "
             << commandidToString(cmdid) << ENDL;
    }
    else
    {
        LOGE << "oops! cannot find handler for " << commandidToString(cmdid) << ENDL;
    }
}

void rilc_unsocilited_deregister(int cmdid)
{
    auto processer = UnSocilitedResponseProcesser.find(cmdid);
    if (processer != UnSocilitedResponseProcesser.end())
    {
        processer->second.callback = nullptr;
        LOGI << "deregister callback for unsocilited: "
             << commandidToString(cmdid) << ENDL;
    }
    else
    {
        LOGE << "oops! cannot find handler for " << commandidToString(cmdid) << ENDL;
    }
}

/********************************************************************************/
/************************** RILC STANDARD REQUESTS ******************************/
/********************************************************************************/
#define RILC_REQUEST_WITH_ARG(func, resp, arg, args...)                          \
    do                                                                           \
    {                                                                            \
        if (!resp)                                                               \
            LOGW << __func__ << " is called without response parameter" << ENDL; \
        else                                                                     \
            clock_gettime(CLOCK_MONOTONIC, &(resp->startTime));                  \
        RILRequest *req = new (std::nothrow) RILRequest(resp);                   \
        if (req->func(arg, ##args))                                              \
        {                                                                        \
            delete req;                                                          \
            return -1;                                                           \
        }                                                                        \
        return 0;                                                                \
    } while (0);

#define RILC_REQUEST_NO_ARG(func, resp)                                          \
    do                                                                           \
    {                                                                            \
        if (!resp)                                                               \
            LOGW << __func__ << " is called without response parameter" << ENDL; \
        else                                                                     \
            clock_gettime(CLOCK_MONOTONIC, &(resp->startTime));                  \
        RILRequest *req = new (std::nothrow) RILRequest(resp);                   \
        if (req->func())                                                         \
        {                                                                        \
            delete req;                                                          \
            return -1;                                                           \
        }                                                                        \
        return 0;                                                                \
    } while (0);

int RILC_getIccCardStatus(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getIccCardStatus, resp);
}

int RILC_supplyIccPin(RILResponse *resp, const char *pin)
{
    RILC_REQUEST_WITH_ARG(supplyIccPin, resp,
                          NULLSTR(pin));
}

int RILC_supplyIccPinForApp(RILResponse *resp, const char *pin, const char *aid)
{
    RILC_REQUEST_WITH_ARG(supplyIccPinForApp, resp,
                          NULLSTR(pin),
                          NULLSTR(aid));
}

int RILC_supplyIccPuk(RILResponse *resp, const char *puk, const char *newPin)
{
    RILC_REQUEST_WITH_ARG(supplyIccPuk, resp,
                          NULLSTR(puk),
                          NULLSTR(newPin));
}

int RILC_supplyIccPukForApp(RILResponse *resp, const char *puk, const char *newPin, const char *aid)
{
    RILC_REQUEST_WITH_ARG(supplyIccPukForApp, resp,
                          NULLSTR(puk),
                          NULLSTR(newPin),
                          NULLSTR(aid));
}

int RILC_supplyIccPin2(RILResponse *resp, const char *pin)
{
    RILC_REQUEST_WITH_ARG(supplyIccPin2, resp,
                          NULLSTR(pin));
}

int RILC_supplyIccPin2ForApp(RILResponse *resp, const char *pin, const char *aid)
{
    RILC_REQUEST_WITH_ARG(supplyIccPin2ForApp, resp,
                          NULLSTR(pin),
                          NULLSTR(aid));
}

int RILC_supplyIccPuk2(RILResponse *resp, const char *puk2, const char *newPin2)
{
    RILC_REQUEST_WITH_ARG(supplyIccPuk2, resp,
                          NULLSTR(puk2),
                          NULLSTR(newPin2));
}

int RILC_supplyIccPuk2ForApp(RILResponse *resp, const char *puk, const char *newPin2, const char *aid)
{
    RILC_REQUEST_WITH_ARG(supplyIccPuk2ForApp, resp,
                          NULLSTR(puk),
                          NULLSTR(newPin2),
                          NULLSTR(aid));
}

int RILC_changeIccPin(RILResponse *resp, const char *oldPin, const char *newPin)
{
    RILC_REQUEST_WITH_ARG(changeIccPin, resp,
                          NULLSTR(oldPin),
                          NULLSTR(newPin));
}

int RILC_changeIccPinForApp(RILResponse *resp, const char *oldPin, const char *newPin, const char *aid)
{
    RILC_REQUEST_WITH_ARG(changeIccPinForApp, resp,
                          NULLSTR(oldPin),
                          NULLSTR(newPin),
                          NULLSTR(aid));
}

int RILC_changeIccPin2(RILResponse *resp, const char *oldPin2, const char *newPin2)
{
    RILC_REQUEST_WITH_ARG(changeIccPin2, resp,
                          NULLSTR(oldPin2),
                          NULLSTR(newPin2));
}

int RILC_changeIccPin2ForApp(RILResponse *resp, const char *oldPin2, const char *newPin2, const char *aid)
{
    RILC_REQUEST_WITH_ARG(changeIccPin2ForApp, resp,
                          NULLSTR(oldPin2),
                          NULLSTR(newPin2),
                          NULLSTR(aid));
}

int RILC_changeBarringPassword(RILResponse *resp, const char *facility, const char *oldPwd, const char *newPwd)
{
    RILC_REQUEST_WITH_ARG(changeBarringPassword, resp,
                          NULLSTR(facility),
                          NULLSTR(oldPwd),
                          NULLSTR(newPwd));
}

int RILC_supplyNetworkDepersonalization(RILResponse *resp, const char *netpin)
{
    RILC_REQUEST_WITH_ARG(supplyNetworkDepersonalization, resp,
                          NULLSTR(netpin));
}

int RILC_getCurrentCalls(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getCurrentCalls, resp);
}

// __attribute_deprecated__ int getPDPContextList();

int RILC_getDataCallList(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getDataCallList, resp);
}

int RILC_dial(RILResponse *resp, const char *address, int clirMode)
{
    RILC_REQUEST_WITH_ARG(dial, resp,
                          NULLSTR(address),
                          clirMode);
}

int RILC_dial(RILResponse *resp, const char *address, int clirMode, RIL_UUS_Info *uusInfo)
{
    RILC_REQUEST_WITH_ARG(dial, resp,
                          NULLSTR(address),
                          clirMode,
                          uusInfo);
}

int RILC_getIMSI(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getIMSI, resp);
}

int RILC_getIMEI(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getIMEI, resp);
}

int RILC_getIMEISV(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getIMEISV, resp);
}

int RILC_hangupConnection(RILResponse *resp, int gsmIndex)
{
    RILC_REQUEST_WITH_ARG(hangupConnection, resp,
                          gsmIndex);
}

int RILC_hangupWaitingOrBackground(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(hangupWaitingOrBackground, resp);
}

int RILC_hangupForegroundResumeBackground(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(hangupForegroundResumeBackground, resp);
}

int RILC_switchWaitingOrHoldingAndActive(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(switchWaitingOrHoldingAndActive, resp);
}

int RILC_conference(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(conference, resp);
}

int RILC_setPreferredVoicePrivacy(RILResponse *resp, bool enable)
{
    RILC_REQUEST_WITH_ARG(setPreferredVoicePrivacy, resp,
                          enable);
}

int RILC_getPreferredVoicePrivacy(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getPreferredVoicePrivacy, resp);
}

int RILC_separateConnection(RILResponse *resp, int gsmIndex)
{
    RILC_REQUEST_WITH_ARG(separateConnection, resp,
                          gsmIndex);
}

int RILC_acceptCall(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(acceptCall, resp);
}

int RILC_rejectCall(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(rejectCall, resp);
}

int RILC_explicitCallTransfer(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(explicitCallTransfer, resp);
}

int RILC_getLastCallFailCause(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getLastCallFailCause, resp);
}

// __attribute_deprecated__ int getLastPdpFailCause();

int RILC_getLastDataCallFailCause(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getLastDataCallFailCause, resp);
}

int RILC_setMute(RILResponse *resp, bool enableMute)
{
    RILC_REQUEST_WITH_ARG(setMute, resp, enableMute);
}

int RILC_getMute(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getMute, resp);
}

int RILC_getSignalStrength(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getSignalStrength, resp);
}

int RILC_getVoiceRegistrationState(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getVoiceRegistrationState, resp);
}

int RILC_getDataRegistrationState(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getDataRegistrationState, resp);
}

int RILC_getOperator(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getOperator, resp);
}

int RILC_sendDtmf(RILResponse *resp, char c)
{
    RILC_REQUEST_WITH_ARG(sendDtmf, resp, c);
}

int RILC_startDtmf(RILResponse *resp, char c)
{
    RILC_REQUEST_WITH_ARG(startDtmf, resp, c);
}

int RILC_stopDtmf(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(stopDtmf, resp);
}

int RILC_sendBurstDtmf(RILResponse *resp, const char *dtmfString, int on, int off)
{
    RILC_REQUEST_WITH_ARG(sendBurstDtmf, resp,
                          NULLSTR(dtmfString),
                          on,
                          off);
}

int RILC_sendSMS(RILResponse *resp, const char *smscPDU, const char *pdu)
{
    RILC_REQUEST_WITH_ARG(sendSMS, resp,
                          NULLSTR(smscPDU),
                          NULLSTR(pdu));
}

// int sendCdmaSms(uint8_t *pdu);

int RILC_deleteSmsOnSim(RILResponse *resp, int index)
{
    RILC_REQUEST_WITH_ARG(deleteSmsOnSim, resp,
                          index);
}

int RILC_deleteSmsOnRuim(RILResponse *resp, int index)
{
    RILC_REQUEST_WITH_ARG(deleteSmsOnRuim, resp,
                          index);
}

int RILC_writeSmsToSim(RILResponse *resp, int status, const char *smsc, const char *pdu)
{
    RILC_REQUEST_WITH_ARG(writeSmsToSim, resp,
                          status,
                          NULLSTR(smsc),
                          NULLSTR(pdu));
}

int RILC_writeSmsToRuim(RILResponse *resp, int status, const char *pdu)
{
    RILC_REQUEST_WITH_ARG(writeSmsToRuim, resp,
                          status,
                          NULLSTR(pdu));
}

int RILC_setupDataCall(RILResponse *resp, RadioTech radioTechnology, const char *profile, const char *apn,
                       const char *user, const char *password, RadioAuth authType, RadioProtocol protocol)
{
    const char *ip_protocol[] = {
        [0] = "IP",
        [1] = "IPV6",
        [2] = "IPV4V6",
    };

    const char *proto = ip_protocol[protocol];
    RILC_REQUEST_WITH_ARG(setupDataCall, resp,
                          std::to_string(radioTechnology).c_str(),
                          NULLSTR(profile),
                          NULLSTR(apn),
                          NULLSTR(user),
                          NULLSTR(password),
                          std::to_string(authType).c_str(),
                          proto);
}

int RILC_deactivateDataCall(RILResponse *resp, int cid, int reason)
{
    RILC_REQUEST_WITH_ARG(deactivateDataCall, resp,
                          cid,
                          reason);
}

int RILC_setRadioPower(RILResponse *resp, bool on)
{
    RILC_REQUEST_WITH_ARG(setRadioPower, resp,
                          on);
}

int RILC_setSuppServiceNotifications(RILResponse *resp, bool enable)
{
    RILC_REQUEST_WITH_ARG(setSuppServiceNotifications, resp,
                          enable);
}

int RILC_acknowledgeLastIncomingGsmSms(RILResponse *resp, bool success, int cause)
{
    RILC_REQUEST_WITH_ARG(acknowledgeLastIncomingGsmSms, resp,
                          success,
                          cause);
}

int RILC_acknowledgeLastIncomingCdmaSms(RILResponse *resp, bool success, int cause)
{
    RILC_REQUEST_WITH_ARG(acknowledgeLastIncomingCdmaSms, resp,
                          success,
                          cause);
}

int RILC_acknowledgeIncomingGsmSmsWithPdu(RILResponse *resp, bool success, const char *ackPdu)
{
    RILC_REQUEST_WITH_ARG(acknowledgeIncomingGsmSmsWithPdu, resp,
                          success,
                          NULLSTR(ackPdu));
}

int RILC_iccIO(RILResponse *resp, int command, int fileid,
               const char *path, int p1, int p2, int p3,
               const char *data, const char *pin2)
{
    RILC_REQUEST_WITH_ARG(iccIO, resp,
                          command, fileid,
                          NULLSTR(path),
                          p1, p2, p3,
                          NULLSTR(data),
                          NULLSTR(pin2));
}

int RILC_getCLIR(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getCLIR, resp);
}

int RILC_setCLIR(RILResponse *resp, int clirMode)
{
    RILC_REQUEST_WITH_ARG(setCLIR, resp,
                          clirMode);
}

int RILC_queryCallWaiting(RILResponse *resp, int serviceClass)
{
    RILC_REQUEST_WITH_ARG(queryCallWaiting, resp,
                          serviceClass);
}

int RILC_setCallWaiting(RILResponse *resp, bool enable, int serviceClass)
{
    RILC_REQUEST_WITH_ARG(setCallWaiting, resp,
                          enable,
                          serviceClass);
}

int RILC_setNetworkSelectionModeAutomatic(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(setNetworkSelectionModeAutomatic, resp);
}

int RILC_setNetworkSelectionModeManual(RILResponse *resp, const char *operatorNumeric)
{
    RILC_REQUEST_WITH_ARG(setNetworkSelectionModeManual, resp,
                          NULLSTR(operatorNumeric));
}

int RILC_getNetworkSelectionMode(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getNetworkSelectionMode, resp);
}

int RILC_getAvailableNetworks(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getAvailableNetworks, resp);
}

int RILC_setCallForward(RILResponse *resp, int action, int cfReason, int serviceClass,
                        const char *number, int timeSeconds)
{
    RILC_REQUEST_WITH_ARG(setCallForward, resp,
                          action, cfReason,
                          serviceClass,
                          NULLSTR(number),
                          timeSeconds);
}

int RILC_queryCallForwardStatus(RILResponse *resp, int cfReason, int serviceClass,
                                const char *number)
{
    RILC_REQUEST_WITH_ARG(queryCallForwardStatus, resp,
                          cfReason,
                          serviceClass,
                          NULLSTR(number));
}

int RILC_queryCLIP(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(queryCLIP, resp);
}

int RILC_getBasebandVersion(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getBasebandVersion, resp);
}

int RILC_queryFacilityLock(RILResponse *resp, const char *facility, const char *password, int serviceClass)
{
    RILC_REQUEST_WITH_ARG(queryFacilityLock, resp,
                          NULLSTR(facility),
                          NULLSTR(password),
                          serviceClass);
}

int RILC_queryFacilityLockForApp(RILResponse *resp, const char *facility, const char *password, int serviceClass, const char *appId)
{
    RILC_REQUEST_WITH_ARG(queryFacilityLockForApp, resp,
                          NULLSTR(facility),
                          NULLSTR(password),
                          serviceClass,
                          NULLSTR(appId));
}

int RILC_setFacilityLock(RILResponse *resp, const char *facility, bool lockState, const char *password, int serviceClass)
{
    RILC_REQUEST_WITH_ARG(setFacilityLock, resp,
                          NULLSTR(facility),
                          lockState,
                          NULLSTR(password),
                          serviceClass);
}

int RILC_setFacilityLockForApp(RILResponse *resp, const char *facility, bool lockState, const char *password,
                               int serviceClass, const char *appId)
{
    RILC_REQUEST_WITH_ARG(setFacilityLockForApp, resp,
                          NULLSTR(facility),
                          lockState,
                          NULLSTR(password),
                          serviceClass,
                          NULLSTR(appId));
}

int RILC_sendUSSD(RILResponse *resp, const char *ussdString)
{
    RILC_REQUEST_WITH_ARG(sendUSSD, resp,
                          NULLSTR(ussdString));
}

// inherited javadoc suffices
int RILC_cancelPendingUssd(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(cancelPendingUssd, resp);
}

int RILC_resetRadio(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(resetRadio, resp);
}

int RILC_invokeOemRILRequestRaw(RILResponse *resp, uint8_t *data)
{
    // RILC_REQUEST_WITH_ARG(invokeOemRILRequestRaw, resp,
    //                       data);
    return 0;
}

int RILC_invokeOemRILRequestStrings(RILResponse *resp, int num, const char **strings)
{
    std::vector<std::string> vec;
    for (int i = 0; i < num; i++)
        vec.emplace_back(NULLSTR(strings[i]));

    RILC_REQUEST_WITH_ARG(invokeOemRILRequestStrings, resp,
                          vec);
}

int RILC_setBandMode(RILResponse *resp, int bandMode)
{
    RILC_REQUEST_WITH_ARG(setBandMode, resp,
                          bandMode);
}

int RILC_queryAvailableBandMode(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(queryAvailableBandMode, resp);
}

int RILC_sendTerminalResponse(RILResponse *resp, const char *contents)
{
    RILC_REQUEST_WITH_ARG(sendTerminalResponse, resp,
                          NULLSTR(contents));
}

int RILC_sendEnvelope(RILResponse *resp, const char *contents)
{
    RILC_REQUEST_WITH_ARG(sendEnvelope, resp,
                          NULLSTR(contents));
}

int RILC_sendEnvelopeWithStatus(RILResponse *resp, const char *contents)
{
    RILC_REQUEST_WITH_ARG(sendEnvelopeWithStatus, resp,
                          NULLSTR(contents));
}

int RILC_handleCallSetupRequestFromSim(RILResponse *resp, bool accept)
{
    RILC_REQUEST_WITH_ARG(setBandMode, resp,
                          accept);
}

int RILC_setPreferredNetworkType(RILResponse *resp, RadioTech networktype)
{
    RILC_REQUEST_WITH_ARG(setPreferredNetworkType, resp,
                          networktype);
}

int RILC_getPreferredNetworkType(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getPreferredNetworkType, resp);
}

int RILC_getNeighboringCids(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getNeighboringCids, resp);
}

int RILC_setLocationUpdates(RILResponse *resp, bool enable)
{
    RILC_REQUEST_WITH_ARG(setLocationUpdates, resp,
                          enable);
}

int RILC_getSmscAddress(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getSmscAddress, resp);
}

int RILC_setSmscAddress(RILResponse *resp, const char *address)
{
    RILC_REQUEST_WITH_ARG(setSmscAddress, resp,
                          NULLSTR(address));
}

int RILC_reportSmsMemoryStatus(RILResponse *resp, bool available)
{
    RILC_REQUEST_WITH_ARG(reportSmsMemoryStatus, resp,
                          available);
}

int RILC_reportStkServiceIsRunning(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(reportStkServiceIsRunning, resp);
}

int RILC_getGsmBroadcastConfig(RILResponse *resp)
{
    RILC_REQUEST_NO_ARG(getGsmBroadcastConfig, resp);
}

// int RILC_setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config)
// {
// }

int RILC_setGsmBroadcastActivation(RILResponse *resp, bool activate)
{
    RILC_REQUEST_WITH_ARG(setGsmBroadcastActivation, resp,
                          activate);
}
