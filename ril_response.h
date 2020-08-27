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

void responseStrings(Parcel &p, RILResponse *resp);
void responseStringsShow(RILResponse *resp);
void responseStringsFree(RILResponse *resp);

void responseString(Parcel &p, RILResponse *resp);
void responseStringShow(RILResponse *resp);
void responseStringFree(RILResponse *resp);

void responseInts(Parcel &p, RILResponse *resp);
void responseIntsShow(RILResponse *resp);
void responseIntsFree(RILResponse *resp);

void responseVoid(Parcel &p, RILResponse *resp);
void responseVoidShow(RILResponse *resp);
void responseVoidFree(RILResponse *resp);

void responseIccCardStatus(Parcel &, RILResponse *);
void responseIccCardStatusShow(RILResponse *);
void responseIccCardStatusFree(RILResponse *);

void responseCallList(Parcel &, RILResponse *);
void responseCallListShow(RILResponse *);
void responseCallListFree(RILResponse *);

void responseSignalStrength(Parcel &, RILResponse *);
void responseSignalStrengthShow(RILResponse *);
void responseSignalStrengthFree(RILResponse *);

void responseSMS(Parcel &, RILResponse *);
void responseSMSShow(RILResponse *);
void responseSMSFree(RILResponse *);

void responseSetupDataCall(Parcel &, RILResponse *);
void responseSetupDataCallShow(RILResponse *);
void responseSetupDataCallFree(RILResponse *);

void responseICC_IO(Parcel &, RILResponse *);
void responseICC_IOShow(RILResponse *);
void responseICC_IOFree(RILResponse *);

void responseCallForward(Parcel &, RILResponse *);
void responseCallForwardShow(RILResponse *);
void responseCallForwardFree(RILResponse *);

void responseOperatorInfos(Parcel &, RILResponse *);
void responseOperatorInfosShow(RILResponse *);
void responseOperatorInfosFree(RILResponse *);

void responseDataCallList(Parcel &, RILResponse *);
void responseDataCallListShow(RILResponse *);
void responseDataCallListFree(RILResponse *);

void responseRaw(Parcel &, RILResponse *);
void responseRawShow(RILResponse *);
void responseRawFree(RILResponse *);

void responseGetPreferredNetworkType(Parcel &, RILResponse *);
void responseGetPreferredNetworkTypeShow(RILResponse *);
void responseGetPreferredNetworkTypeFree(RILResponse *);

void responseCellList(Parcel &, RILResponse *);
void responseCellListShow(RILResponse *);
void responseCellListFree(RILResponse *);

void responseGmsBroadcastConfig(Parcel &, RILResponse *);
void responseGmsBroadcastConfigShow(RILResponse *);
void responseGmsBroadcastConfigFree(RILResponse *);

void responseCdmaBroadcastConfig(Parcel &, RILResponse *);
void responseCdmaBroadcastConfigShow(RILResponse *);
void responseCdmaBroadcastConfigFree(RILResponse *);

void responseSuppServiceNotification(Parcel &, RILResponse *);
void responseSuppServiceNotificationShow(RILResponse *);
void responseSuppServiceNotificationFree(RILResponse *);

void responseCallRing(Parcel &, RILResponse *);
void responseCallRingShow(RILResponse *);
void responseCallRingFree(RILResponse *);

void responseCdmaSms(Parcel &, RILResponse *);
void responseCdmaSmsShow(RILResponse *);
void responseCdmaSmsFree(RILResponse *);

void responseCdmaCallWaiting(Parcel &, RILResponse *);
void responseCdmaCallWaitingShow(RILResponse *);
void responseCdmaCallWaitingFree(RILResponse *);

void responseCdmaInformationRecord(Parcel &, RILResponse *);
void responseCdmaInformationRecordShow(RILResponse *);
void responseCdmaInformationRecordFree(RILResponse *);

typedef struct
{
    void (*responseParser)(Parcel &, RILResponse *);
    void (*responseShow)(RILResponse *);
    void (*responseFree)(RILResponse *);
    void (*callback)(RILResponse *);
} RILCProcesser;

