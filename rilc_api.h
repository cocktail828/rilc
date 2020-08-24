#ifndef __RILC
#define __RILC

#include "rilc_interface.h"

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
// RILC_ + RILRequest method
int RILC_getIMEI(RILResponse *resp);

int RILC_getIMSI(RILResponse *resp);

int RILC_getVoiceRegistrationState(RILResponse *resp);

int RILC_getDataRegistrationState(RILResponse *resp);

int RILC_getOperator(RILResponse *resp);

int RILC_getNeighboringCids(RILResponse *resp);

#endif //__RILC
