#ifndef __RIL_REQUEST
#define __RIL_REQUEST

#include <mutex>

#include "ISubjectObserver.h"
#include "DeviceManager.h"
#include "parcel/parcel.h"

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
    std::mutex mRequestLock;
    std::condition_variable mRequestcond;

    /* transication id, increasing */
    int mRequestId;

    /* command id of the specified request */
    int mCommandId;
    Parcel mParcel;

public:
    static RilRequest &instance();

    static bool init(const char *device);

    static bool uninit();

    static bool isReady();

    static void resetRequest();

    static bool send(RilRequest *);

public:
    explicit RilRequest();

    ~RilRequest();

    void obtain(int cid);

    /* When get some message from serial, this function will be called */
    void update(Parcel &);

    int get_requestid();

    int get_commandid();

public:
    static void processUnsolicited(Parcel &);

    void processSolicited(Parcel &);

    /* RIL Requests */
private:
    int translateStatus(int status);

public:
    void getIccCardStatus();

    void supplyIccPin(std::string pin);

    void supplyIccPinForApp(std::string pin, std::string aid);

    void supplyIccPuk(std::string puk, std::string newPin);

    void supplyIccPukForApp(std::string puk, std::string newPin, std::string aid);

    void supplyIccPin2(std::string pin);

    void supplyIccPin2ForApp(std::string pin, std::string aid);

    void supplyIccPuk2(std::string puk2, std::string newPin2);

    void supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid);

    void changeIccPin(std::string oldPin, std::string newPin);

    void changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid);

    void changeIccPin2(std::string oldPin2, std::string newPin2);

    void changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid);

    void changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd);

    void supplyNetworkDepersonalization(std::string netpin);

    void getCurrentCalls();

    __attribute_deprecated__ void getPDPContextList();

    void getDataCallList();

    // void dial(std::string address, int clirMode);

    // void dial(std::string address, int clirMode, UUSInfo *uusInfo);

    void getIMSI();

    void getIMEI();

    void getIMEISV();

    void hangupConnection(int gsmIndex);

    void hangupWaitingOrBackground();

    void hangupForegroundResumeBackground();

    void switchWaitingOrHoldingAndActive();

    void conference();

    void setPreferredVoicePrivacy(bool enable);

    void getPreferredVoicePrivacy();

    void separateConnection(int gsmIndex);

    void acceptCall();

    void rejectCall();

    void explicitCallTransfer();

    void getLastCallFailCause();

    __attribute_deprecated__ void getLastPdpFailCause();

    void getLastDataCallFailCause();

    void setMute(bool enableMute);

    void getMute();

    void getSignalStrength();

    void getVoiceRegistrationState();

    void getDataRegistrationState();

    void getOperator();

    void sendDtmf(char c);

    void startDtmf(char c);

    void stopDtmf();

    void sendBurstDtmf(std::string dtmfString, int on, int off);

    void sendSMS(std::string smscPDU, std::string pdu);

    // void sendCdmaSms(uint8_t *pdu);

    void deleteSmsOnSim(int index);

    void deleteSmsOnRuim(int index);

    void writeSmsToSim(int status, std::string smsc, std::string pdu);

    void writeSmsToRuim(int status, std::string pdu);

    void setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
                       std::string user, std::string password, std::string authType, std::string protocol);

    void deactivateDataCall(int cid, int reason);

    void setRadioPower(bool on);

    void setSuppServiceNotifications(bool enable);

    void acknowledgeLastIncomingGsmSms(bool success, int cause);

    void acknowledgeLastIncomingCdmaSms(bool success, int cause);

    void acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu);

    void iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
               std::string data, std::string pin2);

    void getCLIR();

    void setCLIR(int clirMode);

    void queryCallWaiting(int serviceClass);

    void setCallWaiting(bool enable, int serviceClass);

    void setNetworkSelectionModeAutomatic();

    void setNetworkSelectionModeManual(std::string operatorNumeric);

    void getNetworkSelectionMode();

    void getAvailableNetworks();

    void setCallForward(int action, int cfReason, int serviceClass,
                        std::string number, int timeSeconds);

    void queryCallForwardStatus(int cfReason, int serviceClass,
                                std::string number);

    void queryCLIP();

    void getBasebandVersion();

    void queryFacilityLock(std::string facility, std::string password, int serviceClass);

    void queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId);

    void setFacilityLock(std::string facility, bool lockState, std::string password,
                         int serviceClass);

    void setFacilityLockForApp(std::string facility, bool lockState, std::string password,
                               int serviceClass, std::string appId);

    void sendUSSD(std::string ussdString);

    // inherited javadoc suffices
    void cancelPendingUssd();

    void resetRadio();

    // void invokeOemRilRequestRaw(uint8_t *data);

    // void invokeOemRilRequestStrings(std::string[] strings);

    void setBandMode(int bandMode);

    void queryAvailableBandMode();

    void sendTerminalResponse(std::string contents);

    void sendEnvelope(std::string contents);

    void sendEnvelopeWithStatus(std::string contents);

    void handleCallSetupRequestFromSim(bool accept);

    void setCurrentPreferredNetworkType();

    void setPreferredNetworkType(int networkType);

    void getPreferredNetworkType();

    void getNeighboringCids();

    void setLocationUpdates(bool enable);

    void getSmscAddress();

    void setSmscAddress(std::string address);

    void reportSmsMemoryStatus(bool available);

    void reportStkServiceIsRunning();

    void getGsmBroadcastConfig();

    // void setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config);

    void setGsmBroadcastActivation(bool activate);
};

typedef RilRequest RILREQUEST;

#endif //__RIL_REQUEST
