# rilc
A simple SDK writen in c++, that can communicate with RILD of Android

## Framework

### DeviceManager

`DeviceManager` will manager the ttydevice/socket. Anyone that will be used for communicate with RILD.

```
class DeviceManager final : public ISubject
{
    static const int RESPONSE_SOLICITED = 0;
    static const int RESPONSE_UNSOLICITED = 1;
...
};
```

`DeviceManager` will start a new thread and polling any response via `epoll` from the file handle, that is managed. If any response (socilited/unsocilited) message was received, `DeviceManager` will call `processResponse` to notify the observer.



## RILRequest
Now, rilc support almost all standard request of Android(7). Both socilited/unsocilited response will be normally and peacefully processed!
User can perform any request, just after call `RILC_init`and do cleanup `RILC_uninit`.
Almost all the API has been tested on Android.
```c++

int RILC_init(const char *device);

/**
 * uninit rilc, stop polling
 * return:
 *  0 for some error
 *  1 for success
 */
int RILC_uninit();

/***********************************************************/
/***************** RILC UNSOCILITED PROCESSERS *************/
/***********************************************************/
void rilc_unsocilited_register(int cmdid, void (*cb)(RILResponse *));
void rilc_unsocilited_deregister(int cmdid);

/***********************************************************/
/***************** RILC STANDARD REQUESTS ******************/
/***********************************************************/
/**
 * NOTICE:
 * Refer to ril.h for more details
 */
int RILC_getIccCardStatus(RILResponse *resp);
int RILC_supplyIccPin(RILResponse *resp, const char *pin);
int RILC_supplyIccPinForApp(RILResponse *resp, const char *pin, const char *aid);
int RILC_supplyIccPuk(RILResponse *resp, const char *puk, const char *newPin);
int RILC_supplyIccPukForApp(RILResponse *resp, const char *puk, const char *newPin, const char *aid);
int RILC_supplyIccPin2(RILResponse *resp, const char *pin);
int RILC_supplyIccPin2ForApp(RILResponse *resp, const char *pin, const char *aid);
int RILC_supplyIccPuk2(RILResponse *resp, const char *puk2, const char *newPin2);
int RILC_supplyIccPuk2ForApp(RILResponse *resp, const char *puk, const char *newPin2, const char *aid);
int RILC_changeIccPin(RILResponse *resp, const char *oldPin, const char *newPin);
int RILC_changeIccPinForApp(RILResponse *resp, const char *oldPin, const char *newPin, const char *aid);
int RILC_changeIccPin2(RILResponse *resp, const char *oldPin2, const char *newPin2);
int RILC_changeIccPin2ForApp(RILResponse *resp, const char *oldPin2, const char *newPin2, const char *aid);
int RILC_changeBarringPassword(RILResponse *resp, const char *facility, const char *oldPwd, const char *newPwd);
int RILC_supplyNetworkDepersonalization(RILResponse *resp, const char *netpin);
int RILC_getCurrentCalls(RILResponse *resp);

// __attribute_deprecated__ int getPDPContextList();

int RILC_getDataCallList(RILResponse *resp);
int RILC_dial(RILResponse *resp, const char *address, int clirMode);
int RILC_dial(RILResponse *resp, const char *address, int clirMode, RIL_UUS_Info *uusInfo);
int RILC_getIMSI(RILResponse *resp);
int RILC_getIMEI(RILResponse *resp);
int RILC_getIMEISV(RILResponse *resp);
int RILC_hangupConnection(RILResponse *resp, int gsmIndex);
int RILC_hangupWaitingOrBackground(RILResponse *resp);
int RILC_hangupForegroundResumeBackground(RILResponse *resp);
int RILC_switchWaitingOrHoldingAndActive(RILResponse *resp);
int RILC_conference(RILResponse *resp);
int RILC_setPreferredVoicePrivacy(RILResponse *resp, bool enable);
int RILC_getPreferredVoicePrivacy(RILResponse *resp);
int RILC_separateConnection(RILResponse *resp, int gsmIndex);
int RILC_acceptCall(RILResponse *resp);
int RILC_rejectCall(RILResponse *resp);
int RILC_explicitCallTransfer(RILResponse *resp);
int RILC_getLastCallFailCause(RILResponse *resp);

// __attribute_deprecated__ int getLastPdpFailCause();

int RILC_getLastDataCallFailCause(RILResponse *resp);
int RILC_setMute(RILResponse *resp, bool enableMute);
int RILC_getMute(RILResponse *resp);
int RILC_getSignalStrength(RILResponse *resp);
int RILC_getVoiceRegistrationState(RILResponse *resp);
int RILC_getDataRegistrationState(RILResponse *resp);
int RILC_getOperator(RILResponse *resp);
int RILC_sendDtmf(RILResponse *resp, char c);
int RILC_startDtmf(RILResponse *resp, char c);
int RILC_stopDtmf(RILResponse *resp);
int RILC_sendBurstDtmf(RILResponse *resp, const char *dtmfString, int on, int off);
int RILC_sendSMS(RILResponse *resp, const char *smscPDU, const char *pdu);

// int sendCdmaSms(uint8_t *pdu);

int RILC_deleteSmsOnSim(RILResponse *resp, int index);
int RILC_deleteSmsOnRuim(RILResponse *resp, int index);
int RILC_writeSmsToSim(RILResponse *resp, int status, const char *smsc, const char *pdu);
int RILC_writeSmsToRuim(RILResponse *resp, int status, const char *pdu);
int RILC_setupDataCall(RILResponse *resp, RadioTech radioTechnology, const char *profile, const char *apn,
                       const char *user, const char *password, RadioAuth authType, RadioProtocol protocol);

int RILC_deactivateDataCall(RILResponse *resp, int cid, int reason);
int RILC_setRadioPower(RILResponse *resp, bool on);
int RILC_setSuppServiceNotifications(RILResponse *resp, bool enable);
int RILC_acknowledgeLastIncomingGsmSms(RILResponse *resp, bool success, int cause);
int RILC_acknowledgeLastIncomingCdmaSms(RILResponse *resp, bool success, int cause);
int RILC_acknowledgeIncomingGsmSmsWithPdu(RILResponse *resp, bool success, const char *ackPdu);
int RILC_iccIO(RILResponse *resp, int command, int fileid, const char *path, int p1, int p2, int p3,
               const char *data, const char *pin2);

int RILC_getCLIR(RILResponse *resp);
int RILC_setCLIR(RILResponse *resp, int clirMode);
int RILC_queryCallWaiting(RILResponse *resp, int serviceClass);
int RILC_setCallWaiting(RILResponse *resp, bool enable, int serviceClass);
int RILC_setNetworkSelectionModeAutomatic(RILResponse *resp);
int RILC_setNetworkSelectionModeManual(RILResponse *resp, const char *operatorNumeric);
int RILC_getNetworkSelectionMode(RILResponse *resp);
int RILC_getAvailableNetworks(RILResponse *resp);
int RILC_setCallForward(RILResponse *resp, int action, int cfReason, int serviceClass,
                        const char *number, int timeSeconds);

int RILC_queryCallForwardStatus(RILResponse *resp, int cfReason, int serviceClass,
                                const char *number);

int RILC_queryCLIP(RILResponse *resp);
int RILC_getBasebandVersion(RILResponse *resp);
int RILC_queryFacilityLock(RILResponse *resp, const char *facility, const char *password, int serviceClass);
int RILC_queryFacilityLockForApp(RILResponse *resp, const char *facility, const char *password, int serviceClass, const char *appId);
int RILC_setFacilityLock(RILResponse *resp, const char *facility, bool lockState, const char *password, int serviceClass);
int RILC_setFacilityLockForApp(RILResponse *resp, const char *facility, bool lockState, const char *password,
                               int serviceClass, const char *appId);
int RILC_sendUSSD(RILResponse *resp, const char *ussdString);
int RILC_cancelPendingUssd(RILResponse *resp);
int RILC_resetRadio(RILResponse *resp);

// int RILC_invokeOemRILRequestRaw(RILResponse *resp, uint8_t *data);

int RILC_invokeOemRILRequestStrings(RILResponse *resp, int num, const char **strings);
int RILC_setBandMode(RILResponse *resp, int bandMode);
int RILC_queryAvailableBandMode(RILResponse *resp);
int RILC_sendTerminalResponse(RILResponse *resp, const char *contents);
int RILC_sendEnvelope(RILResponse *resp, const char *contents);
int RILC_sendEnvelopeWithStatus(RILResponse *resp, const char *contents);
int RILC_handleCallSetupRequestFromSim(RILResponse *resp, bool accept);
int RILC_setPreferredNetworkType(RILResponse *resp, RadioTech networktype);
int RILC_getPreferredNetworkType(RILResponse *resp);
int RILC_getNeighboringCids(RILResponse *resp);
int RILC_setLocationUpdates(RILResponse *resp, bool enable);
int RILC_getSmscAddress(RILResponse *resp);
int RILC_setSmscAddress(RILResponse *resp, const char *address);
int RILC_reportSmsMemoryStatus(RILResponse *resp, bool available);
int RILC_reportStkServiceIsRunning(RILResponse *resp);
int RILC_getGsmBroadcastConfig(RILResponse *resp);

// int RILC_setGsmBroadcastConfig(RILResponse *resp, SmsBroadcastConfigInfo[] config)

int RILC_setGsmBroadcastActivation(RILResponse *resp, bool activate);
```



