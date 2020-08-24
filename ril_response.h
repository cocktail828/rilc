#ifndef __RIL_RESPONSE
#define __RIL_RESPONSE

#include <string>
#include <vector>
#include <functional>
#include <map>

#include "ril/ril.h"
#include "parcel/parcel.h"
#include "rilc_interface.h"

std::string responseToString(int respid);

void responseVoid(Parcel &, RILResponse *p);

void responseInts(Parcel &, RILResponse *p);

void responseString(Parcel &, RILResponse *p);

void responseStrings(Parcel &, RILResponse *p);

/* private process functions */
void responseIccCardStatus(Parcel &, RILResponse *);

void responseCallList(Parcel &, RILResponse *);

void responseSignalStrength(Parcel &, RILResponse *);

void responseSMS(Parcel &, RILResponse *);

void responseSetupDataCall(Parcel &, RILResponse *);

void responseICC_IO(Parcel &, RILResponse *);

void responseCallForward(Parcel &, RILResponse *);

void responseOperatorInfos(Parcel &, RILResponse *);

void responseDataCallList(Parcel &, RILResponse *);

void responseRaw(Parcel &, RILResponse *);

void responseGetPreferredNetworkType(Parcel &, RILResponse *);

void responseCellList(Parcel &, RILResponse *);

void responseGmsBroadcastConfig(Parcel &, RILResponse *);

void responseCdmaBroadcastConfig(Parcel &, RILResponse *);

void responseSuppServiceNotification(Parcel &, RILResponse *);

void responseCallRing(Parcel &, RILResponse *);

void responseCdmaSms(Parcel &, RILResponse *);

void responseCdmaCallWaiting(Parcel &, RILResponse *);

void responseCdmaInformationRecord(Parcel &, RILResponse *);

