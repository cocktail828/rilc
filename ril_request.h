#ifndef __RIL_REQUEST
#define __RIL_REQUEST

#include <mutex>

#include "ISubjectObserver.h"
#include "DeviceManager.h"
#include "parcel/parcel.h"
#include "rilc_interface.h"
#include "ril/ril.h"

#ifndef __attribute_deprecated__
#define __attribute_deprecated__ __attribute__((deprecated))
#endif

#define RIL_MAX_BUFSIZE (1024 * 8)
class RILRequest final : public IObserver
{
private:
    /* class variables */
    static DeviceManager *mDeviceMgr;
    static int mGlobalRequestId;
    static bool mReady;
    static RILResponse mUnsocilitedResponse;

public:
    static std::mutex mGlobalLock;
    static const int RIL_MAX_COMMAND_BYTES = (8 * 1024);
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;

private:
    /* instance variables */
    std::mutex mRequestLock;
    std::condition_variable mRequestCond;

    /* transication id, increasing */
    int mRequestId;

    /* command id of the specified request */
    int mCommandId;

    Parcel mParcel;

public:
    /* response info */
    RILResponse *mResponse;

public:
    static RILRequest &instance();

    static bool init(const char *device);

    static bool uninit();

    static bool isReady();

    static void resetGlobalRequest();

    static void processUnsolicited(Parcel &);

    static void processSolicited(RILRequest *rr, Parcel &);

    static bool blockSend(RILRequest *);
    /**
     * the request must be an pointer
     * or coredump or other unexpected result will be get
     */
    static bool nonblockSend(RILRequest *);

public:
    explicit RILRequest();
    explicit RILRequest(RILResponse *resp);

    ~RILRequest();

    void obtain(int cid);

    /* When get some message from serial, this function will be called */
    void update(Parcel &);

    int getRequestId();

    int getCommandId();

    void recycle();

    /* RIL Requests */
private:
    int translateStatus(int status);

public:
    int getIccCardStatus();

    int supplyIccPin(std::string pin);

    int supplyIccPinForApp(std::string pin, std::string aid);

    int supplyIccPuk(std::string puk, std::string newPin);

    int supplyIccPukForApp(std::string puk, std::string newPin, std::string aid);

    int supplyIccPin2(std::string pin);

    int supplyIccPin2ForApp(std::string pin, std::string aid);

    int supplyIccPuk2(std::string puk2, std::string newPin2);

    int supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid);

    int changeIccPin(std::string oldPin, std::string newPin);

    int changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid);

    int changeIccPin2(std::string oldPin2, std::string newPin2);

    int changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid);

    int changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd);

    int supplyNetworkDepersonalization(std::string netpin);

    int getCurrentCalls();

    __attribute_deprecated__ int getPDPContextList();

    int getDataCallList();

    int dial(std::string address, int clirMode);

    int dial(std::string address, int clirMode, RIL_UUS_Info *uusInfo);

    int getIMSI();

    int getIMEI();

    int getIMEISV();

    int hangupConnection(int gsmIndex);

    int hangupWaitingOrBackground();

    int hangupForegroundResumeBackground();

    int switchWaitingOrHoldingAndActive();

    int conference();

    int setPreferredVoicePrivacy(bool enable);

    int getPreferredVoicePrivacy();

    int separateConnection(int gsmIndex);

    int acceptCall();

    int rejectCall();

    int explicitCallTransfer();

    int getLastCallFailCause();

    __attribute_deprecated__ int getLastPdpFailCause();

    int getLastDataCallFailCause();

    int setMute(bool enableMute);

    int getMute();

    int getSignalStrength();

    int getVoiceRegistrationState();

    int getDataRegistrationState();

    int getOperator();

    int sendDtmf(char c);

    int startDtmf(char c);

    int stopDtmf();

    int sendBurstDtmf(std::string dtmfString, int on, int off);

    int sendSMS(std::string smscPDU, std::string pdu);

    // int sendCdmaSms(uint8_t *pdu);

    int deleteSmsOnSim(int index);

    int deleteSmsOnRuim(int index);

    int writeSmsToSim(int status, std::string smsc, std::string pdu);

    int writeSmsToRuim(int status, std::string pdu);

    int setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
                      std::string user, std::string password, std::string authType, std::string protocol);

    int deactivateDataCall(int cid, int reason);

    int setRadioPower(bool on);

    int setSuppServiceNotifications(bool enable);

    int acknowledgeLastIncomingGsmSms(bool success, int cause);

    int acknowledgeLastIncomingCdmaSms(bool success, int cause);

    int acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu);

    int iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
              std::string data, std::string pin2);

    int getCLIR();

    int setCLIR(int clirMode);

    int queryCallWaiting(int serviceClass);

    int setCallWaiting(bool enable, int serviceClass);

    int setNetworkSelectionModeAutomatic();

    int setNetworkSelectionModeManual(std::string operatorNumeric);

    int getNetworkSelectionMode();

    int getAvailableNetworks();

    int setCallForward(int action, int cfReason, int serviceClass,
                       std::string number, int timeSeconds);

    int queryCallForwardStatus(int cfReason, int serviceClass,
                               std::string number);

    int queryCLIP();

    int getBasebandVersion();

    int queryFacilityLock(std::string facility, std::string password, int serviceClass);

    int queryFacilityLockForApp(std::string facility, std::string password, int serviceClass, std::string appId);

    int setFacilityLock(std::string facility, bool lockState, std::string password,
                        int serviceClass);

    int setFacilityLockForApp(std::string facility, bool lockState, std::string password,
                              int serviceClass, std::string appId);

    int sendUSSD(std::string ussdString);

    // inherited javadoc suffices
    int cancelPendingUssd();

    int resetRadio();

    // int invokeOemRILRequestRaw(uint8_t *data);

    int invokeOemRILRequestStrings(std::vector<std::string> strings);

    int setBandMode(int bandMode);

    int queryAvailableBandMode();

    int sendTerminalResponse(std::string contents);

    int sendEnvelope(std::string contents);

    int sendEnvelopeWithStatus(std::string contents);

    int handleCallSetupRequestFromSim(bool accept);

    int setPreferredNetworkType(int networkType);

    int getPreferredNetworkType();

    int getNeighboringCids();

    int setLocationUpdates(bool enable);

    int getSmscAddress();

    int setSmscAddress(std::string address);

    int reportSmsMemoryStatus(bool available);

    int reportStkServiceIsRunning();

    int getGsmBroadcastConfig();

    // int setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config);

    int setGsmBroadcastActivation(bool activate);
};

typedef RILRequest RILREQUEST;

#endif //__RIL_REQUEST
