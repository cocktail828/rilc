#ifndef __RILC
#define __RILC

#include "rilc_interface.h"
#include "ril/ril.h"

/**
 * init rilc, start an polling thread for read
 * return:
 *  0 for some error
 *  1 for success
 */
int RILC_init(const char *device);

/**
 * uninit rilc, stop polling
 * return:
 *  0 for some error
 *  1 for success
 */
int RILC_uninit();

/***********************************************************/
/***************** RILC UNSOCILITED PROCESSERS ******************/
/***********************************************************/
// TODO FINISH
// /**
//      * Fires on any RadioState transition
//      * Always fires immediately as well
//      *
//      * do not attempt to calculate transitions by storing getRadioState() values
//      * on previous invocations of this notification. Instead, use the other
//      * registration methods
//      */
// void registerForRadioStateChanged(Handler h, int what, Object obj);
// void unregisterForRadioStateChanged(Handler h);

// /**
//      * Fires on any transition into RadioState.isOn()
//      * Fires immediately if currently in that state
//      * In general, actions should be idempotent. State may change
//      * before event is received.
//      */
// void registerForOn(Handler h, int what, Object obj);
// void unregisterForOn(Handler h);

// /**
//      * Fires on any transition out of RadioState.isAvailable()
//      * Fires immediately if currently in that state
//      * In general, actions should be idempotent. State may change
//      * before event is received.
//      */
// void registerForAvailable(Handler h, int what, Object obj);
// void unregisterForAvailable(Handler h);

// /**
//      * Fires on any transition into !RadioState.isAvailable()
//      * Fires immediately if currently in that state
//      * In general, actions should be idempotent. State may change
//      * before event is received.
//      */
// void registerForNotAvailable(Handler h, int what, Object obj);
// void unregisterForNotAvailable(Handler h);

// /**
//      * Fires on any transition into RADIO_OFF or !RadioState.isAvailable()
//      * Fires immediately if currently in that state
//      * In general, actions should be idempotent. State may change
//      * before event is received.
//      */
// void registerForOffOrNotAvailable(Handler h, int what, Object obj);
// void unregisterForOffOrNotAvailable(Handler h);

// /**
//      * Fires on any transition into SIM_READY
//      * Fires immediately if if currently in that state
//      * In general, actions should be idempotent. State may change
//      * before event is received.
//      */
// void registerForSIMReady(Handler h, int what, Object obj);
// void unregisterForSIMReady(Handler h);

// /** Any transition into SIM_LOCKED_OR_ABSENT */
// void registerForSIMLockedOrAbsent(Handler h, int what, Object obj);
// void unregisterForSIMLockedOrAbsent(Handler h);

// void registerForIccStatusChanged(Handler h, int what, Object obj);
// void unregisterForIccStatusChanged(Handler h);

// void registerForCallStateChanged(Handler h, int what, Object obj);
// void unregisterForCallStateChanged(Handler h);
// void registerForVoiceNetworkStateChanged(Handler h, int what, Object obj);
// void unregisterForVoiceNetworkStateChanged(Handler h);
// void registerForDataNetworkStateChanged(Handler h, int what, Object obj);
// void unregisterForDataNetworkStateChanged(Handler h);

// void registerForRadioTechnologyChanged(Handler h, int what, Object obj);
// void unregisterForRadioTechnologyChanged(Handler h);
// void registerForNVReady(Handler h, int what, Object obj);
// void unregisterForNVReady(Handler h);
// void registerForRUIMLockedOrAbsent(Handler h, int what, Object obj);
// void unregisterForRUIMLockedOrAbsent(Handler h);

// /** InCall voice privacy notifications */
// void registerForInCallVoicePrivacyOn(Handler h, int what, Object obj);
// void unregisterForInCallVoicePrivacyOn(Handler h);
// void registerForInCallVoicePrivacyOff(Handler h, int what, Object obj);
// void unregisterForInCallVoicePrivacyOff(Handler h);

// /**
//      * Fires on any transition into RUIM_READY
//      * Fires immediately if if currently in that state
//      * In general, actions should be idempotent. State may change
//      * before event is received.
//      */
// void registerForRUIMReady(Handler h, int what, Object obj);
// void unregisterForRUIMReady(Handler h);

// /**
//      * unlike the register* methods, there's only one new 3GPP format SMS handler.
//      * if you need to unregister, you should also tell the radio to stop
//      * sending SMS's to you (via AT+CNMI)
//      *
//      * AsyncResult.result is a String containing the SMS PDU
//      */
// void setOnNewGsmSms(Handler h, int what, Object obj);
// void unSetOnNewGsmSms(Handler h);

// /**
//      * unlike the register* methods, there's only one new 3GPP2 format SMS handler.
//      * if you need to unregister, you should also tell the radio to stop
//      * sending SMS's to you (via AT+CNMI)
//      *
//      * AsyncResult.result is a String containing the SMS PDU
//      */
// void setOnNewCdmaSms(Handler h, int what, Object obj);
// void unSetOnNewCdmaSms(Handler h);

