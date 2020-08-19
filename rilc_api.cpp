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

void RILC_TEST_REQ()
{
    RILRequest req;

    // req.getIccCardStatus(); // android ok
    // req.supplyIccPin("123");
    // req.supplyIccPinForApp("123", "234");
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
    // req.supplyNetworkDepersonalization(""); // android ok
    // req.getCurrentCalls();

    // __attribute_deprecated__ void getPDPContextList();
    // req.getDataCallList();

    // // req.dial(std::string address, int clirMode);

    // // req.dial(std::string address, int clirMode, UUSInfo *uusInfo);
    req.getIMSI();        // Android ok
    req.recycle();
    req.getIMEI();        // Android ok
    req.recycle();
    req.getIMEISV();        // Android ok
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
    // req.getLastDataCallFailCause();
    // req.setMute(bool enableMute);
    // req.getMute();
    // req.getSignalStrength();
    // req.getVoiceRegistrationState();
    // req.getDataRegistrationState();
    // req.getOperator();
    // req.sendDtmf(char c);
    // req.startDtmf(char c);
    // req.stopDtmf();
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
    // req.getCLIR();
    // req.setCLIR(int clirMode);
    // req.queryCallWaiting(int serviceClass);
    // req.setCallWaiting(bool enable, int serviceClass);
    // req.setNetworkSelectionModeAutomatic();
    // req.setNetworkSelectionModeManual(std::string operatorNumeric);
    // req.getNetworkSelectionMode();
    // req.getAvailableNetworks();
    // req.setCallForward(int action, int cfReason, int serviceClass,
    //                     std::string number, int timeSeconds);
    // req.queryCallForwardStatus(int cfReason, int serviceClass,
    //                             std::string number);
    // req.queryCLIP();
    // req.getBasebandVersion();
    // req.queryFacilityLock(std::string facility, std::string password, int serviceClass);
    // req.queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId);
    // req.setFacilityLock(std::string facility, bool lockState, std::string password,
    //                      int serviceClass);
    // req.setFacilityLockForApp(std::string facility, bool lockState, std::string password,
    //                            int serviceClass, std::string appId);
    // req.sendUSSD(std::string ussdString);

    // // inherited javadoc suffice
    // req.cancelPendingUssd();
    // req.resetRadio();

    // // req.invokeOemRILRequestRaw(uint8_t *data);

    // // req.invokeOemRILRequestStrings(std::string[] strings);
    // req.setBandMode(int bandMode);
    // req.queryAvailableBandMode();
    // req.sendTerminalResponse(std::string contents);
    // req.sendEnvelope(std::string contents);
    // req.sendEnvelopeWithStatus(std::string contents);
    // req.handleCallSetupRequestFromSim(bool accept);
    // req.setCurrentPreferredNetworkType();
    // req.setPreferredNetworkType(int networkType);
    // req.getPreferredNetworkType();
    // req.getNeighboringCids();
    // req.setLocationUpdates(bool enable);
    // req.getSmscAddress();
    // req.setSmscAddress(std::string address);
    // req.reportSmsMemoryStatus(bool available);
    // req.reportStkServiceIsRunning();
    // req.getGsmBroadcastConfig();

    // // req.setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config);
    // req.setGsmBroadcastActivation(bool activate);
    return;
}