`RilRequest` is the real worker for every request. Before all the job starts, user should call `RILC_init` to do some init works, including 'start new polling thread in the background', 'init the class variables'.



## RIlResponse
All response(socilited/unsocilited) will be passed to user in the following struct including a 'show func', a 'free func'. App developer does not need to care about the free job and memory leak.

```c++
typedef struct _RILResponse
{
    /**
     * user data field, user can set the fileld as he will. users should distinguish the request by himself
     * -> value set by user
     */
    void *userdata;

    /**
     * response data if have 
     * -> value set by rilc
     */
    union
    {
        int value_int;
        const char *value_string;
        data_array array;
    } responseData;

    response_type responseType;

    /* command id, or request id */
    int commandId;

    /**
     * error code from rild, refer to rild for more details. notice, this field is valid only in socilited response
     * -> value set by rilc
     */
    int errorCode;

    /**
     * the response is unsocilited response?
     * 0 for socilited response
     * 1 for unsocilited response
     * -> value set by rilc
     */
    int isUnsocilited;

    /* request time or the time get unsocilited response, rilc will set the time
     * -> value set by rilc */
    struct timespec startTime;

    /* request finish time, rilc will set the time when finish 
     * -> value set by rilc */
    struct timespec finishTime;

    /**
     * an callback function, the function will be called when rilc finish the request or get unsocilited response
     * NOTICE:
     *      User should implement an mechenism of notification, by signal or lock by himself, 
     *      anyway, rilc does not care, but it should work.
     * -> value set by user
     */
    void (*responseNotify)(_RILResponse *);

    void (*responseShow)(_RILResponse *);

    void (*responseFree)(_RILResponse *);
} RILResponse;
```

