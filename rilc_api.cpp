#include <thread>
#include <chrono>

#include "ril_request.h"
#include "logger.h"

int RILC_init(const char *device)
{
    const int max_try = 30;
    int try_time = 0;

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
        LOGI << "init seccussfully " << ENDL;
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

int RILC_requestIMEI()
{
    RILRequest req;
    req.getIMEI();

    return 0;
}

int RILC_requestIMSI()
{
    RILRequest req;
    req.getIMSI();

    return 0;
}

#define ABORT_IF_ERROR(l)                                                      \
    do                                                                         \
    {                                                                          \
        req.recycle();                                                         \
        l;                                                                     \
        if (req.mResponse.getError() || req.mResponse.getCommandId() == 0)     \
        {                                                                      \
            LOGE << "OOPS: request " << req.getCommandId() << " fail" << ENDL; \
            abort();                                                           \
        }                                                                      \
    } while (0)

void TEST_VOID_REQ()
{
    RILRequest req;
    /**
     * request without parameters
     */

    ABORT_IF_ERROR(req.getIccCardStatus());
    ABORT_IF_ERROR(req.getCurrentCalls());
    ABORT_IF_ERROR(req.getDataCallList());
    ABORT_IF_ERROR(req.getIMEI());
    ABORT_IF_ERROR(req.getIMEISV());
    ABORT_IF_ERROR(req.getLastDataCallFailCause());
    ABORT_IF_ERROR(req.getMute());
    ABORT_IF_ERROR(req.getSignalStrength());
    ABORT_IF_ERROR(req.getVoiceRegistrationState());
    ABORT_IF_ERROR(req.getDataRegistrationState());
    ABORT_IF_ERROR(req.getOperator());
    ABORT_IF_ERROR(req.stopDtmf());
    ABORT_IF_ERROR(req.getCLIR());
    ABORT_IF_ERROR(req.setNetworkSelectionModeAutomatic());
    ABORT_IF_ERROR(req.getNetworkSelectionMode());
    ABORT_IF_ERROR(req.getAvailableNetworks());
    ABORT_IF_ERROR(req.queryCLIP());
    ABORT_IF_ERROR(req.getBasebandVersion());
    ABORT_IF_ERROR(req.cancelPendingUssd());
    ABORT_IF_ERROR(req.resetRadio());
    ABORT_IF_ERROR(req.queryAvailableBandMode());
    ABORT_IF_ERROR(req.getPreferredNetworkType());
    ABORT_IF_ERROR(req.getNeighboringCids());
    ABORT_IF_ERROR(req.getSmscAddress());
    ABORT_IF_ERROR(req.reportStkServiceIsRunning());
    ABORT_IF_ERROR(req.getGsmBroadcastConfig());
    ABORT_IF_ERROR(req.getIMSI()); // --------- error
}

void RILC_TEST_REQ()
{
    // TEST_VOID_REQ();

    RILRequest req;
    /**
     * request with parameters
     */
    // req.supplyIccPin("1234");
    // req.supplyIccPinForApp("1234", "2345");
    // req.supplyIccPuk(std::string puk, std::string newPin);
    // req.supplyIccPukForApp(std::string puk, std::string newPin, std::string aid);
    // req.supplyIccPin2(std::string pin);
    // req.supplyIccPin2ForApp(std::string pin, std::string aid);
    // req.supplyIccPuk2(std::string puk2, std::string newPin2);
    // req.supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid);
    // req.changeIccPin(std::string oldPin, std::string newPin);
    // req.changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid);
    // req.changeIccPin2(std::string oldPin2, std::string newPin2);
    // req.changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid);
    // req.changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd);
    // req.supplyNetworkDepersonalization("");
    // __attribute_deprecated__ void getPDPContextList();
    ABORT_IF_ERROR(req.dial("15510525846", 0));
    // // req.dial(std::string address, int clirMode, UUSInfo *uusInfo);
    // req.hangupConnection(int gsmIndex);
    // req.hangupWaitingOrBackground();
    // req.hangupForegroundResumeBackground();
    // req.switchWaitingOrHoldingAndActive();
    // req.conference();
    // req.setPreferredVoicePrivacy(bool enable);
    // req.getPreferredVoicePrivacy();
    // req.separateConnection(int gsmIndex);
    // req.acceptCall();
    // req.rejectCall();
    // req.explicitCallTransfer();
    // req.getLastCallFailCause();

    // __attribute_deprecated__ void getLastPdpFailCause();
    // req.setMute(bool enableMute);
    // req.sendDtmf(char c);
    // req.startDtmf(char c);
    // req.sendBurstDtmf(std::string dtmfString, int on, int off);
    // req.sendSMS(std::string smscPDU, std::string pdu);

    // // req.sendCdmaSms(uint8_t *pdu);
    // req.deleteSmsOnSim(int index);
    // req.deleteSmsOnRuim(int index);
    // req.writeSmsToSim(int status, std::string smsc, std::string pdu);
    // req.writeSmsToRuim(int status, std::string pdu);
    // req.setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
    //                    std::string user, std::string password, std::string authType, std::string protocol);
    // req.deactivateDataCall(int cid, int reason);
    // req.setRadioPower(bool on);
    // req.setSuppServiceNotifications(bool enable);
    // req.acknowledgeLastIncomingGsmSms(bool success, int cause);
    // req.acknowledgeLastIncomingCdmaSms(bool success, int cause);
    // req.acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu);
    // req.iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
    //            std::string data, std::string pin2);
    // req.setCLIR(int clirMode);
    // req.queryCallWaiting(int serviceClass);
    // req.setCallWaiting(bool enable, int serviceClass);
    // req.setNetworkSelectionModeManual(std::string operatorNumeric);
    // req.setCallForward(int action, int cfReason, int serviceClass,
    //                     std::string number, int timeSeconds);
    // req.queryCallForwardStatus(int cfReason, int serviceClass,
    //                             std::string number);
    // req.queryFacilityLock(std::string facility, std::string password, int serviceClass);
    // req.queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId);
    // req.setFacilityLock(std::string facility, bool lockState, std::string password,
    //                      int serviceClass);
    // req.setFacilityLockForApp(std::string facility, bool lockState, std::string password,
    //                            int serviceClass, std::string appId);
    // req.sendUSSD(std::string ussdString);
    // // req.invokeOemRILRequestRaw(uint8_t *data);
    // // req.invokeOemRILRequestStrings(std::string[] strings);
    // req.setBandMode(int bandMode);
    // req.sendTerminalResponse(std::string contents);
    // req.sendEnvelope(std::string contents);
    // req.sendEnvelopeWithStatus(std::string contents);
    // req.handleCallSetupRequestFromSim(bool accept);
    // req.setPreferredNetworkType(int networkType);
    // req.setLocationUpdates(bool enable);
    // req.setSmscAddress(std::string address);
    // req.reportSmsMemoryStatus(bool available);
    // req.setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config);
    // req.setGsmBroadcastActivation(bool activate);
    return;
}