#define PROCESSER(v) \
    RILCProcesser { v, v##Show, v##Free }

/* socilited response handlers */
static std::map<int, RILCProcesser> SocilitedResponseProcesser = {
    {RIL_REQUEST_GET_SIM_STATUS, PROCESSER(responseIccCardStatus)},
    {RIL_REQUEST_ENTER_SIM_PIN, PROCESSER(responseInts)},
    {RIL_REQUEST_ENTER_SIM_PUK, PROCESSER(responseInts)},
    {RIL_REQUEST_ENTER_SIM_PIN2, PROCESSER(responseInts)},
    {RIL_REQUEST_ENTER_SIM_PUK2, PROCESSER(responseInts)},
    {RIL_REQUEST_CHANGE_SIM_PIN, PROCESSER(responseInts)},
    {RIL_REQUEST_CHANGE_SIM_PIN2, PROCESSER(responseInts)},
    {RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION, PROCESSER(responseInts)},
    {RIL_REQUEST_GET_CURRENT_CALLS, PROCESSER(responseCallList)},
    {RIL_REQUEST_DIAL, PROCESSER(responseVoid)},
    {RIL_REQUEST_GET_IMSI, PROCESSER(responseString)},
    {RIL_REQUEST_HANGUP, PROCESSER(responseVoid)},
    {RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND, PROCESSER(responseVoid)},
    {RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND, PROCESSER(responseVoid)},
    {RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE, PROCESSER(responseVoid)},
    {RIL_REQUEST_CONFERENCE, PROCESSER(responseVoid)},
    {RIL_REQUEST_UDUB, PROCESSER(responseVoid)},
    {RIL_REQUEST_LAST_CALL_FAIL_CAUSE, PROCESSER(responseInts)},
    {RIL_REQUEST_SIGNAL_STRENGTH, PROCESSER(responseSignalStrength)},
    {RIL_REQUEST_VOICE_REGISTRATION_STATE, PROCESSER(responseStrings)},
    {RIL_REQUEST_DATA_REGISTRATION_STATE, PROCESSER(responseStrings)},
    {RIL_REQUEST_OPERATOR, PROCESSER(responseStrings)},
    {RIL_REQUEST_RADIO_POWER, PROCESSER(responseVoid)},
    {RIL_REQUEST_DTMF, PROCESSER(responseVoid)},
    {RIL_REQUEST_SEND_SMS, PROCESSER(responseSMS)},
    {RIL_REQUEST_SEND_SMS_EXPECT_MORE, PROCESSER(responseSMS)},
    {RIL_REQUEST_SETUP_DATA_CALL, PROCESSER(responseSetupDataCall)},
    {RIL_REQUEST_SIM_IO, PROCESSER(responseICC_IO)},
    {RIL_REQUEST_SEND_USSD, PROCESSER(responseVoid)},
    {RIL_REQUEST_CANCEL_USSD, PROCESSER(responseVoid)},
    {RIL_REQUEST_GET_CLIR, PROCESSER(responseInts)},
    {RIL_REQUEST_SET_CLIR, PROCESSER(responseVoid)},
    {RIL_REQUEST_QUERY_CALL_FORWARD_STATUS, PROCESSER(responseCallForward)},
    {RIL_REQUEST_SET_CALL_FORWARD, PROCESSER(responseVoid)},
    {RIL_REQUEST_QUERY_CALL_WAITING, PROCESSER(responseInts)},
    {RIL_REQUEST_SET_CALL_WAITING, PROCESSER(responseVoid)},
    {RIL_REQUEST_SMS_ACKNOWLEDGE, PROCESSER(responseVoid)},
    {RIL_REQUEST_GET_IMEI, PROCESSER(responseString)},
    {RIL_REQUEST_GET_IMEISV, PROCESSER(responseString)},
    {RIL_REQUEST_ANSWER, PROCESSER(responseVoid)},
    {RIL_REQUEST_DEACTIVATE_DATA_CALL, PROCESSER(responseVoid)},
    {RIL_REQUEST_QUERY_FACILITY_LOCK, PROCESSER(responseInts)},
    {RIL_REQUEST_SET_FACILITY_LOCK, PROCESSER(responseInts)},
    {RIL_REQUEST_CHANGE_BARRING_PASSWORD, PROCESSER(responseVoid)},
    {RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE, PROCESSER(responseInts)},
    {RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC, PROCESSER(responseVoid)},
    {RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL, PROCESSER(responseVoid)},
    {RIL_REQUEST_QUERY_AVAILABLE_NETWORKS, PROCESSER(responseOperatorInfos)},
    {RIL_REQUEST_DTMF_START, PROCESSER(responseVoid)},
    {RIL_REQUEST_DTMF_STOP, PROCESSER(responseVoid)},
    {RIL_REQUEST_BASEBAND_VERSION, PROCESSER(responseString)},
    {RIL_REQUEST_SEPARATE_CONNECTION, PROCESSER(responseVoid)},
    {RIL_REQUEST_SET_MUTE, PROCESSER(responseVoid)},
    {RIL_REQUEST_GET_MUTE, PROCESSER(responseInts)},
    {RIL_REQUEST_QUERY_CLIP, PROCESSER(responseInts)},
    {RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE, PROCESSER(responseInts)},
    {RIL_REQUEST_DATA_CALL_LIST, PROCESSER(responseDataCallList)},
    {RIL_REQUEST_RESET_RADIO, PROCESSER(responseVoid)},
    {RIL_REQUEST_OEM_HOOK_RAW, PROCESSER(responseRaw)},
    {RIL_REQUEST_OEM_HOOK_STRINGS, PROCESSER(responseStrings)},
    {RIL_REQUEST_SCREEN_STATE, PROCESSER(responseVoid)},
    {RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION, PROCESSER(responseVoid)},
    {RIL_REQUEST_WRITE_SMS_TO_SIM, PROCESSER(responseInts)},
    {RIL_REQUEST_DELETE_SMS_ON_SIM, PROCESSER(responseVoid)},
    {RIL_REQUEST_SET_BAND_MODE, PROCESSER(responseVoid)},
    {RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE, PROCESSER(responseInts)},
    {RIL_REQUEST_STK_GET_PROFILE, PROCESSER(responseString)},
    {RIL_REQUEST_STK_SET_PROFILE, PROCESSER(responseVoid)},
    {RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND, PROCESSER(responseString)},
    {RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE, PROCESSER(responseVoid)},
    {RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM, PROCESSER(responseInts)},
    {RIL_REQUEST_EXPLICIT_CALL_TRANSFER, PROCESSER(responseVoid)},
    {RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE, PROCESSER(responseVoid)},
    {RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE, PROCESSER(responseGetPreferredNetworkType)},
    {RIL_REQUEST_GET_NEIGHBORING_CELL_IDS, PROCESSER(responseCellList)},
    {RIL_REQUEST_SET_LOCATION_UPDATES, PROCESSER(responseVoid)},
    {RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE, PROCESSER(responseVoid)},
    {RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE, PROCESSER(responseVoid)},
    {RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE, PROCESSER(responseInts)},
    {RIL_REQUEST_SET_TTY_MODE, PROCESSER(responseVoid)},
    {RIL_REQUEST_QUERY_TTY_MODE, PROCESSER(responseInts)},
    {RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE, PROCESSER(responseVoid)},
    {RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE, PROCESSER(responseInts)},
    {RIL_REQUEST_CDMA_FLASH, PROCESSER(responseVoid)},
    {RIL_REQUEST_CDMA_BURST_DTMF, PROCESSER(responseVoid)},
    {RIL_REQUEST_CDMA_SEND_SMS, PROCESSER(responseSMS)},
    {RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE, PROCESSER(responseVoid)},

    // {RIL_REQUEST_GSM_GET_BROADCAST_CONFIG, PROCESSER(responseGmsBroadcastConfig}},
    // {RIL_REQUEST_GSM_SET_BROADCAST_CONFIG, PROCESSER(responseVoid}},
    // {RIL_REQUEST_GSM_BROADCAST_ACTIVATION, PROCESSER(responseVoid}},
    // {RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG, PROCESSER(responseCdmaBroadcastConfig}},
    // {RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG, PROCESSER(responseVoid}},
    // {RIL_REQUEST_CDMA_BROADCAST_ACTIVATION, PROCESSER(responseVoid}},
    // {RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY, PROCESSER(responseVoid}},

    {RIL_REQUEST_CDMA_SUBSCRIPTION, PROCESSER(responseStrings)},
    {RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM, PROCESSER(responseInts)},
    {RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM, PROCESSER(responseVoid)},
    {RIL_REQUEST_DEVICE_IDENTITY, PROCESSER(responseStrings)},
    {RIL_REQUEST_GET_SMSC_ADDRESS, PROCESSER(responseString)},
    {RIL_REQUEST_SET_SMSC_ADDRESS, PROCESSER(responseVoid)},
    {RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE, PROCESSER(responseVoid)},
    {RIL_REQUEST_REPORT_SMS_MEMORY_STATUS, PROCESSER(responseVoid)},
    {RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING, PROCESSER(responseVoid)},
    {RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE, PROCESSER(responseInts)},
    {RIL_REQUEST_ISIM_AUTHENTICATION, PROCESSER(responseString)},
    {RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU, PROCESSER(responseVoid)},
    {RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS, PROCESSER(responseICC_IO)},
};

/* unsocilited response handlers */
static std::map<int, RILCProcesser> UnSocilitedResponseProcesser = {
    {RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED, PROCESSER(responseVoid)},
    {RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED, PROCESSER(responseVoid)},
    {RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED, PROCESSER(responseVoid)},
    {RIL_UNSOL_RESPONSE_NEW_SMS, PROCESSER(responseString)},
    {RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT, PROCESSER(responseString)},
    {RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM, PROCESSER(responseInts)},
    {RIL_UNSOL_ON_USSD, PROCESSER(responseStrings)},
    {RIL_UNSOL_NITZ_TIME_RECEIVED, PROCESSER(responseString)},
    {RIL_UNSOL_SIGNAL_STRENGTH, PROCESSER(responseSignalStrength)},
    {RIL_UNSOL_DATA_CALL_LIST_CHANGED, PROCESSER(responseDataCallList)},
    {RIL_UNSOL_SUPP_SVC_NOTIFICATION, PROCESSER(responseSuppServiceNotification)},
    {RIL_UNSOL_STK_SESSION_END, PROCESSER(responseVoid)},
    {RIL_UNSOL_STK_PROACTIVE_COMMAND, PROCESSER(responseString)},
    {RIL_UNSOL_STK_EVENT_NOTIFY, PROCESSER(responseString)},
    {RIL_UNSOL_STK_CALL_SETUP, PROCESSER(responseInts)},
    {RIL_UNSOL_SIM_SMS_STORAGE_FULL, PROCESSER(responseVoid)},
    {RIL_UNSOL_SIM_REFRESH, PROCESSER(responseInts)},
    {RIL_UNSOL_CALL_RING, PROCESSER(responseCallRing)},
    {RIL_UNSOL_RESTRICTED_STATE_CHANGED, PROCESSER(responseInts)},
    {RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED, PROCESSER(responseVoid)},
    {RIL_UNSOL_RESPONSE_CDMA_NEW_SMS, PROCESSER(responseCdmaSms)},
    {RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS, PROCESSER(responseRaw)},
    {RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL, PROCESSER(responseVoid)},
    {RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE, PROCESSER(responseVoid)},
    {RIL_UNSOL_CDMA_CALL_WAITING, PROCESSER(responseCdmaCallWaiting)},
    {RIL_UNSOL_CDMA_OTA_PROVISION_STATUS, PROCESSER(responseInts)},
    {RIL_UNSOL_CDMA_INFO_REC, PROCESSER(responseCdmaInformationRecord)},
    {RIL_UNSOL_OEM_HOOK_RAW, PROCESSER(responseRaw)},
    {RIL_UNSOL_RINGBACK_TONE, PROCESSER(responseInts)},
    {RIL_UNSOL_RESEND_INCALL_MUTE, PROCESSER(responseVoid)},
    {RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED, PROCESSER(responseInts)},
    {RIL_UNSOL_CDMA_PRL_CHANGED, PROCESSER(responseInts)},
    {RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE, PROCESSER(responseVoid)},
    {RIL_UNSOL_RIL_CONNECTED, PROCESSER(responseInts)},
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
    {RIL_EXT_UNSOL_ATROUTER_RSP, PROCESSER(responseString)},
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
