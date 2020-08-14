#ifndef __RIL_REQUEST
#define __RIL_REQUEST

#include <mutex>

#include "ISubjectObserver.h"
#include "DeviceManager.h"
#include "parcel/parcel.h"
#include "ril_response.h"

#define RIL_MAX_BUFSIZE (1024 * 8)
class RilRequest final : public IObserver
{
private:
    /* class variables */
    static DeviceManager *mDeviceMgr;
    static int mGlobalRequestId;
    static bool mReady;

public:
    static std::mutex mGlobalLock;
    static const int RIL_MAX_COMMAND_BYTES = (8 * 1024);
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;

private:
    /* instance variables */
    RilResponse *mResponse;
    int mRequestId;
    int mCommandId;
    Parcel mParcel;

public:
    static RilRequest &instance();

    static RilRequest *obtain(int cid, RilResponse *);

    static bool init(const char *device);

    static bool uninit();

    static bool isReady();

    static void resetRequest();

public:
    explicit RilRequest();

    ~RilRequest();

    /* When get some message from serial, this function will be called */
    void update(void *data);

    void send(RilRequest *);

    std::string serialString();

    std::string requestToString();

    int get_requestid();

    int get_commandid();

private:
    void processUnsolicited(Parcel &);

    void processSolicited(Parcel &);

    /* RIL Requests */
private:
    int translateStatus(int status);

public:
    void getIccCardStatus(RilResponse *result);

    void supplyIccPin(std::string pin, RilResponse *result);

    void supplyIccPinForApp(std::string pin, std::string aid, RilResponse *result);

    void supplyIccPuk(std::string puk, std::string newPin, RilResponse *result);

    void supplyIccPukForApp(std::string puk, std::string newPin, std::string aid, RilResponse *result);

    void supplyIccPin2(std::string pin, RilResponse *result);

    void supplyIccPin2ForApp(std::string pin, std::string aid, RilResponse *result);

    void supplyIccPuk2(std::string puk2, std::string newPin2, RilResponse *result);

