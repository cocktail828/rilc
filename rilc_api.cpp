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
    // ABORT_IF_ERROR(req.supplyIccPin("1234"));
    // ABORT_IF_ERROR(req.supplyIccPinForApp("1234", "2345"));
    // ABORT_IF_ERROR(req.supplyIccPuk(std::string puk, std::string newPin));
    // ABORT_IF_ERROR(req.supplyIccPukForApp(std::string puk, std::string newPin, std::string aid));
    // ABORT_IF_ERROR(req.supplyIccPin2(std::string pin));
    // ABORT_IF_ERROR(req.supplyIccPin2ForApp(std::string pin, std::string aid));
    // ABORT_IF_ERROR(req.supplyIccPuk2(std::string puk2, std::string newPin2));
    // ABORT_IF_ERROR(req.supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid));
    // ABORT_IF_ERROR(req.changeIccPin(std::string oldPin, std::string newPin));
    // ABORT_IF_ERROR(req.changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid));
    // ABORT_IF_ERROR(req.changeIccPin2(std::string oldPin2, std::string newPin2));
    // ABORT_IF_ERROR(req.changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid));
    // ABORT_IF_ERROR(req.changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd));
    // ABORT_IF_ERROR(req.supplyNetworkDepersonalization(""));
    // __attribute_deprecated__ void getPDPContextList();
    ABORT_IF_ERROR(req.dial("15510525846", 0));
    ABORT_IF_ERROR(req.dial("15510525846", 0, nullptr));
    // ABORT_IF_ERROR(req.hangupConnection(int gsmIndex));
    // ABORT_IF_ERROR(req.hangupWaitingOrBackground());
    // ABORT_IF_ERROR(req.hangupForegroundResumeBackground());
    // ABORT_IF_ERROR(req.switchWaitingOrHoldingAndActive());
    // ABORT_IF_ERROR(req.conference());
    // ABORT_IF_ERROR(req.setPreferredVoicePrivacy(bool enable));
    // ABORT_IF_ERROR(req.getPreferredVoicePrivacy());
    // ABORT_IF_ERROR(req.separateConnection(int gsmIndex));
    // ABORT_IF_ERROR(req.acceptCall());
    // ABORT_IF_ERROR(req.rejectCall());
    // ABORT_IF_ERROR(req.explicitCallTransfer());
    // ABORT_IF_ERROR(req.getLastCallFailCause());

    // // __attribute_deprecated__ void getLastPdpFailCause();
    // ABORT_IF_ERROR(req.setMute(bool enableMute));
    // ABORT_IF_ERROR(req.sendDtmf(char c));
    // ABORT_IF_ERROR(req.startDtmf(char c));
    // ABORT_IF_ERROR(req.sendBurstDtmf(std::string dtmfString, int on, int off));
    // ABORT_IF_ERROR(req.sendSMS(std::string smscPDU, std::string pdu));

    // ABORT_IF_ERROR(req.sendCdmaSms(uint8_t * pdu));
    // ABORT_IF_ERROR(req.deleteSmsOnSim(int index));
    // ABORT_IF_ERROR(req.deleteSmsOnRuim(int index));
    // ABORT_IF_ERROR(req.writeSmsToSim(int status, std::string smsc, std::string pdu));
    // ABORT_IF_ERROR(req.writeSmsToRuim(int status, std::string pdu));
    // ABORT_IF_ERROR(req.setupDataCall(std::string radioTechnology, std::string profile, std::string apn, std::string user, std::string password, std::string authType, std::string protocol);
    // ABORT_IF_ERROR(req.deactivateDataCall(int cid, int reason));
    // ABORT_IF_ERROR(req.setRadioPower(bool on));
    // ABORT_IF_ERROR(req.setSuppServiceNotifications(bool enable));
    // ABORT_IF_ERROR(req.acknowledgeLastIncomingGsmSms(bool success, int cause));
    // ABORT_IF_ERROR(req.acknowledgeLastIncomingCdmaSms(bool success, int cause));
    // ABORT_IF_ERROR(req.acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu));
    // ABORT_IF_ERROR(req.iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,std::string data, std::string pin2);
    // ABORT_IF_ERROR(req.setCLIR(int clirMode));
    // ABORT_IF_ERROR(req.queryCallWaiting(int serviceClass));
    // ABORT_IF_ERROR(req.setCallWaiting(bool enable, int serviceClass));
    // ABORT_IF_ERROR(req.setNetworkSelectionModeManual(std::string operatorNumeric));
    // ABORT_IF_ERROR(req.setCallForward(int action, int cfReason, int serviceClass, std::string number, int timeSeconds);
    // ABORT_IF_ERROR(req.queryCallForwardStatus(int cfReason, int serviceClass, std::string number);
    // ABORT_IF_ERROR(req.queryFacilityLock(std::string facility, std::string password, int serviceClass));
    // ABORT_IF_ERROR(req.queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId));
    // ABORT_IF_ERROR(req.setFacilityLock(std::string facility, bool lockState, std::string password, int serviceClass);
    // ABORT_IF_ERROR(req.setFacilityLockForApp(std::string facility, bool lockState, std::string password, int serviceClass, std::string appId);
    // ABORT_IF_ERROR(req.sendUSSD(std::string ussdString));
    // ABORT_IF_ERROR(req.invokeOemRILRequestRaw(uint8_t *data));
    // ABORT_IF_ERROR(req.invokeOemRILRequestStrings(std::string[] strings));
    // ABORT_IF_ERROR(req.setBandMode(int bandMode));
    // ABORT_IF_ERROR(req.sendTerminalResponse(std::string contents));
    // ABORT_IF_ERROR(req.sendEnvelope(std::string contents));
    // ABORT_IF_ERROR(req.sendEnvelopeWithStatus(std::string contents));
    // ABORT_IF_ERROR(req.handleCallSetupRequestFromSim(bool accept));
    // ABORT_IF_ERROR(req.setPreferredNetworkType(int networkType));
    // ABORT_IF_ERROR(req.setLocationUpdates(bool enable));
    // ABORT_IF_ERROR(req.setSmscAddress(std::string address));
    // ABORT_IF_ERROR(req.reportSmsMemoryStatus(bool available));
    // ABORT_IF_ERROR(req.setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config));
    // ABORT_IF_ERROR(req.setGsmBroadcastActivation(bool activate));
}