// /**
//      * Set the handler for SMS Cell Broadcast messages.
//      *
//      * AsyncResult.result is a byte array containing the SMS-CB PDU
//      */
// void setOnNewGsmBroadcastSms(Handler h, int what, Object obj);
// void unSetOnNewGsmBroadcastSms(Handler h);

// /**
//      * Register for NEW_SMS_ON_SIM unsolicited message
//      *
//      * AsyncResult.result is an int array containing the index of new SMS
//      */
// void setOnSmsOnSim(Handler h, int what, Object obj);
// void unSetOnSmsOnSim(Handler h);

// /**
//      * Register for NEW_SMS_STATUS_REPORT unsolicited message
//      *
//      * AsyncResult.result is a String containing the status report PDU
//      */
// void setOnSmsStatus(Handler h, int what, Object obj);
// void unSetOnSmsStatus(Handler h);

// /**
//      * unlike the register* methods, there's only one NITZ time handler
//      *
//      * AsyncResult.result is an Object[]
//      * ((Object[])AsyncResult.result)[0] is a String containing the NITZ time string
//      * ((Object[])AsyncResult.result)[1] is a Long containing the milliseconds since boot as
//      *                                   returned by elapsedRealtime() when this NITZ time
//      *                                   was posted.
//      *
//      * Please note that the delivery of this message may be delayed several
//      * seconds on system startup
//      */
// void setOnNITZTime(Handler h, int what, Object obj);
// void unSetOnNITZTime(Handler h);

// /**
//      * unlike the register* methods, there's only one USSD notify handler
//      *
//      * Represents the arrival of a USSD "notify" message, which may
//      * or may not have been triggered by a previous USSD send
//      *
//      * AsyncResult.result is a String[]
//      * ((String[])(AsyncResult.result))[0] contains status code
//      *      "0"   USSD-Notify -- text in ((const char **)data)[1]
//      *      "1"   USSD-Request -- text in ((const char **)data)[1]
//      *      "2"   Session terminated by network
//      *      "3"   other local client (eg, SIM Toolkit) has responded
//      *      "4"   Operation not supported
//      *      "5"   Network timeout
//      *
//      * ((String[])(AsyncResult.result))[1] contains the USSD message
//      * The numeric representations of these are in USSD_MODE_*
//      */

// void setOnUSSD(Handler h, int what, Object obj);
// void unSetOnUSSD(Handler h);

// /**
//      * unlike the register* methods, there's only one signal strength handler
//      * AsyncResult.result is an int[2]
//      * response.obj.result[0] is received signal strength (0-31, 99)
//      * response.obj.result[1] is  bit error rate (0-7, 99)
//      * as defined in TS 27.007 8.5
//      */

// void setOnSignalStrengthUpdate(Handler h, int what, Object obj);
// void unSetOnSignalStrengthUpdate(Handler h);

// /**
//      * Sets the handler for SIM/RUIM SMS storage full unsolicited message.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void setOnIccSmsFull(Handler h, int what, Object obj);
// void unSetOnIccSmsFull(Handler h);

// /**
//      * Sets the handler for SIM Refresh notifications.
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForIccRefresh(Handler h, int what, Object obj);
// void unregisterForIccRefresh(Handler h);

// void setOnIccRefresh(Handler h, int what, Object obj);
// void unsetOnIccRefresh(Handler h);

// /**
//      * Sets the handler for RING notifications.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void setOnCallRing(Handler h, int what, Object obj);
// void unSetOnCallRing(Handler h);

// /**
//      * Sets the handler for RESTRICTED_STATE changed notification,
//      * eg, for Domain Specific Access Control
//      * unlike the register* methods, there's only one signal strength handler
//      *
//      * AsyncResult.result is an int[1]
//      * response.obj.result[0] is a bitmask of RIL_RESTRICTED_STATE_* values
//      */

// void setOnRestrictedStateChanged(Handler h, int what, Object obj);
// void unSetOnRestrictedStateChanged(Handler h);

// /**
//      * Sets the handler for Supplementary Service Notifications.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void setOnSuppServiceNotification(Handler h, int what, Object obj);
// void unSetOnSuppServiceNotification(Handler h);

// /**
//      * Sets the handler for Session End Notifications for CAT.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void setOnCatSessionEnd(Handler h, int what, Object obj);
// void unSetOnCatSessionEnd(Handler h);

// /**
//      * Sets the handler for Proactive Commands for CAT.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void setOnCatProactiveCmd(Handler h, int what, Object obj);
// void unSetOnCatProactiveCmd(Handler h);

// /**
//      * Sets the handler for Event Notifications for CAT.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void setOnCatEvent(Handler h, int what, Object obj);
// void unSetOnCatEvent(Handler h);

