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
    RilRequest req;
    req.getIMEI();

    return 0;
}

int RILC_requestIMSI()
{
    RilRequest req;
    req.getIMSI();

    return 0;
}

void RILC_TEST_REQ()
{
    RilRequest req;

    req.getIccCardStatus();
    // req.supplyIccPin(std::string pin);
    // void supplyIccPinForApp(std::string pin, std::string aid);
    // void supplyIccPuk(std::string puk, std::string newPin);
    // void supplyIccPukForApp(std::string puk, std::string newPin, std::string aid);
    // void supplyIccPin2(std::string pin);
    // void supplyIccPin2ForApp(std::string pin, std::string aid);
    // void supplyIccPuk2(std::string puk2, std::string newPin2);
    // void supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid);
    // void changeIccPin(std::string oldPin, std::string newPin);
    // void changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid);
    // void changeIccPin2(std::string oldPin2, std::string newPin2);
    // void changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid);
    // void changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd);
    // void supplyNetworkDepersonalization(std::string netpin);
    // void getCurrentCalls();

    // __attribute_deprecated__ void getPDPContextList();
    // void getDataCallList();

    // // void dial(std::string address, int clirMode);

    // // void dial(std::string address, int clirMode, UUSInfo *uusInfo);
    // void getIMSI();
    // void getIMEI();
    // void getIMEISV();
    // void hangupConnection(int gsmIndex);
    // void hangupWaitingOrBackground();
    // void hangupForegroundResumeBackground();
    // void switchWaitingOrHoldingAndActive();
    // void conference();
    // void setPreferredVoicePrivacy(bool enable);
    // void getPreferredVoicePrivacy();
    // void separateConnection(int gsmIndex);
    // void acceptCall();
    // void rejectCall();
    // void explicitCallTransfer();
    // void getLastCallFailCause();

    // __attribute_deprecated__ void getLastPdpFailCause();
    // void getLastDataCallFailCause();
    // void setMute(bool enableMute);
    // void getMute();
    // void getSignalStrength();
    // void getVoiceRegistrationState();
    // void getDataRegistrationState();
    // void getOperator();
    // void sendDtmf(char c);
    // void startDtmf(char c);
    // void stopDtmf();
    // void sendBurstDtmf(std::string dtmfString, int on, int off);
    // void sendSMS(std::string smscPDU, std::string pdu);

    // // void sendCdmaSms(uint8_t *pdu);
    // void deleteSmsOnSim(int index);
    // void deleteSmsOnRuim(int index);
    // void writeSmsToSim(int status, std::string smsc, std::string pdu);
    // void writeSmsToRuim(int status, std::string pdu);
    // void setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
    //                    std::string user, std::string password, std::string authType, std::string protocol);
    // void deactivateDataCall(int cid, int reason);
    // void setRadioPower(bool on);
    // void setSuppServiceNotifications(bool enable);
    // void acknowledgeLastIncomingGsmSms(bool success, int cause);
    // void acknowledgeLastIncomingCdmaSms(bool success, int cause);
    // void acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu);
    // void iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
    //            std::string data, std::string pin2);
    // void getCLIR();
    // void setCLIR(int clirMode);
    // void queryCallWaiting(int serviceClass);
    // void setCallWaiting(bool enable, int serviceClass);
    // void setNetworkSelectionModeAutomatic();
    // void setNetworkSelectionModeManual(std::string operatorNumeric);
    // void getNetworkSelectionMode();
    // void getAvailableNetworks();
    // void setCallForward(int action, int cfReason, int serviceClass,
    //                     std::string number, int timeSeconds);
    // void queryCallForwardStatus(int cfReason, int serviceClass,
    //                             std::string number);
    // void queryCLIP();
    // void getBasebandVersion();
    // void queryFacilityLock(std::string facility, std::string password, int serviceClass);
    // void queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId);
    // void setFacilityLock(std::string facility, bool lockState, std::string password,
    //                      int serviceClass);
    // void setFacilityLockForApp(std::string facility, bool lockState, std::string password,
    //                            int serviceClass, std::string appId);
    // void sendUSSD(std::string ussdString);

    // // inherited javadoc suffice
    // void cancelPendingUssd();
    // void resetRadio();

    // // void invokeOemRilRequestRaw(uint8_t *data);

    // // void invokeOemRilRequestStrings(std::string[] strings);
    // void setBandMode(int bandMode);
    // void queryAvailableBandMode();
    // void sendTerminalResponse(std::string contents);
    // void sendEnvelope(std::string contents);
    // void sendEnvelopeWithStatus(std::string contents);
    // void handleCallSetupRequestFromSim(bool accept);
    // void setCurrentPreferredNetworkType();
    // void setPreferredNetworkType(int networkType);
    // void getPreferredNetworkType();
    // void getNeighboringCids();
    // void setLocationUpdates(bool enable);
    // void getSmscAddress();
    // void setSmscAddress(std::string address);
    // void reportSmsMemoryStatus(bool available);
    // void reportStkServiceIsRunning();
    // void getGsmBroadcastConfig();

    // // void setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config);
    // void setGsmBroadcastActivation(bool activate);
    return;
}