/* socilited response handlers */
static std::map<int, std::function<void(Parcel &, RILResponse *)>> SocilitedProcesser = {
    {RIL_REQUEST_GET_SIM_STATUS, responseIccCardStatus},
    {RIL_REQUEST_ENTER_SIM_PIN, responseInts},
    {RIL_REQUEST_ENTER_SIM_PUK, responseInts},
    {RIL_REQUEST_ENTER_SIM_PIN2, responseInts},
    {RIL_REQUEST_ENTER_SIM_PUK2, responseInts},
    {RIL_REQUEST_CHANGE_SIM_PIN, responseInts},
    {RIL_REQUEST_CHANGE_SIM_PIN2, responseInts},
    {RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION, responseInts},
    {RIL_REQUEST_GET_CURRENT_CALLS, responseCallList},
    {RIL_REQUEST_DIAL, responseVoid},
    {RIL_REQUEST_GET_IMSI, responseString},
    {RIL_REQUEST_HANGUP, responseVoid},
    {RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND, responseVoid},
    {RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND, responseVoid},
    {RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE, responseVoid},
    {RIL_REQUEST_CONFERENCE, responseVoid},
    {RIL_REQUEST_UDUB, responseVoid},
    {RIL_REQUEST_LAST_CALL_FAIL_CAUSE, responseInts},
    {RIL_REQUEST_SIGNAL_STRENGTH, responseSignalStrength},
    {RIL_REQUEST_VOICE_REGISTRATION_STATE, responseStrings},
    {RIL_REQUEST_DATA_REGISTRATION_STATE, responseStrings},
    {RIL_REQUEST_OPERATOR, responseStrings},
    {RIL_REQUEST_RADIO_POWER, responseVoid},
    {RIL_REQUEST_DTMF, responseVoid},
    {RIL_REQUEST_SEND_SMS, responseSMS},
    {RIL_REQUEST_SEND_SMS_EXPECT_MORE, responseSMS},
    {RIL_REQUEST_SETUP_DATA_CALL, responseSetupDataCall},
    {RIL_REQUEST_SIM_IO, responseICC_IO},
    {RIL_REQUEST_SEND_USSD, responseVoid},
    {RIL_REQUEST_CANCEL_USSD, responseVoid},
    {RIL_REQUEST_GET_CLIR, responseInts},
    {RIL_REQUEST_SET_CLIR, responseVoid},
    {RIL_REQUEST_QUERY_CALL_FORWARD_STATUS, responseCallForward},
    {RIL_REQUEST_SET_CALL_FORWARD, responseVoid},
    {RIL_REQUEST_QUERY_CALL_WAITING, responseInts},
    {RIL_REQUEST_SET_CALL_WAITING, responseVoid},
    {RIL_REQUEST_SMS_ACKNOWLEDGE, responseVoid},
    {RIL_REQUEST_GET_IMEI, responseString},
    {RIL_REQUEST_GET_IMEISV, responseString},
    {RIL_REQUEST_ANSWER, responseVoid},
    {RIL_REQUEST_DEACTIVATE_DATA_CALL, responseVoid},
    {RIL_REQUEST_QUERY_FACILITY_LOCK, responseInts},
    {RIL_REQUEST_SET_FACILITY_LOCK, responseInts},
    {RIL_REQUEST_CHANGE_BARRING_PASSWORD, responseVoid},
    {RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE, responseInts},
    {RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC, responseVoid},
    {RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL, responseVoid},
    {RIL_REQUEST_QUERY_AVAILABLE_NETWORKS, responseOperatorInfos},
    {RIL_REQUEST_DTMF_START, responseVoid},
    {RIL_REQUEST_DTMF_STOP, responseVoid},
    {RIL_REQUEST_BASEBAND_VERSION, responseString},
    {RIL_REQUEST_SEPARATE_CONNECTION, responseVoid},
    {RIL_REQUEST_SET_MUTE, responseVoid},
    {RIL_REQUEST_GET_MUTE, responseInts},
    {RIL_REQUEST_QUERY_CLIP, responseInts},
    {RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE, responseInts},
    {RIL_REQUEST_DATA_CALL_LIST, responseDataCallList},
    {RIL_REQUEST_RESET_RADIO, responseVoid},
    {RIL_REQUEST_OEM_HOOK_RAW, responseRaw},
    {RIL_REQUEST_OEM_HOOK_STRINGS, responseStrings},
    {RIL_REQUEST_SCREEN_STATE, responseVoid},
    {RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION, responseVoid},
    {RIL_REQUEST_WRITE_SMS_TO_SIM, responseInts},
    {RIL_REQUEST_DELETE_SMS_ON_SIM, responseVoid},
    {RIL_REQUEST_SET_BAND_MODE, responseVoid},
    {RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE, responseInts},
    {RIL_REQUEST_STK_GET_PROFILE, responseString},
    {RIL_REQUEST_STK_SET_PROFILE, responseVoid},
    {RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND, responseString},
    {RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE, responseVoid},
    {RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM, responseInts},
    {RIL_REQUEST_EXPLICIT_CALL_TRANSFER, responseVoid},
    {RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE, responseVoid},
    {RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE, responseGetPreferredNetworkType},
    {RIL_REQUEST_GET_NEIGHBORING_CELL_IDS, responseCellList},
    {RIL_REQUEST_SET_LOCATION_UPDATES, responseVoid},
    {RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE, responseVoid},
    {RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE, responseVoid},
    {RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE, responseInts},
    {RIL_REQUEST_SET_TTY_MODE, responseVoid},
    {RIL_REQUEST_QUERY_TTY_MODE, responseInts},
    {RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE, responseVoid},
    {RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE, responseInts},
    {RIL_REQUEST_CDMA_FLASH, responseVoid},
    {RIL_REQUEST_CDMA_BURST_DTMF, responseVoid},
    {RIL_REQUEST_CDMA_SEND_SMS, responseSMS},
    {RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE, responseVoid},

    // {RIL_REQUEST_GSM_GET_BROADCAST_CONFIG, responseGmsBroadcastConfig},
    // {RIL_REQUEST_GSM_SET_BROADCAST_CONFIG, responseVoid},
    // {RIL_REQUEST_GSM_BROADCAST_ACTIVATION, responseVoid},
    // {RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG, responseCdmaBroadcastConfig},
    // {RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG, responseVoid},
    // {RIL_REQUEST_CDMA_BROADCAST_ACTIVATION, responseVoid},
    // {RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY, responseVoid},

    {RIL_REQUEST_CDMA_SUBSCRIPTION, responseStrings},
    {RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM, responseInts},
    {RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM, responseVoid},
    {RIL_REQUEST_DEVICE_IDENTITY, responseStrings},
    {RIL_REQUEST_GET_SMSC_ADDRESS, responseString},
    {RIL_REQUEST_SET_SMSC_ADDRESS, responseVoid},
    {RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE, responseVoid},
    {RIL_REQUEST_REPORT_SMS_MEMORY_STATUS, responseVoid},
    {RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING, responseVoid},
    {RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE, responseInts},
    {RIL_REQUEST_ISIM_AUTHENTICATION, responseString},
    {RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU, responseVoid},
    {RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS, responseICC_IO}};