// /**
//      * Sets the handler for Call Set Up Notifications for CAT.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void setOnCatCallSetUp(Handler h, int what, Object obj);
// void unSetOnCatCallSetUp(Handler h);

// /**
//      * Enables/disbables supplementary service related notifications from
//      * the network.
//      *
//      * @param enable true to enable notifications, false to disable.
//      * @param result Message to be posted when command completes.
//      */
// void setSuppServiceNotifications(boolean enable, Message result);
// //void unSetSuppServiceNotifications(Handler h);

// /**
//      * Sets the handler for Event Notifications for CDMA Display Info.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForDisplayInfo(Handler h, int what, Object obj);
// void unregisterForDisplayInfo(Handler h);

// /**
//      * Sets the handler for Event Notifications for CallWaiting Info.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForCallWaitingInfo(Handler h, int what, Object obj);
// void unregisterForCallWaitingInfo(Handler h);

// /**
//      * Sets the handler for Event Notifications for Signal Info.
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForSignalInfo(Handler h, int what, Object obj);
// void unregisterForSignalInfo(Handler h);

// /**
//      * Registers the handler for CDMA number information record
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForNumberInfo(Handler h, int what, Object obj);
// void unregisterForNumberInfo(Handler h);

// /**
//      * Registers the handler for CDMA redirected number Information record
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForRedirectedNumberInfo(Handler h, int what, Object obj);
// void unregisterForRedirectedNumberInfo(Handler h);

// /**
//      * Registers the handler for CDMA line control information record
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForLineControlInfo(Handler h, int what, Object obj);
// void unregisterForLineControlInfo(Handler h);

// /**
//      * Registers the handler for CDMA T53 CLIR information record
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerFoT53ClirlInfo(Handler h, int what, Object obj);
// void unregisterForT53ClirInfo(Handler h);

// /**
//      * Registers the handler for CDMA T53 audio control information record
//      * Unlike the register* methods, there's only one notification handler
//      *
//      * @param h Handler for notification message.
//      * @param what User-defined message code.
//      * @param obj User object.
//      */
// void registerForT53AudioControlInfo(Handler h, int what, Object obj);
// void unregisterForT53AudioControlInfo(Handler h);

// /**
//      * Fires on if Modem enters Emergency Callback mode
//      */
// void setEmergencyCallbackMode(Handler h, int what, Object obj);

// /**
//       * Fires on any CDMA OTA provision status change
//       */
// void registerForCdmaOtaProvision(Handler h, int what, Object obj);
// void unregisterForCdmaOtaProvision(Handler h);

// /**
//       * Registers the handler when out-band ringback tone is needed.<p>
//       *
//       *  Messages received from this:
//       *  Message.obj will be an AsyncResult
//       *  AsyncResult.userObj = obj
//       *  AsyncResult.result = boolean. <p>
//       */
// void registerForRingbackTone(Handler h, int what, Object obj);
// void unregisterForRingbackTone(Handler h);

// /**
//       * Registers the handler when mute/unmute need to be resent to get
//       * uplink audio during a call.<p>
//       *
//       * @param h Handler for notification message.
//       * @param what User-defined message code.
//       * @param obj User object.
//       *
//       */
// void registerForResendIncallMute(Handler h, int what, Object obj);
// void unregisterForResendIncallMute(Handler h);

// /**
//       * Registers the handler for when Cdma subscription changed events
//       *
//       * @param h Handler for notification message.
//       * @param what User-defined message code.
//       * @param obj User object.
//       *
//       */
// void registerForCdmaSubscriptionChanged(Handler h, int what, Object obj);
// void unregisterForCdmaSubscriptionChanged(Handler h);

// /**
//       * Registers the handler for when Cdma prl changed events
//       *
//       * @param h Handler for notification message.
//       * @param what User-defined message code.
//       * @param obj User object.
//       *
//       */
// void registerForCdmaPrlChanged(Handler h, int what, Object obj);
// void unregisterForCdmaPrlChanged(Handler h);

// /**
//       * Registers the handler for when Cdma prl changed events
//       *
//       * @param h Handler for notification message.
//       * @param what User-defined message code.
//       * @param obj User object.
//       *
//       */
// void registerForExitEmergencyCallbackMode(Handler h, int what, Object obj);
// void unregisterForExitEmergencyCallbackMode(Handler h);

// /**
//       * Registers the handler for RIL_UNSOL_RIL_CONNECT events.
//       *
//       * When ril connects or disconnects a message is sent to the registrant
//       * which contains an AsyncResult, ar, in msg.obj. The ar.result is an
//       * Integer which is the version of the ril or -1 if the ril disconnected.
//       *
//       * @param h Handler for notification message.
//       * @param what User-defined message code.
//       * @param obj User object.
//       */
// void registerForRilConnected(Handler h, int what, Object obj);
// void unregisterForRilConnected(Handler h);

/***********************************************************/
/***************** RILC STANDARD REQUESTS ******************/
/***********************************************************/
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

#endif //__RILC