    void supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid, RilResponse *result);

    void changeIccPin(std::string oldPin, std::string newPin, RilResponse *result);

    void changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid, RilResponse *result);

    void changeIccPin2(std::string oldPin2, std::string newPin2, RilResponse *result);

    void changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid, RilResponse *result);

    void changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd, RilResponse *result);

    void supplyNetworkDepersonalization(std::string netpin, RilResponse *result);

    void getCurrentCalls(RilResponse *result);

    __attribute_deprecated__ void getPDPContextList(RilResponse *result);

    void getDataCallList(RilResponse *result);

    // void dial(std::string address, int clirMode, RilResponse *result);

    // void dial(std::string address, int clirMode, UUSInfo *uusInfo, RilResponse *result);

    void getIMSI(RilResponse *result);

    void getIMEI(RilResponse *result);

    void getIMEISV(RilResponse *result);

    void hangupConnection(int gsmIndex, RilResponse *result);

    void hangupWaitingOrBackground(RilResponse *result);

    void hangupForegroundResumeBackground(RilResponse *result);

    void switchWaitingOrHoldingAndActive(RilResponse *result);

    void conference(RilResponse *result);

    void setPreferredVoicePrivacy(bool enable, RilResponse *result);

    void getPreferredVoicePrivacy(RilResponse *result);

    void separateConnection(int gsmIndex, RilResponse *result);

    void acceptCall(RilResponse *result);

    void rejectCall(RilResponse *result);

    void explicitCallTransfer(RilResponse *result);

    void getLastCallFailCause(RilResponse *result);

    __attribute_deprecated__ void getLastPdpFailCause(RilResponse *result);

    void getLastDataCallFailCause(RilResponse *result);

    void setMute(bool enableMute, RilResponse *response);

    void getMute(RilResponse *response);

    void getSignalStrength(RilResponse *result);

    void getVoiceRegistrationState(RilResponse *result);

    void getDataRegistrationState(RilResponse *result);

    void getOperator(RilResponse *result);

    void sendDtmf(char c, RilResponse *result);

    void startDtmf(char c, RilResponse *result);

    void stopDtmf(RilResponse *result);

    void sendBurstDtmf(std::string dtmfString, int on, int off, RilResponse *result);

    void sendSMS(std::string smscPDU, std::string pdu, RilResponse *result);

    // void sendCdmaSms(uint8_t *pdu, RilResponse *result);

    void deleteSmsOnSim(int index, RilResponse *response);

    void deleteSmsOnRuim(int index, RilResponse *response);

    void writeSmsToSim(int status, std::string smsc, std::string pdu, RilResponse *response);

    void writeSmsToRuim(int status, std::string pdu, RilResponse *response);

    void setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
                       std::string user, std::string password, std::string authType, std::string protocol,
                       RilResponse *result);

    void deactivateDataCall(int cid, int reason, RilResponse *result);

    void setRadioPower(bool on, RilResponse *result);

    void setSuppServiceNotifications(bool enable, RilResponse *result);

    void acknowledgeLastIncomingGsmSms(bool success, int cause, RilResponse *result);

    void acknowledgeLastIncomingCdmaSms(bool success, int cause, RilResponse *result);

    void acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu, RilResponse *result);

    void iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
               std::string data, std::string pin2, RilResponse *result);

    void getCLIR(RilResponse *result);

    void setCLIR(int clirMode, RilResponse *result);

    void queryCallWaiting(int serviceClass, RilResponse *response);

    void setCallWaiting(bool enable, int serviceClass, RilResponse *response);

    void setNetworkSelectionModeAutomatic(RilResponse *response);

    void setNetworkSelectionModeManual(std::string operatorNumeric, RilResponse *response);

    void getNetworkSelectionMode(RilResponse *response);

    void getAvailableNetworks(RilResponse *response);

    void setCallForward(int action, int cfReason, int serviceClass,
                        std::string number, int timeSeconds, RilResponse *response);

    void queryCallForwardStatus(int cfReason, int serviceClass,
                                std::string number, RilResponse *response);

    void queryCLIP(RilResponse *response);

    void getBasebandVersion(RilResponse *response);

    void queryFacilityLock(std::string facility, std::string password, int serviceClass,
                           RilResponse *response);

    void queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId,
                                 RilResponse *response);

    void setFacilityLock(std::string facility, bool lockState, std::string password,
                         int serviceClass, RilResponse *response);

    void setFacilityLockForApp(std::string facility, bool lockState, std::string password,
                               int serviceClass, std::string appId, RilResponse *response);

    void sendUSSD(std::string ussdString, RilResponse *response);

    // inherited javadoc suffices
    void cancelPendingUssd(RilResponse *response);

    void resetRadio(RilResponse *result);

    // void invokeOemRilRequestRaw(uint8_t *data, RilResponse *response);

    // void invokeOemRilRequestStrings(std::string[] strings, RilResponse *response);

    void setBandMode(int bandMode, RilResponse *response);

    void queryAvailableBandMode(RilResponse *response);

    void sendTerminalResponse(std::string contents, RilResponse *response);

    void sendEnvelope(std::string contents, RilResponse *response);

    void sendEnvelopeWithStatus(std::string contents, RilResponse *response);

    void handleCallSetupRequestFromSim(bool accept, RilResponse *response);

    void setCurrentPreferredNetworkType();

    void setPreferredNetworkType(int networkType, RilResponse *response);

    void getPreferredNetworkType(RilResponse *response);

    void getNeighboringCids(RilResponse *response);

    void setLocationUpdates(bool enable, RilResponse *response);

    void getSmscAddress(RilResponse *result);

    void setSmscAddress(std::string address, RilResponse *result);

    void reportSmsMemoryStatus(bool available, RilResponse *result);

    void reportStkServiceIsRunning(RilResponse *result);

    void getGsmBroadcastConfig(RilResponse *response);

    // void setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config, RilResponse *response);

    void setGsmBroadcastActivation(bool activate, RilResponse *response);
};

typedef RilRequest RILREQUEST;

#endif //__RIL_REQUEST