static std::map<int, std::function<void(Parcel &, RILResponse *)>> UnsocilitedProcesser = {
    {RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED, responseVoid},
    {RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED, responseVoid},
    {RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED, responseVoid},
    {RIL_UNSOL_RESPONSE_NEW_SMS, responseString},
    {RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT, responseString},
    {RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM, responseInts},
    {RIL_UNSOL_ON_USSD, responseStrings},
    {RIL_UNSOL_NITZ_TIME_RECEIVED, responseString},
    {RIL_UNSOL_SIGNAL_STRENGTH, responseSignalStrength},
    {RIL_UNSOL_DATA_CALL_LIST_CHANGED, responseDataCallList},
    {RIL_UNSOL_SUPP_SVC_NOTIFICATION, responseSuppServiceNotification},
    {RIL_UNSOL_STK_SESSION_END, responseVoid},
    {RIL_UNSOL_STK_PROACTIVE_COMMAND, responseString},
    {RIL_UNSOL_STK_EVENT_NOTIFY, responseString},
    {RIL_UNSOL_STK_CALL_SETUP, responseInts},
    {RIL_UNSOL_SIM_SMS_STORAGE_FULL, responseVoid},
    {RIL_UNSOL_SIM_REFRESH, responseInts},
    {RIL_UNSOL_CALL_RING, responseCallRing},
    {RIL_UNSOL_RESTRICTED_STATE_CHANGED, responseInts},
    {RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED, responseVoid},
    {RIL_UNSOL_RESPONSE_CDMA_NEW_SMS, responseCdmaSms},
    {RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS, responseRaw},
    {RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL, responseVoid},
    {RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE, responseVoid},
    {RIL_UNSOL_CDMA_CALL_WAITING, responseCdmaCallWaiting},
    {RIL_UNSOL_CDMA_OTA_PROVISION_STATUS, responseInts},
    {RIL_UNSOL_CDMA_INFO_REC, responseCdmaInformationRecord},
    {RIL_UNSOL_OEM_HOOK_RAW, responseRaw},
    {RIL_UNSOL_RINGBACK_TONE, responseInts},
    {RIL_UNSOL_RESEND_INCALL_MUTE, responseVoid},
    {RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED, responseInts},
    {RIL_UNSOL_CDMA_PRL_CHANGED, responseInts},
    {RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE, responseVoid},
    {RIL_UNSOL_RIL_CONNECTED, responseInts},
    //     {RIL_UNSOL_VOICE_RADIO_TECH_CHANGED:
    //         ,"RIL_UNSOL_VOICE_RADIO_TECH_CHANGED";
    //     {RIL_UNSOL_CELL_INFO_LIST:
    //         ,"RIL_UNSOL_CELL_INFO_LIST";
    //     {RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED:
    //         ,"RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED";
    //     {RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED:
    //         ,"RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED";
    //     {RIL_UNSOL_SRVCC_STATE_NOTIFY:
    //         ,"RIL_UNSOL_SRVCC_STATE_NOTIFY";
    //     {RIL_UNSOL_HARDWARE_CONFIG_CHANGED:
    //         ,"RIL_UNSOL_HARDWARE_CONFIG_CHANGED";
    //     {RIL_UNSOL_DC_RT_INFO_CHANGED:
    //         ,"RIL_UNSOL_DC_RT_INFO_CHANGED";
    //     {RIL_UNSOL_RADIO_CAPABILITY:
    //         ,"RIL_UNSOL_RADIO_CAPABILITY";
    //     {RIL_UNSOL_ON_SS:
    //         ,"RIL_UNSOL_ON_SS";
    //     {RIL_UNSOL_STK_CC_ALPHA_NOTIFY:
    //         ,"RIL_UNSOL_STK_CC_ALPHA_NOTIFY";
    //     {RIL_UNSOL_LCEDATA_RECV:
    //         ,"RIL_UNSOL_LCEDATA_RECV";
    //     {RIL_UNSOL_RESPONSE_IMS_CALL_STATE_CHANGED:
    //         ,"RIL_UNSOL_RESPONSE_IMS_CALL_STATE_CHANGED";
    //     {RIL_UNSOL_RESPONSE_VIDEO_QUALITY:
    //         ,"RIL_UNSOL_RESPONSE_VIDEO_QUALITY";
    //     {RIL_UNSOL_RESPONSE_IMS_BEARER_ESTABLISTED:
    //         ,"RIL_UNSOL_RESPONSE_IMS_BEARER_ESTABLISTED";
    //     {RIL_UNSOL_IMS_HANDOVER_REQUEST:
    //         ,"RIL_UNSOL_IMS_HANDOVER_REQUEST";
    //     {RIL_UNSOL_IMS_HANDOVER_STATUS_CHANGE:
    //         ,"RIL_UNSOL_IMS_HANDOVER_STATUS_CHANGE";
    //     {RIL_UNSOL_IMS_NETWORK_INFO_CHANGE:
    //         ,"RIL_UNSOL_IMS_NETWORK_INFO_CHANGE";
    //     {RIL_UNSOL_IMS_REGISTER_ADDRESS_CHANGE:
    //         ,"RIL_UNSOL_IMS_REGISTER_ADDRESS_CHANGE";
    //     {RIL_UNSOL_IMS_WIFI_PARAM:
    //         ,"RIL_UNSOL_IMS_WIFI_PARAM";
    //     {RIL_UNSOL_IMS_NETWORK_STATE_CHANGED:
    //         ,"RIL_UNSOL_IMS_NETWORK_STATE_CHANGED";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_CODEC:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_CODEC";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_DSCI:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_DSCI";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_STRING:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_STRING";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_REMOTE_MEDIA:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_REMOTE_MEDIA";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_MM_RING:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_MM_RING";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_RELEASING:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_RELEASING";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_RECORD_VIDEO:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_RECORD_VIDEO";
    //     {RIL_EXT_UNSOL_VIDEOPHONE_MEDIA_START:
    //         ,"RIL_EXT_UNSOL_VIDEOPHONE_MEDIA_START";
    //     {RIL_EXT_UNSOL_ECC_NETWORKLIST_CHANGED:
    //         ,"RIL_EXT_UNSOL_ECC_NETWORKLIST_CHANGED";
    //     {RIL_EXT_UNSOL_RAU_SUCCESS:
    //         ,"RIL_EXT_UNSOL_RAU_SUCCESS";
    //     {RIL_EXT_UNSOL_CLEAR_CODE_FALLBACK:
    //         ,"RIL_EXT_UNSOL_CLEAR_CODE_FALLBACK";
    //     {RIL_EXT_UNSOL_RIL_CONNECTED:
    //         ,"RIL_EXT_UNSOL_RIL_CONNECTED";
    //     {RIL_EXT_UNSOL_SIMLOCK_STATUS_CHANGED:
    //         ,"RIL_EXT_UNSOL_SIMLOCK_STATUS_CHANGED";
    //     {RIL_EXT_UNSOL_SIMLOCK_SIM_EXPIRED:
    //         ,"RIL_EXT_UNSOL_SIMLOCK_SIM_EXPIRED";
    //     {RIL_EXT_UNSOL_BAND_INFO:
    //         ,"RIL_EXT_UNSOL_BAND_INFO";
    //     {RIL_EXT_UNSOL_SWITCH_PRIMARY_CARD:
    //         ,"RIL_EXT_UNSOL_SWITCH_PRIMARY_CARD";
    //     {RIL_EXT_UNSOL_SIM_PS_REJECT:
    //         ,"RIL_EXT_UNSOL_SIM_PS_REJECT";
    //     {RIL_EXT_UNSOL_SETUP_DATA_FOR_CP:
    //         ,"RIL_EXT_UNSOL_SETUP_DATA_FOR_CP";
    //     {RIL_EXT_UNSOL_SIMMGR_SIM_STATUS_CHANGED:
    //         ,"RIL_EXT_UNSOL_SIMMGR_SIM_STATUS_CHANGED";
    //     {RIL_EXT_UNSOL_RADIO_CAPABILITY_CHANGED:
    //         ,"RIL_EXT_UNSOL_RADIO_CAPABILITY_CHANGED";
    //     {RIL_EXT_UNSOL_EARLY_MEDIA:
    //         ,"RIL_EXT_UNSOL_EARLY_MEDIA";
    {RIL_EXT_UNSOL_ATROUTER_RSP, responseString},
//     {RIL_EXT_UNSOL_DATA_PDP_INFO, "RIL_EXT_UNSOL_DATA_PDP_INFO";

#ifdef ORCA_FEATURE_5G
//     {RIL_EXT_UNSOL_PHYSICAL_CHANNEL_CONFIG, "RIL_EXT_UNSOL_PHYSICAL_CHANNEL_CONFIG";
//     {RIL_EXT_UNSOL_NETWORK_SCAN_RESULT, "RIL_EXT_UNSOL_NETWORK_SCAN_RESULT";
//     {RIL_EXT_UNSOL_SIGNAL_STRENGTH, "RIL_EXT_UNSOL_SIGNAL_STRENGTH";
//     {RIL_EXT_UNSOL_SIGNAL_CONN_STATUS, "RIL_EXT_UNSOL_SIGNAL_CONN_STATUS";
//     {RIL_EXT_UNSOL_PPP_RSP, "RIL_EXT_UNSOL_PPP_RSP";
//     {RIL_EXT_UNSOL_PPP_DATA_PDP_INFO, "RIL_EXT_UNSOL_PPP_DATA_PDP_INFO";
#else
// {RIL_EXT_UNSOL_PPP_RSP, "RIL_EXT_UNSOL_PPP_RSP"},
// {RIL_EXT_UNSOL_PPP_DATA_PDP_INFO, "RIL_EXT_UNSOL_PPP_DATA_PDP_INFO"},
#endif
};

#endif //__RIL_RESPONSE
