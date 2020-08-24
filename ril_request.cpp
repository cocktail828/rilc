#include <vector>

#include <assert.h>
#include <endian.h>

#include "ril_request.h"
#include "ril_response.h"
#include "logger.h"
#include "ril/ril.h"

/**
 * RIL Request
 */
DeviceManager *RILRequest::mDeviceMgr = nullptr;
int RILRequest::mGlobalRequestId = 0;
;
bool RILRequest::mReady = false;
std::mutex RILRequest::mGlobalLock;
RILResponse RILRequest::mUnsocilitedResponse;

static std::string requestidToString(int id)
{
    return std::to_string(id);
}

static std::string commandidToString(int cid)
{
    switch (cid)
    {
    case RIL_REQUEST_GET_SIM_STATUS:
        return "GET_SIM_STATUS";
    case RIL_REQUEST_ENTER_SIM_PIN:
        return "ENTER_SIM_PIN";
    case RIL_REQUEST_ENTER_SIM_PUK:
        return "ENTER_SIM_PUK";
    case RIL_REQUEST_ENTER_SIM_PIN2:
        return "ENTER_SIM_PIN2";
    case RIL_REQUEST_ENTER_SIM_PUK2:
        return "ENTER_SIM_PUK2";
    case RIL_REQUEST_CHANGE_SIM_PIN:
        return "CHANGE_SIM_PIN";
    case RIL_REQUEST_CHANGE_SIM_PIN2:
        return "CHANGE_SIM_PIN2";
    case RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION:
        return "ENTER_NETWORK_DEPERSONALIZATION";
    case RIL_REQUEST_GET_CURRENT_CALLS:
        return "GET_CURRENT_CALLS";
    case RIL_REQUEST_DIAL:
        return "DIAL";
    case RIL_REQUEST_GET_IMSI:
        return "GET_IMSI";
    case RIL_REQUEST_HANGUP:
        return "HANGUP";
    case RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND:
        return "HANGUP_WAITING_OR_BACKGROUND";
    case RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND:
        return "HANGUP_FOREGROUND_RESUME_BACKGROUND";
    case RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE:
        return "REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE";
    case RIL_REQUEST_CONFERENCE:
        return "CONFERENCE";
    case RIL_REQUEST_UDUB:
        return "UDUB";
    case RIL_REQUEST_LAST_CALL_FAIL_CAUSE:
        return "LAST_CALL_FAIL_CAUSE";
    case RIL_REQUEST_SIGNAL_STRENGTH:
        return "SIGNAL_STRENGTH";
    case RIL_REQUEST_VOICE_REGISTRATION_STATE:
        return "VOICE_REGISTRATION_STATE";
    case RIL_REQUEST_DATA_REGISTRATION_STATE:
        return "DATA_REGISTRATION_STATE";
    case RIL_REQUEST_OPERATOR:
        return "OPERATOR";
    case RIL_REQUEST_RADIO_POWER:
        return "RADIO_POWER";
    case RIL_REQUEST_DTMF:
        return "DTMF";
    case RIL_REQUEST_SEND_SMS:
        return "SEND_SMS";
    case RIL_REQUEST_SEND_SMS_EXPECT_MORE:
        return "SEND_SMS_EXPECT_MORE";
    case RIL_REQUEST_SETUP_DATA_CALL:
        return "SETUP_DATA_CALL";
    case RIL_REQUEST_SIM_IO:
        return "SIM_IO";
    case RIL_REQUEST_SEND_USSD:
        return "SEND_USSD";
    case RIL_REQUEST_CANCEL_USSD:
        return "CANCEL_USSD";
    case RIL_REQUEST_GET_CLIR:
        return "GET_CLIR";
    case RIL_REQUEST_SET_CLIR:
        return "SET_CLIR";
    case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS:
        return "QUERY_CALL_FORWARD_STATUS";
    case RIL_REQUEST_SET_CALL_FORWARD:
        return "SET_CALL_FORWARD";
    case RIL_REQUEST_QUERY_CALL_WAITING:
        return "QUERY_CALL_WAITING";
    case RIL_REQUEST_SET_CALL_WAITING:
        return "SET_CALL_WAITING";
    case RIL_REQUEST_SMS_ACKNOWLEDGE:
        return "SMS_ACKNOWLEDGE";
    case RIL_REQUEST_GET_IMEI:
        return "GET_IMEI";
    case RIL_REQUEST_GET_IMEISV:
        return "GET_IMEISV";
    case RIL_REQUEST_ANSWER:
        return "ANSWER";
    case RIL_REQUEST_DEACTIVATE_DATA_CALL:
        return "DEACTIVATE_DATA_CALL";
    case RIL_REQUEST_QUERY_FACILITY_LOCK:
        return "QUERY_FACILITY_LOCK";
    case RIL_REQUEST_SET_FACILITY_LOCK:
        return "SET_FACILITY_LOCK";
    case RIL_REQUEST_CHANGE_BARRING_PASSWORD:
        return "CHANGE_BARRING_PASSWORD";
    case RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE:
        return "QUERY_NETWORK_SELECTION_MODE";
    case RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC:
        return "SET_NETWORK_SELECTION_AUTOMATIC";
    case RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL:
        return "SET_NETWORK_SELECTION_MANUAL";
    case RIL_REQUEST_QUERY_AVAILABLE_NETWORKS:
        return "QUERY_AVAILABLE_NETWORKS ";
    case RIL_REQUEST_DTMF_START:
        return "DTMF_START";
    case RIL_REQUEST_DTMF_STOP:
        return "DTMF_STOP";
    case RIL_REQUEST_BASEBAND_VERSION:
        return "BASEBAND_VERSION";
    case RIL_REQUEST_SEPARATE_CONNECTION:
        return "SEPARATE_CONNECTION";
    case RIL_REQUEST_SET_MUTE:
        return "SET_MUTE";
    case RIL_REQUEST_GET_MUTE:
        return "GET_MUTE";
    case RIL_REQUEST_QUERY_CLIP:
        return "QUERY_CLIP";
    case RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE:
        return "LAST_DATA_CALL_FAIL_CAUSE";
    case RIL_REQUEST_DATA_CALL_LIST:
        return "DATA_CALL_LIST";
    case RIL_REQUEST_RESET_RADIO:
        return "RESET_RADIO";
    case RIL_REQUEST_OEM_HOOK_RAW:
        return "OEM_HOOK_RAW";
    case RIL_REQUEST_OEM_HOOK_STRINGS:
        return "OEM_HOOK_STRINGS";
    case RIL_REQUEST_SCREEN_STATE:
        return "SCREEN_STATE";
    case RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION:
        return "SET_SUPP_SVC_NOTIFICATION";
    case RIL_REQUEST_WRITE_SMS_TO_SIM:
        return "WRITE_SMS_TO_SIM";
    case RIL_REQUEST_DELETE_SMS_ON_SIM:
        return "DELETE_SMS_ON_SIM";
    case RIL_REQUEST_SET_BAND_MODE:
        return "SET_BAND_MODE";
    case RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE:
        return "QUERY_AVAILABLE_BAND_MODE";
    case RIL_REQUEST_STK_GET_PROFILE:
        return "REQUEST_STK_GET_PROFILE";
    case RIL_REQUEST_STK_SET_PROFILE:
        return "REQUEST_STK_SET_PROFILE";
    case RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND:
        return "REQUEST_STK_SEND_ENVELOPE_COMMAND";
    case RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE:
        return "REQUEST_STK_SEND_TERMINAL_RESPONSE";
    case RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM:
        return "REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM";
    case RIL_REQUEST_EXPLICIT_CALL_TRANSFER:
        return "REQUEST_EXPLICIT_CALL_TRANSFER";
    case RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE:
        return "REQUEST_SET_PREFERRED_NETWORK_TYPE";
    case RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE:
        return "REQUEST_GET_PREFERRED_NETWORK_TYPE";
    case RIL_REQUEST_GET_NEIGHBORING_CELL_IDS:
        return "REQUEST_GET_NEIGHBORING_CELL_IDS";
    case RIL_REQUEST_SET_LOCATION_UPDATES:
        return "REQUEST_SET_LOCATION_UPDATES";
    case RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE:
        return "RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE";
    case RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE:
        return "RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE";
    case RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE:
        return "RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE";
    case RIL_REQUEST_SET_TTY_MODE:
        return "RIL_REQUEST_SET_TTY_MODE";
    case RIL_REQUEST_QUERY_TTY_MODE:
        return "RIL_REQUEST_QUERY_TTY_MODE";
    case RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE:
        return "RIL_REQUEST_CDMA_SET_PREFEthisED_VOICE_PRIVACY_MODE";
    case RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE:
        return "RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE";
    case RIL_REQUEST_CDMA_FLASH:
        return "RIL_REQUEST_CDMA_FLASH";
    case RIL_REQUEST_CDMA_BURST_DTMF:
        return "RIL_REQUEST_CDMA_BURST_DTMF";
    case RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY:
        return "RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY";
    case RIL_REQUEST_CDMA_SEND_SMS:
        return "RIL_REQUEST_CDMA_SEND_SMS";
    case RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE:
        return "RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE";
    case RIL_REQUEST_GSM_GET_BROADCAST_SMS_CONFIG:
        return "RIL_REQUEST_GSM_GET_BROADCAST_SMS_CONFIG";
    case RIL_REQUEST_GSM_SET_BROADCAST_SMS_CONFIG:
        return "RIL_REQUEST_GSM_SET_BROADCAST_SMS_CONFIG";
    case RIL_REQUEST_GSM_SMS_BROADCAST_ACTIVATION:
        return "RIL_REQUEST_GSM_SMS_BROADCAST_ACTIVATION";
    case RIL_REQUEST_CDMA_GET_BROADCAST_SMS_CONFIG:
        return "RIL_REQUEST_CDMA_GET_BROADCAST_SMS_CONFIG";
    case RIL_REQUEST_CDMA_SET_BROADCAST_SMS_CONFIG:
        return "RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG";
    case RIL_REQUEST_CDMA_SMS_BROADCAST_ACTIVATION:
        return "RIL_REQUEST_CDMA_SMS_BROADCAST_ACTIVATION";
    case RIL_REQUEST_CDMA_SUBSCRIPTION:
        return "RIL_REQUEST_CDMA_SUBSCRIPTION";
    case RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM:
        return "RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM";
    case RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM:
        return "RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM";
    case RIL_REQUEST_DEVICE_IDENTITY:
        return "RIL_REQUEST_DEVICE_IDENTITY";
    case RIL_REQUEST_GET_SMSC_ADDRESS:
        return "RIL_REQUEST_GET_SMSC_ADDRESS";
    case RIL_REQUEST_SET_SMSC_ADDRESS:
        return "RIL_REQUEST_SET_SMSC_ADDRESS";
    case RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE:
        return "REQUEST_EXIT_EMERGENCY_CALLBACK_MODE";
    case RIL_REQUEST_REPORT_SMS_MEMORY_STATUS:
        return "RIL_REQUEST_REPORT_SMS_MEMORY_STATUS";
    case RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING:
        return "RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING";
    case RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE:
        return "RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE";
    case RIL_REQUEST_ISIM_AUTHENTICATION:
        return "RIL_REQUEST_ISIM_AUTHENTICATION";
    case RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU:
        return "RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU";
    case RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS:
        return "RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS";
    case RIL_REQUEST_VOICE_RADIO_TECH:
        return "RIL_REQUEST_VOICE_RADIO_TECH";
    case RIL_REQUEST_GET_CELL_INFO_LIST:
        return "RIL_REQUEST_GET_CELL_INFO_LIST";
    case RIL_REQUEST_SET_UNSOL_CELL_INFO_LIST_RATE:
        return "RIL_REQUEST_SET_UNSOL_CELL_INFO_LIST_RATE";
    case RIL_REQUEST_SET_INITIAL_ATTACH_APN:
        return "RIL_REQUEST_SET_INITIAL_ATTACH_APN";
    case RIL_REQUEST_IMS_REGISTRATION_STATE:
        return "RIL_REQUEST_IMS_REGISTRATION_STATE";
    case RIL_REQUEST_IMS_SEND_SMS:
        return "RIL_REQUEST_IMS_SEND_SMS";
    case RIL_REQUEST_SIM_TRANSMIT_APDU_BASIC:
        return "RIL_REQUEST_SIM_TRANSMIT_APDU_BASIC";
    case RIL_REQUEST_SIM_OPEN_CHANNEL:
        return "RIL_REQUEST_SIM_OPEN_CHANNEL";
    case RIL_REQUEST_SIM_CLOSE_CHANNEL:
        return "RIL_REQUEST_SIM_CLOSE_CHANNEL";
    case RIL_REQUEST_SIM_TRANSMIT_APDU_CHANNEL:
        return "RIL_REQUEST_SIM_TRANSMIT_APDU_CHANNEL";
    case RIL_REQUEST_NV_READ_ITEM:
        return "RIL_REQUEST_NV_READ_ITEM";
    case RIL_REQUEST_NV_WRITE_ITEM:
        return "RIL_REQUEST_NV_WRITE_ITEM";
    case RIL_REQUEST_NV_WRITE_CDMA_PRL:
        return "RIL_REQUEST_NV_WRITE_CDMA_PRL";
    case RIL_REQUEST_NV_RESET_CONFIG:
        return "RIL_REQUEST_NV_RESET_CONFIG";
    case RIL_REQUEST_SET_UICC_SUBSCRIPTION:
        return "RIL_REQUEST_SET_UICC_SUBSCRIPTION";
    case RIL_REQUEST_ALLOW_DATA:
        return "RIL_REQUEST_ALLOW_DATA";
    case RIL_REQUEST_GET_HARDWARE_CONFIG:
        return "RIL_REQUEST_GET_HARDWARE_CONFIG";
    case RIL_REQUEST_SIM_AUTHENTICATION:
        return "RIL_REQUEST_SIM_AUTHENTICATION";
    case RIL_REQUEST_GET_DC_RT_INFO:
        return "RIL_REQUEST_GET_DC_RT_INFO";
    case RIL_REQUEST_SET_DC_RT_INFO_RATE:
        return "RIL_REQUEST_SET_DC_RT_INFO_RATE";
    case RIL_REQUEST_SET_DATA_PROFILE:
        return "RIL_REQUEST_SET_DATA_PROFILE";
    case RIL_REQUEST_SHUTDOWN:
        return "RIL_REQUEST_SHUTDOWN";
    case RIL_REQUEST_GET_RADIO_CAPABILITY:
        return "RIL_REQUEST_GET_RADIO_CAPABILITY";
    case RIL_REQUEST_SET_RADIO_CAPABILITY:
        return "RIL_REQUEST_SET_RADIO_CAPABILITY";
    case RIL_REQUEST_START_LCE:
        return "RIL_REQUEST_START_LCE";
    case RIL_REQUEST_STOP_LCE:
        return "RIL_REQUEST_STOP_LCE";
    case RIL_REQUEST_PULL_LCEDATA:
        return "RIL_REQUEST_PULL_LCEDATA";
    case RIL_REQUEST_GET_ACTIVITY_INFO:
        return "RIL_REQUEST_GET_ACTIVITY_INFO";

        /**
         * IMS REQUESTS
         */
    case RIL_REQUEST_GET_IMS_CURRENT_CALLS:
        return "RIL_REQUEST_GET_IMS_CURRENT_CALLS";
    case RIL_REQUEST_SET_IMS_VOICE_CALL_AVAILABILITY:
        return "RIL_REQUEST_SET_IMS_VOICE_CALL_AVAILABILITY";
    case RIL_REQUEST_GET_IMS_VOICE_CALL_AVAILABILITY:
        return "RIL_REQUEST_GET_IMS_VOICE_CALL_AVAILABILITY";
    case RIL_REQUEST_INIT_ISIM:
        return "RIL_REQUEST_INIT_ISIM";
    case RIL_REQUEST_IMS_CALL_REQUEST_MEDIA_CHANGE:
        return "RIL_REQUEST_IMS_CALL_REQUEST_MEDIA_CHANGE";
    case RIL_REQUEST_IMS_CALL_RESPONSE_MEDIA_CHANGE:
        return "RIL_REQUEST_IMS_CALL_RESPONSE_MEDIA_CHANGE";
    case RIL_REQUEST_SET_IMS_SMSC:
        return "RIL_REQUEST_SET_IMS_SMSC";
    case RIL_REQUEST_IMS_CALL_FALL_BACK_TO_VOICE:
        return "RIL_REQUEST_IMS_CALL_FALL_BACK_TO_VOICE";
    case RIL_REQUEST_SET_IMS_INITIAL_ATTACH_APN:
        return "RIL_REQUEST_SET_IMS_INITIAL_ATTACH_APN";
    case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS_URI:
        return "RIL_REQUEST_QUERY_CALL_FORWARD_STATUS_URI";
    case RIL_REQUEST_SET_CALL_FORWARD_URI:
        return "RIL_REQUEST_SET_CALL_FORWARD_URI";
    case RIL_REQUEST_IMS_INITIAL_GROUP_CALL:
        return "RIL_REQUEST_IMS_INITIAL_GROUP_CALL";
    case RIL_REQUEST_IMS_ADD_TO_GROUP_CALL:
        return "RIL_REQUEST_IMS_ADD_TO_GROUP_CALL";
    case RIL_REQUEST_VIDEOPHONE_DIAL:
        return "RIL_REQUEST_VIDEOPHONE_DIAL";
    case RIL_REQUEST_ENABLE_IMS:
        return "RIL_REQUEST_ENABLE_IMS";
    case RIL_REQUEST_DISABLE_IMS:
        return "RIL_REQUEST_DISABLE_IMS";
    case RIL_REQUEST_GET_IMS_BEARER_STATE:
        return "RIL_REQUEST_GET_IMS_BEARER_STATE";
    case RIL_REQUEST_VIDEOPHONE_CODEC:
        return "RIL_REQUEST_VIDEOPHONE_CODEC";
    case RIL_REQUEST_SET_SOS_INITIAL_ATTACH_APN:
        return "RIL_REQUEST_SET_SOS_INITIAL_ATTACH_APN";
    case RIL_REQUEST_IMS_HANDOVER:
        return "RIL_REQUEST_IMS_HANDOVER";
    case RIL_REQUEST_IMS_HANDOVER_STATUS_UPDATE:
        return "RIL_REQUEST_IMS_HANDOVER_STATUS_UPDATE";
    case RIL_REQUEST_IMS_NETWORK_INFO_CHANGE:
        return "RIL_REQUEST_IMS_NETWORK_INFO_CHANGE";
    case RIL_REQUEST_IMS_HANDOVER_CALL_END:
        return "RIL_REQUEST_IMS_HANDOVER_CALL_END";
    case RIL_REQUEST_GET_TPMR_STATE:
        return "RIL_REQUEST_GET_TPMR_STATE";
    case RIL_REQUEST_SET_TPMR_STATE:
        return "RIL_REQUEST_SET_TPMR_STATE";
    case RIL_REQUEST_IMS_WIFI_ENABLE:
        return "RIL_REQUEST_IMS_WIFI_ENABLE";
    case RIL_REQUEST_IMS_WIFI_CALL_STATE_CHANGE:
        return "RIL_REQUEST_IMS_WIFI_CALL_STATE_CHANGE";
    case RIL_REQUEST_IMS_UPDATE_DATA_ROUTER:
        return "RIL_REQUEST_IMS_UPDATE_DATA_ROUTER";
    case RIL_REQUEST_IMS_HOLD_SINGLE_CALL:
        return "RIL_REQUEST_IMS_HOLD_SINGLE_CALL";
    case RIL_REQUEST_IMS_MUTE_SINGLE_CALL:
        return "RIL_REQUEST_IMS_MUTE_SINGLE_CALL";
    case RIL_REQUEST_IMS_SILENCE_SINGLE_CALL:
        return "RIL_REQUEST_IMS_SILENCE_SINGLE_CALL";
    case RIL_REQUEST_IMS_ENABLE_LOCAL_CONFERENCE:
        return "RIL_REQUEST_IMS_ENABLE_LOCAL_CONFERENCE";
    case RIL_REQUEST_IMS_NOTIFY_HANDOVER_CALL_INFO:
        return "RIL_REQUEST_IMS_NOTIFY_HANDOVER_CALL_INFO";
    case RIL_REQUEST_GET_IMS_SRVCC_CAPBILITY:
        return "RIL_REQUEST_GET_IMS_SRVCC_CAPBILITY";
    case RIL_REQUEST_GET_IMS_PCSCF_ADDR:
        return "RIL_REQUEST_GET_IMS_PCSCF_ADDR";
    case RIL_REQUEST_SET_VOWIFI_PCSCF_ADDR:
        return "RIL_REQUEST_SET_VOWIFI_PCSCF_ADDR";
    case RIL_REQUEST_IMS_UPDATE_CLIP:
        return "RIL_REQUEST_IMS_UPDATE_CLIP";
    case RIL_REQUEST_IMS_REGADDR:
        return "RIL_REQUEST_IMS_REGADDR";
    case RIL_EXT_REQUEST_VIDEOPHONE_DIAL:
        return "RIL_EXT_REQUEST_VIDEOPHONE_DIAL";
    case RIL_EXT_REQUEST_VIDEOPHONE_CODEC:
        return "RIL_EXT_REQUEST_VIDEOPHONE_CODEC";
    case RIL_EXT_REQUEST_VIDEOPHONE_FALLBACK:
        return "RIL_EXT_REQUEST_VIDEOPHONE_FALLBACK";
    case RIL_EXT_REQUEST_VIDEOPHONE_STRING:
        return "RIL_EXT_REQUEST_VIDEOPHONE_STRING";
    case RIL_EXT_REQUEST_VIDEOPHONE_LOCAL_MEDIA:
        return "RIL_EXT_REQUEST_VIDEOPHONE_LOCAL_MEDIA";
    case RIL_EXT_REQUEST_VIDEOPHONE_CONTROL_IFRAME:
        return "RIL_EXT_REQUEST_VIDEOPHONE_CONTROL_IFRAME";
    case RIL_EXT_REQUEST_SWITCH_MULTI_CALL:
        return "RIL_EXT_REQUEST_SWITCH_MULTI_CALL";
    case RIL_EXT_REQUEST_TRAFFIC_CLASS:
        return "RIL_EXT_REQUEST_TRAFFIC_CLASS";
    case RIL_EXT_REQUEST_ENABLE_LTE:
        return "RIL_EXT_REQUEST_ENABLE_LTE";
    case RIL_EXT_REQUEST_ATTACH_DATA:
        return "RIL_EXT_REQUEST_ATTACH_DATA";
    case RIL_EXT_REQUEST_STOP_QUERY_NETWORK:
        return "RIL_EXT_REQUEST_STOP_QUERY_NETWORK";
    case RIL_EXT_REQUEST_FORCE_DETACH:
        return "RIL_EXT_REQUEST_FORCE_DETACH";
    case RIL_EXT_REQUEST_GET_HD_VOICE_STATE:
        return "RIL_EXT_REQUEST_GET_HD_VOICE_STATE";
    case RIL_EXT_REQUEST_SIMMGR_SIM_POWER:
        return "RIL_EXT_REQUEST_SIMMGR_SIM_POWER";
    case RIL_EXT_REQUEST_ENABLE_RAU_NOTIFY:
        return "RIL_EXT_REQUEST_ENABLE_RAU_NOTIFY";
    case RIL_EXT_REQUEST_SET_COLP:
        return "RIL_EXT_REQUEST_SET_COLP";
    case RIL_EXT_REQUEST_GET_DEFAULT_NAN:
        return "RIL_EXT_REQUEST_GET_DEFAULT_NAN";
    case RIL_EXT_REQUEST_SIM_GET_ATR:
        return "RIL_EXT_REQUEST_SIM_GET_ATR";
    case RIL_EXT_REQUEST_SIM_OPEN_CHANNEL_WITH_P2:
        return "RIL_EXT_REQUEST_SIM_OPEN_CHANNEL_WITH_P2";
    case RIL_EXT_REQUEST_GET_SIM_CAPACITY:
        return "RIL_EXT_REQUEST_GET_SIM_CAPACITY";
    case RIL_EXT_REQUEST_STORE_SMS_TO_SIM:
        return "RIL_EXT_REQUEST_STORE_SMS_TO_SIM";
    case RIL_EXT_REQUEST_QUERY_SMS_STORAGE_MODE:
        return "RIL_EXT_REQUEST_QUERY_SMS_STORAGE_MODE";
    case RIL_EXT_REQUEST_GET_SIMLOCK_REMAIN_TIMES:
        return "RIL_EXT_REQUEST_GET_SIMLOCK_REMAIN_TIMES";
    case RIL_EXT_REQUEST_SET_FACILITY_LOCK_FOR_USER:
        return "RIL_EXT_REQUEST_SET_FACILITY_LOCK_FOR_USER";
    case RIL_EXT_REQUEST_GET_SIMLOCK_STATUS:
        return "RIL_EXT_REQUEST_GET_SIMLOCK_STATUS";
    case RIL_EXT_REQUEST_GET_SIMLOCK_DUMMYS:
        return "RIL_EXT_REQUEST_GET_SIMLOCK_DUMMYS";
    case RIL_EXT_REQUEST_GET_SIMLOCK_WHITE_LIST:
        return "RIL_EXT_REQUEST_GET_SIMLOCK_WHITE_LIST";
    case RIL_EXT_REQUEST_UPDATE_ECCLIST:
        return "RIL_EXT_REQUEST_UPDATE_ECCLIST";
    case RIL_EXT_REQUEST_GET_BAND_INFO:
        return "RIL_EXT_REQUEST_GET_BAND_INFO";
    case RIL_EXT_REQUEST_SET_BAND_INFO_MODE:
        return "RIL_EXT_REQUEST_SET_BAND_INFO_MODE";
    case RIL_EXT_REQUEST_SET_SINGLE_PDN:
        return "RIL_EXT_REQUEST_SET_SINGLE_PDN";
    case RIL_EXT_REQUEST_SET_SPECIAL_RATCAP:
        return "RIL_EXT_REQUEST_SET_SPECIAL_RATCAP";
    case RIL_EXT_REQUEST_QUERY_COLP:
        return "RIL_EXT_REQUEST_QUERY_COLP";
    case RIL_EXT_REQUEST_QUERY_COLR:
        return "RIL_EXT_REQUEST_QUERY_COLR";
    case RIL_EXT_REQUEST_MMI_ENTER_SIM:
        return "RIL_EXT_REQUEST_MMI_ENTER_SIM";
    case RIL_EXT_REQUEST_UPDATE_OPERATOR_NAME:
        return "RIL_EXT_REQUEST_UPDATE_OPERATOR_NAME";
    case RIL_EXT_REQUEST_SIMMGR_GET_SIM_STATUS:
        return "RIL_EXT_REQUEST_SIMMGR_GET_SIM_STATUS";
    case RIL_EXT_REQUEST_SET_XCAP_IP_ADDR:
        return "RIL_EXT_REQUEST_SET_XCAP_IP_ADDR";
    case RIL_EXT_REQUEST_REATTACH:
        return "RIL_EXT_REQUEST_REATTACH";
    case RIL_EXT_REQUEST_SET_VOICE_DOMAIN:
        return "RIL_EXT_REQUEST_SET_VOICE_DOMAIN";
    case RIL_EXT_REQUEST_SET_SMS_BEARER:
        return "RIL_EXT_REQUEST_SET_SMS_BEARER";
    case RIL_EXT_REQUEST_SET_IMEI:
        return "RIL_EXT_REQUEST_SET_IMEI";
    case RIL_EXT_REQUEST_SET_IMEISV:
        return "RIL_EXT_REQUEST_SET_IMEISV";
    case RIL_EXT_REQUEST_QUERY_LTE_CTCC:
        return "RIL_EXT_REQUEST_QUERY_LTE_CTCC";
    case RIL_EXT_REQUEST_QUERY_LTE_CTCC_SINR:
        return "RIL_EXT_REQUEST_QUERY_LTE_CTCC_SINR";
    case RIL_EXT_REQUEST_QUERY_LTE_CTCC_MMEI:
        return "RIL_EXT_REQUEST_QUERY_LTE_CTCC_MMEI";
    case RIL_EXT_REQUEST_SET_GSM_BAND:
        return "RIL_EXT_REQUEST_SET_GSM_BAND";
    case RIL_EXT_REQUEST_SET_WCDMA_BAND:
        return "RIL_EXT_REQUEST_SET_WCDMA_BAND";
    case RIL_EXT_REQUEST_SET_LTE_BAND:
        return "RIL_EXT_REQUEST_SET_LTE_BAND";
#ifdef ORCA_FEATURE_5G
    case RIL_EXT_REQUEST_DATA_REGISTRATION_STATE:
        return "RIL_EXT_REQUEST_DATA_REGISTRATION_STATE";
    case RIL_EXT_REQUEST_EVALUATE_URSP:
        return "RIL_EXT_REQUEST_EVALUATE_URSP";
    case RIL_EXT_REQUEST_SETUP_DATA_CALL:
        return "RIL_EXT_REQUEST_SETUP_DATA_CALL";
    case RIL_EXT_REQUEST_GET_CELL_INFO_LIST:
        return "RIL_EXT_REQUEST_GET_CELL_INFO_LIST";
    case RIL_EXT_REQUEST_SIGNAL_STRENGTH:
        return "RIL_EXT_REQUEST_SIGNAL_STRENGTH";
    case RIL_EXT_REQUEST_SET_NR_BAND:
        return "RIL_EXT_REQUEST_SET_NR_BAND";
#endif
    default:
        return "<unknown request>";
    }
}

RILRequest::RILRequest(RILResponse *resp)
    : IObserver(),
      mRequestId(0),
      mCommandId(0),
      mResponse(resp) {}

RILRequest::RILRequest()
    : IObserver(),
      mRequestId(0),
      mCommandId(0),
      mResponse(nullptr) {}

RILRequest::~RILRequest()
{
    /**
     * sometimes user may new an instance to make a request
     * we should make sure, the instance is detached when destroy
     */
    if (mDeviceMgr && mAttachState)
        mDeviceMgr->detach(this);
}

/**
 * use dto build an new request will only 'command id'
 */
void RILRequest::obtain(int cid)
{
    mRequestId = ++mGlobalRequestId;
    mCommandId = cid;

    /* marshal command id */
    mParcel.writeInt32(cid);

    /* marshal request id */
    mParcel.writeInt32(mRequestId);

    /**
     * no phone ID on android
     */
    // /* marshal phone id */
    // if (mCommandId == RIL_REQUEST_OEM_HOOK_STRINGS ||
    //     mCommandId == RIL_REQUEST_SETUP_DATA_CALL ||
    //     mCommandId == RIL_REQUEST_DEACTIVATE_DATA_CALL)
    mParcel.writeInt32(0);
}

/**
 * Notice, the instance is an static variable,
 * which means, it's the same for all instances of the class.
 * for all instances shared the same DevciceManager and mGlobalRequestId
 */
RILRequest &RILRequest::instance()
{
    static RILRequest instance_;
    return instance_;
}

/**
 * start a new polling thread for read.
 * the thread is need for reading response and send requests
 */
bool RILRequest::init(const char *device)
{
    assert(device != nullptr);

    mGlobalRequestId = 0;
    if (!mDeviceMgr)
    {
        mDeviceMgr = new (std::nothrow) DeviceManager(device);
        if (!mDeviceMgr)
            return false;
    }

    if (!mDeviceMgr->openDevice())
        return false;

    for (int times = 0; times < 10; times++)
    {
        if (mDeviceMgr->isReady())
            return true;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return false;
}

/**
 * clean up what is created in 'init' function
 */
bool RILRequest::uninit()
{
    if (mDeviceMgr && mDeviceMgr->closeDevice())
    {
        delete mDeviceMgr;
        mDeviceMgr = nullptr;
        return true;
    }

    return false;
}

/**
 * check whether the DeviceManager is ready for send and read
 */
bool RILRequest::isReady()
{
    mReady = mDeviceMgr && mDeviceMgr->isReady();
    return mReady;
}

void RILRequest::resetGlobalRequest()
{
    std::lock_guard<std::mutex> _lk(mGlobalLock);
    mGlobalRequestId = 0;
}

/**
 * send requests. if success, the request will be add the observer list
 * so it can be notified, if it's response reachs
 */
bool RILRequest::blockSend(RILRequest *rr)
{
    std::unique_lock<std::mutex> _lk(rr->mRequestLock);

    if (mDeviceMgr && mDeviceMgr->isReady())
    {
        // parcel length in big endian
        uint32_t dataLength = htobe32(rr->mParcel.dataSize());

        mDeviceMgr->sendAsync(&dataLength, 4);

        mDeviceMgr->sendAsync(
            reinterpret_cast<const void *>(rr->mParcel.data()),
            rr->mParcel.dataSize());
        mDeviceMgr->attach(rr);

        if (rr->mRequestCond.wait_for(_lk, std::chrono::seconds(5)) == std::cv_status::timeout)
        {
            LOGE << requestidToString(rr->getRequestId()) << "> "
                 << commandidToString(rr->getCommandId()) << " timeout" << ENDL;
            mDeviceMgr->detach(rr);
        }
        return true;
    }
    else
    {
        LOGE << "device is not ready" << ENDL;
    }
    return false;
}

bool RILRequest::nonblockSend(RILRequest *rr)
{
    std::unique_lock<std::mutex> _lk(rr->mRequestLock);

    if (mDeviceMgr && mDeviceMgr->isReady() && !mDeviceMgr->isListFull())
    {
        // parcel length in big endian
        uint32_t dataLength = htobe32(rr->mParcel.dataSize());

        mDeviceMgr->sendAsync(&dataLength, 4);

        mDeviceMgr->sendAsync(
            reinterpret_cast<const void *>(rr->mParcel.data()),
            rr->mParcel.dataSize());
        mDeviceMgr->attach(rr);

        // nonblock return immediately
        return true;
    }
    else
    {
        LOGE << "device is not ready or too many requests" << ENDL;
    }
    return false;
}

/**
 * When get some message from DeviceManager, this function will be called
 */
void RILRequest::update(Parcel &p)
{
    /* oops! device manager is destroyed */
    if (p.dataSize() == 0)
    {
        LOGW << "null response get, device connect may be broken" << ENDL;
    }
    else
    {
        processSolicited(this, p);
    }

    return;
}

int RILRequest::getRequestId()
{
    return mRequestId;
}

int RILRequest::getCommandId()
{
    return mCommandId;
}

void RILRequest::recycle()
{
    mCommandId = 0;
    mRequestId = 0;
    mParcel.recycle();
}

int RILRequest::getIccCardStatus()
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_GET_SIM_STATUS);

    LOGI << requestidToString(getRequestId()) << "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::supplyIccPin(std::string pin)
{
    return supplyIccPinForApp(pin, "");
}

int RILRequest::supplyIccPinForApp(std::string pin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PIN);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(2);
    mParcel.writeString(pin.c_str());
    mParcel.writeString(aid.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::supplyIccPuk(std::string puk, std::string newPin)
{
    return supplyIccPukForApp(puk, newPin, "");
}

int RILRequest::supplyIccPukForApp(std::string puk, std::string newPin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PUK);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(3);
    mParcel.writeString(puk.c_str());
    mParcel.writeString(newPin.c_str());
    mParcel.writeString(aid.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::supplyIccPin2(std::string pin)
{
    return supplyIccPin2ForApp(pin, "");
}

int RILRequest::supplyIccPin2ForApp(std::string pin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PIN2);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(2);
    mParcel.writeString(pin.c_str());
    mParcel.writeString(aid.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::supplyIccPuk2(std::string puk2, std::string newPin2)
{
    return supplyIccPuk2ForApp(puk2, newPin2, "");
}

int RILRequest::supplyIccPuk2ForApp(std::string puk, std::string newPin2, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_ENTER_SIM_PUK2);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(3);
    mParcel.writeString(puk.c_str());
    mParcel.writeString(newPin2.c_str());
    mParcel.writeString(aid.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::changeIccPin(std::string oldPin, std::string newPin)
{
    return changeIccPinForApp(oldPin, newPin, "");
}

int RILRequest::changeIccPinForApp(std::string oldPin, std::string newPin, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_CHANGE_SIM_PIN);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(3);
    mParcel.writeString(oldPin.c_str());
    mParcel.writeString(newPin.c_str());
    mParcel.writeString(aid.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::changeIccPin2(std::string oldPin2, std::string newPin2)
{
    return changeIccPin2ForApp(oldPin2, newPin2, "");
}

int RILRequest::changeIccPin2ForApp(std::string oldPin2, std::string newPin2, std::string aid)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_CHANGE_SIM_PIN2);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(3);
    mParcel.writeString(oldPin2.c_str());
    mParcel.writeString(newPin2.c_str());
    mParcel.writeString(aid.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::changeBarringPassword(std::string facility, std::string oldPwd, std::string newPwd)
{
    obtain(RIL_REQUEST_CHANGE_BARRING_PASSWORD);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(3);
    mParcel.writeString(facility.c_str());
    mParcel.writeString(oldPwd.c_str());
    mParcel.writeString(newPwd.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::supplyNetworkDepersonalization(std::string netpin)
{
    obtain(RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(1);
    mParcel.writeString(netpin.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getCurrentCalls()
{
    obtain(RIL_REQUEST_GET_CURRENT_CALLS);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

__attribute_deprecated__ int RILRequest::getPDPContextList()
{
    return getDataCallList();
}

int RILRequest::getDataCallList()
{
    obtain(RIL_REQUEST_DATA_CALL_LIST);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::dial(std::string address, int clirMode)
{
    return dial(address, clirMode, nullptr);
}

int RILRequest::dial(std::string address, int clirMode, RIL_UUS_Info *uusInfo)
{
    obtain(RIL_REQUEST_DIAL);

    mParcel.writeString(address.c_str());
    mParcel.writeInt32(clirMode);

    if (uusInfo == nullptr)
    {
        mParcel.writeInt32(0); // UUS information is absent
    }
    else
    {
        // mParcel.writeInt32(1); // UUS information is present
        // mParcel.writeInt32(uusInfo.getType());
        // mParcel.writeInt32(uusInfo.getDcs());
        // mParcel.writeByteAarray(uusInfo.getUserData());
    }

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

/**
 * Be careful, insert SIM card, before call this function
 * or the rild will dump
 */
int RILRequest::getIMSI()
{
    obtain(RIL_REQUEST_GET_IMSI);

    mParcel.writeInt32(0);
    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getIMEI()
{
    obtain(RIL_REQUEST_GET_IMEI);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getIMEISV()
{
    obtain(RIL_REQUEST_GET_IMEISV);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::hangupConnection(int gsmIndex)
{
    LOGFW("hangupConnection: gsmIndex = ", gsmIndex);

    obtain(RIL_REQUEST_HANGUP);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << gsmIndex << ENDL;

    mParcel.writeInt32(1);
    mParcel.writeInt32(gsmIndex);

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::hangupWaitingOrBackground()
{
    obtain(RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::hangupForegroundResumeBackground()
{
    obtain(RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::switchWaitingOrHoldingAndActive()
{
    obtain(RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::conference()
{
    obtain(RIL_REQUEST_CONFERENCE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setPreferredVoicePrivacy(bool enable)
{
    obtain(RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE);

    mParcel.writeInt32(1);
    mParcel.writeInt32(enable ? 1 : 0);

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getPreferredVoicePrivacy()
{
    obtain(RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE);

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::separateConnection(int gsmIndex)
{
    obtain(RIL_REQUEST_SEPARATE_CONNECTION);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << gsmIndex << ENDL;

    mParcel.writeInt32(1);
    mParcel.writeInt32(gsmIndex);

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::acceptCall()
{
    obtain(RIL_REQUEST_ANSWER);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::rejectCall()
{
    obtain(RIL_REQUEST_UDUB);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::explicitCallTransfer()
{
    obtain(RIL_REQUEST_EXPLICIT_CALL_TRANSFER);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getLastCallFailCause()
{
    obtain(RIL_REQUEST_LAST_CALL_FAIL_CAUSE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

__attribute_deprecated__ int RILRequest::getLastPdpFailCause()
{
    return getLastDataCallFailCause();
}

/**
 * The prefethised new(std::nothrow) alternative to getLastPdpFailCause
 */
int RILRequest::getLastDataCallFailCause()
{
    obtain(RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setMute(bool enableMute)
{
    obtain(RIL_REQUEST_SET_MUTE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << enableMute << ENDL;

    mParcel.writeInt32(1);
    mParcel.writeInt32(enableMute ? 1 : 0);

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getMute()
{
    obtain(RIL_REQUEST_GET_MUTE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getSignalStrength()
{
    obtain(RIL_REQUEST_SIGNAL_STRENGTH);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getVoiceRegistrationState()
{
    obtain(RIL_REQUEST_VOICE_REGISTRATION_STATE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getDataRegistrationState()
{
    obtain(RIL_REQUEST_DATA_REGISTRATION_STATE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getOperator()
{
    obtain(RIL_REQUEST_OPERATOR);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::sendDtmf(char c)
{
    obtain(RIL_REQUEST_DTMF);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeString(std::to_string(int(c)).c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::startDtmf(char c)
{
    obtain(RIL_REQUEST_DTMF_START);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeString(std::to_string(int(c)).c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::stopDtmf()
{
    obtain(RIL_REQUEST_DTMF_STOP);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::sendBurstDtmf(std::string dtmfString, int on, int off)
{
    obtain(RIL_REQUEST_CDMA_BURST_DTMF);

    mParcel.writeInt32(3);
    mParcel.writeString(dtmfString.c_str());
    mParcel.writeString(std::to_string(on).c_str());
    mParcel.writeString(std::to_string(off).c_str());

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << dtmfString << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::sendSMS(std::string smscPDU, std::string pdu)
{
    obtain(RIL_REQUEST_SEND_SMS);

    mParcel.writeInt32(2);
    mParcel.writeString(smscPDU.c_str());
    mParcel.writeString(pdu.c_str());

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

// int RILRequest::sendCdmaSms(uint8_t *pdu)
// {
//     int address_nbr_of_digits;
//     int subaddr_nbr_of_digits;
//     int bearerDataLength;
//     ByteAthisayInputStream bais = new(std::nothrow) ByteAthisayInputStream(pdu);
//     DataInputStream dis = new(std::nothrow) DataInputStream(bais);

//     obtain(//            RIL_REQUEST_CDMA_SEND_SMS,
//            result);

//     try
//     {
//         mParcel.writeInt32(dis.readInt32());        //teleServiceId
//         mParcel.writeByte((byte)dis.readInt32()); //servicePresent
//         mParcel.writeInt32(dis.readInt32());        //serviceCategory
//         mParcel.writeInt32(dis.read());           //address_digit_mode
//         mParcel.writeInt32(dis.read());           //address_nbr_mode
//         mParcel.writeInt32(dis.read());           //address_ton
//         mParcel.writeInt32(dis.read());           //address_nbr_plan
//         address_nbr_of_digits = (byte)dis.read();
//         mParcel.writeByte((byte)address_nbr_of_digits);
//         for (int i = 0; i < address_nbr_of_digits; i++)
//         {
//             mParcel.writeByte(dis.readByte()); // address_orig_bytes[i]
//         }
//         mParcel.writeInt32(dis.read());        //subaddressType
//         mParcel.writeByte((byte)dis.read()); //subaddr_odd
//         subaddr_nbr_of_digits = (byte)dis.read();
//         mParcel.writeByte((byte)subaddr_nbr_of_digits);
//         for (int i = 0; i < subaddr_nbr_of_digits; i++)
//         {
//             mParcel.writeByte(dis.readByte()); //subaddr_orig_bytes[i]
//         }

//         bearerDataLength = dis.read();
//         mParcel.writeInt32(bearerDataLength);
//         for (int i = 0; i < bearerDataLength; i++)
//         {
//             mParcel.writeByte(dis.readByte()); //bearerData[i]
//         }
//     }
//     catch (IOException ex)
//     {

//         riljLog("sendSmsCdma: conversion from input stream to object failed: " + ex);
//     }

//     LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
//     mResponse = result;
// }

int RILRequest::deleteSmsOnSim(int index)
{
    obtain(RIL_REQUEST_DELETE_SMS_ON_SIM);

    mParcel.writeInt32(1);
    mParcel.writeInt32(index);

    if (false)
        LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << index << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::deleteSmsOnRuim(int index)
{
    obtain(RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM);

    mParcel.writeInt32(1);
    mParcel.writeInt32(index);

    if (false)
        LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << index << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

/** Free space (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_FREE = 0;

/** Received and read (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_READ = 1;

/** Received and unread (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_UNREAD = 3;

/** Stored and sent (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_SENT = 5;

/** Stored and unsent (TS 51.011 10.5.3 / 3GPP2 C.S0023 3.4.27). */
static const int STATUS_ON_ICC_UNSENT = 7;
int RILRequest::translateStatus(int status)
{
    switch (status & 0x7)
    {
    case STATUS_ON_ICC_READ:
        return 1;
    case STATUS_ON_ICC_UNREAD:
        return 0;
    case STATUS_ON_ICC_SENT:
        return 3;
    case STATUS_ON_ICC_UNSENT:
        return 2;
    }

    // Default to READ.
    return 1;
}

int RILRequest::writeSmsToSim(int status, std::string smsc, std::string pdu)
{
    status = translateStatus(status);

    obtain(RIL_REQUEST_WRITE_SMS_TO_SIM);

    mParcel.writeInt32(status);
    mParcel.writeString(pdu.c_str());
    mParcel.writeString(smsc.c_str());

    if (false)
        LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << status << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::writeSmsToRuim(int status, std::string pdu)
{
    status = translateStatus(status);

    obtain(RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM);

    mParcel.writeInt32(status);
    mParcel.writeString(pdu.c_str());

    if (false)
        LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << status << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setupDataCall(std::string radioTechnology, std::string profile, std::string apn,
                              std::string user, std::string password, std::string authType, std::string protocol)
{
    obtain(RIL_REQUEST_SETUP_DATA_CALL);

    mParcel.writeInt32(7);

    mParcel.writeString(radioTechnology.c_str());
    mParcel.writeString(profile.c_str());
    mParcel.writeString(apn.c_str());
    mParcel.writeString(user.c_str());
    mParcel.writeString(password.c_str());
    mParcel.writeString(authType.c_str());
    mParcel.writeString(protocol.c_str());

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " "
         << radioTechnology + " " + profile + " " + apn + " " + user + " "
         << password + " " + authType + " " + protocol << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::deactivateDataCall(int cid, int reason)
{
    obtain(RIL_REQUEST_DEACTIVATE_DATA_CALL);

    mParcel.writeInt32(2);
    mParcel.writeString(std::to_string(cid).c_str());
    mParcel.writeString(std::to_string(reason).c_str());

    LOGI << requestidToString(getRequestId()) + "> "
         << commandidToString(getCommandId()) << " " << cid << " " << reason << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setRadioPower(bool on)
{
    obtain(RIL_REQUEST_RADIO_POWER);

    mParcel.writeInt32(1);
    mParcel.writeInt32(on ? 1 : 0);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << (on ? " on" : " off") << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setSuppServiceNotifications(bool enable)
{
    obtain(RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION);

    mParcel.writeInt32(1);
    mParcel.writeInt32(enable ? 1 : 0);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::acknowledgeLastIncomingGsmSms(bool success, int cause)
{
    obtain(RIL_REQUEST_SMS_ACKNOWLEDGE);

    mParcel.writeInt32(2);
    mParcel.writeInt32(success ? 1 : 0);
    mParcel.writeInt32(cause);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " " << success << " " << cause << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::acknowledgeLastIncomingCdmaSms(bool success, int cause)
{
    obtain(RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE);

    mParcel.writeInt32(success ? 0 : 1); //RIL_CDMA_SMS_EthisorClass
    // cause code according to X.S004-550E
    mParcel.writeInt32(cause);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " " << success << " " << cause << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::acknowledgeIncomingGsmSmsWithPdu(bool success, std::string ackPdu)
{
    obtain(RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU);

    mParcel.writeInt32(2);
    mParcel.writeString(success ? "1" : "0");
    mParcel.writeString(ackPdu.c_str());

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ' ' << success << " [" + ackPdu + ']' << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::iccIO(int command, int fileid, std::string path, int p1, int p2, int p3,
                      std::string data, std::string pin2)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    obtain(RIL_REQUEST_SIM_IO);

    mParcel.writeInt32(command);
    mParcel.writeInt32(fileid);
    mParcel.writeString(path.c_str());
    mParcel.writeInt32(p1);
    mParcel.writeInt32(p2);
    mParcel.writeInt32(p3);
    mParcel.writeString(data.c_str());
    mParcel.writeString(pin2.c_str());

    LOGI << requestidToString(getRequestId()) + "> iccIO: " << commandidToString(getCommandId())
         << " 0x" << std::hex << command << " 0x" << fileid << " "
         << " path: " << path << "," << p1 << "," << p2 << "," << p3 << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getCLIR()
{
    obtain(RIL_REQUEST_GET_CLIR);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setCLIR(int clirMode)
{
    obtain(RIL_REQUEST_SET_CLIR);

    // count ints
    mParcel.writeInt32(1);

    mParcel.writeInt32(clirMode);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " " << clirMode << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::queryCallWaiting(int serviceClass)
{
    obtain(RIL_REQUEST_QUERY_CALL_WAITING);

    mParcel.writeInt32(1);
    mParcel.writeInt32(serviceClass);

    LOGI << requestidToString(getRequestId()) + "> "
         << commandidToString(getCommandId()) << " " << serviceClass << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setCallWaiting(bool enable, int serviceClass)
{
    obtain(RIL_REQUEST_SET_CALL_WAITING);

    mParcel.writeInt32(2);
    mParcel.writeInt32(enable ? 1 : 0);
    mParcel.writeInt32(serviceClass);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " " << enable << ", " << serviceClass << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setNetworkSelectionModeAutomatic()
{
    obtain(RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setNetworkSelectionModeManual(std::string operatorNumeric)
{
    obtain(RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " " + operatorNumeric << ENDL;

    mParcel.writeString(operatorNumeric.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getNetworkSelectionMode()
{
    obtain(RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getAvailableNetworks()
{
    obtain(RIL_REQUEST_QUERY_AVAILABLE_NETWORKS);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setCallForward(int action, int cfReason, int serviceClass,
                               std::string number, int timeSeconds)
{
    obtain(RIL_REQUEST_SET_CALL_FORWARD);

    mParcel.writeInt32(action);
    mParcel.writeInt32(cfReason);
    mParcel.writeInt32(serviceClass);
    mParcel.writeInt32(number.length());
    mParcel.writeString(number.c_str());
    mParcel.writeInt32(timeSeconds);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " "
         << action << " " << cfReason << " " << serviceClass << timeSeconds << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::queryCallForwardStatus(int cfReason, int serviceClass,
                                       std::string number)
{
    obtain(RIL_REQUEST_QUERY_CALL_FORWARD_STATUS);

    mParcel.writeInt32(2); // 2 is for query action, not in used anyway
    mParcel.writeInt32(cfReason);
    mParcel.writeInt32(serviceClass);
    mParcel.writeInt32(number.length());
    mParcel.writeString(number.c_str());
    mParcel.writeInt32(0);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " "
         << cfReason << " " << serviceClass << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::queryCLIP()
{
    obtain(RIL_REQUEST_QUERY_CLIP);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getBasebandVersion()
{
    obtain(RIL_REQUEST_BASEBAND_VERSION);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::queryFacilityLock(std::string facility, std::string password, int serviceClass)
{
    return queryFacilityLockForApp(facility, password, serviceClass, "");
}

int RILRequest::queryFacilityLockForApp(std::string facility, std::string password,
                                        int serviceClass, std::string appId)
{
    obtain(RIL_REQUEST_QUERY_FACILITY_LOCK);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    // count strings
    mParcel.writeInt32(4);

    mParcel.writeString(facility.c_str());
    mParcel.writeString(password.c_str());

    mParcel.writeString(std::to_string(serviceClass).c_str());
    mParcel.writeString(appId.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setFacilityLock(std::string facility, bool lockState, std::string password,
                                int serviceClass)
{
    return setFacilityLockForApp(facility, lockState, password, serviceClass, "");
}

int RILRequest::setFacilityLockForApp(std::string facility, bool lockState, std::string password,
                                      int serviceClass, std::string appId)
{
    std::string lockString;
    obtain(RIL_REQUEST_SET_FACILITY_LOCK);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    // count strings
    mParcel.writeInt32(5);

    mParcel.writeString(facility.c_str());
    lockString = (lockState) ? "1" : "0";
    mParcel.writeString(lockString.c_str());
    mParcel.writeString(password.c_str());
    mParcel.writeString(std::to_string(serviceClass).c_str());
    mParcel.writeString(appId.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::sendUSSD(std::string ussdString)
{
    obtain(RIL_REQUEST_SEND_USSD);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " " + ussdString << ENDL;

    mParcel.writeString(ussdString.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::cancelPendingUssd()
{
    obtain(RIL_REQUEST_CANCEL_USSD);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::resetRadio()
{
    obtain(RIL_REQUEST_RESET_RADIO);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

// int RILRequest::invokeOemRilRequestRaw(uint8_t *data)
// {
//     obtain(//               RIL_REQUEST_OEM_HOOK_RAW,
//               result);

//     LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << "[" + IccUtils.bytesToHexString(data) + "]" << ENDL;

//     mParcel.writeByteAthisay(data);
//     if (!nonblockSend(this)){
//     mResponse = result;
// }

int RILRequest::invokeOemRILRequestStrings(std::vector<std::string> strings)
{
    obtain(RIL_REQUEST_OEM_HOOK_STRINGS);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeInt32(strings.size());
    for (size_t i = 0; i < strings.size(); i++)
        mParcel.writeString(strings.at(i).c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

/**
 * Assign a specified band for RF configuration.
 *
 * @param bandMode one of BM_*_BAND
 * @param response is callback message
 */
int RILRequest::setBandMode(int bandMode)
{
    obtain(RIL_REQUEST_SET_BAND_MODE);

    mParcel.writeInt32(1);
    mParcel.writeInt32(bandMode);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " " << bandMode << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

/**
 * Query the list of band mode supported by 
 * std::unique_lock<std::mutex> _lk(mRequestLock);RF.
 *
 * @param response is callback message
 *        ((AsyncResult)response.obj).result  is an int[] with every
 *        element representing one avialable BM_*_BAND
 */
int RILRequest::queryAvailableBandMode()
{
    obtain(RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::sendTerminalResponse(std::string contents)
{
    obtain(RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeString(contents.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::sendEnvelope(std::string contents)
{
    obtain(RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    mParcel.writeString(contents.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::sendEnvelopeWithStatus(std::string contents)
{
    obtain(RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << '[' + contents + ']' << ENDL;

    mParcel.writeString(contents.c_str());

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

// int RILRequest::handleCallSetupRequestFromSim(
//     bool accept)
// {

//     obtain(//         RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM,
//         result);

//     LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

//     int[] param = new(std::nothrow) int[1];
//     param[0] = accept ? 1 : 0;
//     mParcel.writeIntthisay(param);
//     if (!nonblockSend(this)){
//     mResponse = result;
// }

int RILRequest::setPreferredNetworkType(int networkType)
{
    obtain(RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE);

    mParcel.writeInt32(1);
    mParcel.writeInt32(networkType);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getPreferredNetworkType()
{
    obtain(RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getNeighboringCids()
{
    obtain(RIL_REQUEST_GET_NEIGHBORING_CELL_IDS);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setLocationUpdates(bool enable)
{
    obtain(RIL_REQUEST_SET_LOCATION_UPDATES);
    mParcel.writeInt32(1);
    mParcel.writeInt32(enable ? 1 : 0);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ": " << enable << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getSmscAddress()
{
    obtain(RIL_REQUEST_GET_SMSC_ADDRESS);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::setSmscAddress(std::string address)
{
    obtain(RIL_REQUEST_SET_SMSC_ADDRESS);

    mParcel.writeString(address.c_str());

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << " : " + address << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::reportSmsMemoryStatus(bool available)
{
    obtain(RIL_REQUEST_REPORT_SMS_MEMORY_STATUS);
    mParcel.writeInt32(1);
    mParcel.writeInt32(available ? 1 : 0);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ": " << available << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::reportStkServiceIsRunning()
{
    obtain(RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

int RILRequest::getGsmBroadcastConfig()
{
    obtain(RIL_REQUEST_GSM_GET_BROADCAST_SMS_CONFIG);

    LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

    int ret = nonblockSend(this);
    if (!ret)
        LOGE << "send request failed" << ENDL;
    return ret ? 0 : -1;
}

// int RILRequest::setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config)
// {
//     obtain(//           RIL_REQUEST_GSM_SET_BROADCAST_CONFIG,
//           result);

//     int numOfConfig = config.length;
//     mParcel.writeInt32(numOfConfig);

//     for (int i = 0; i < numOfConfig; i++)
//     {
//         mParcel.writeInt32(config[i].getFromServiceId());
//         mParcel.writeInt32(config[i].getToServiceId());
//         mParcel.writeInt32(config[i].getFromCodeScheme());
//         mParcel.writeInt32(config[i].getToCodeScheme());
//         mParcel.writeInt32(config[i].isSelected() ? 1 : 0);
//     }

//     {
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) <<  " with " + numOfConfig + " configs : ");
//         for (int i = 0; i < numOfConfig; i++)
//         {
//             riljLog(config[i].toString());
//         }
//     }
//     if (!nonblockSend(this)){
//     mResponse = result;
// }

// int RILRequest::setGsmBroadcastActivation(bool activate)
// {
//     obtain(RIL_REQUEST_GSM_BROADCAST_ACTIVATION);

//     mParcel.writeInt32(1);
//     mParcel.writeInt32(activate ? 0 : 1);

//     LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;

//     if (!nonblockSend(this))
//     {
//         LOGE << "send request failed" << ENDL;
//         return;
//     }
// }

// //***** Private Methods
// private
// void sendScreenState(bool on)
// {
//     obtain(//         RIL_REQUEST_SCREEN_STATE, null);
//     mParcel.writeInt32(1);
//     mParcel.writeInt32(on ? 1 : 0);
//
//         LOGD << equestidString(getRequestId()) + "> " << commandidToString(getCommandId()) <<  ": " + on);
// if (!nonblockSend(this)){
// mResponse = result;
// }

// // ***** Methods for CDMA support
// public
// void getDeviceIdentity(RilResponse *response)
// {
//     obtain(IL_REQUEST_DEVICE_IDENTITY);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// public
// void getCDMASubscription(RilResponse *response)
// {
//     obtain(IL_REQUEST_CDMA_SUBSCRIPTION);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// void setPhoneType(int phoneType)
// { // Called by CDMAPhone and GSMPhone constructor
//
//         riljLog("setPhoneType=" + phoneType + " old value=" + mPhoneType);
//     mPhoneType = phoneType;
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void queryCdmaRoamingPreference(RilResponse *response)
// {
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaRoamingPreference(int cdmaRoamingType)
// {
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE);

//     this.mp.writeInt32(1);
//     this.mp.writeInt32(cdmaRoamingType);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL+ " : " + cdmaRoamingType);
//     if (!nonblockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaSubscriptionSource(int cdmaSubscription)
// {
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE);

//     this.mp.writeInt32(1);
//     this.mp.writeInt32(cdmaSubscription);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL+ " : " + cdmaSubscription);
//     if (!nonblockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// void getCdmaSubscriptionSource(RilResponse *response)
// {
//     obtain(//         RILConstants.RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void queryTTYMode(RilResponse *response)
// {
//     obtain(//         RILConstants.RIL_REQUEST_QUERY_TTY_MODE);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setTTYMode(int ttyMode)
// {
//     obtain(//         RILConstants.RIL_REQUEST_SET_TTY_MODE);

//     this.mp.writeInt32(1);
//     this.mp.writeInt32(ttyMode);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL+ " : " + ttyMode);
//     if (!nonblockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void sendCDMAFeatureCode(String FeatureCode)
// {
//     obtain(IL_REQUEST_CDMA_FLASH);

//     this.mp.writeString(FeatureCode);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL+ " : " + FeatureCode);
//     if (!nonblockSend(this)){
// }

// public
// void getCdmaBroadcastConfig(RilResponse *response)
// {
//     obtain(IL_REQUEST_CDMA_GET_BROADCAST_CONFIG);
//     if (!nonblockSend(this)){
// }

// // TODO: Change the configValuesAthisay to a RIL_BroadcastSMSConfig
// public
// void setCdmaBroadcastConfig(int[] configValuesAthisay)
// {
//     obtain(IL_REQUEST_CDMA_SET_BROADCAST_CONFIG);

//     for (int i = 0; i < configValuesAthisay.length; i++)
//     {
//         this.mp.writeInt32(configValuesAthisay[i]);
//     }

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// public
// void setCdmaBroadcastActivation(boolean activate)
// {
//     obtain(IL_REQUEST_CDMA_BROADCAST_ACTIVATION);

//     this.mp.writeInt32(1);
//     this.mp.writeInt32(activate ? 0 : 1);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void exitEmergencyCallbackMode(RilResponse *response)
// {
//     obtain(IL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }

// public
// void requestIsimAuthentication(String nonce)
// {
//     obtain(IL_REQUEST_ISIM_AUTHENTICATION);

//     this.mp.writeString(nonce);

//
//         LOGI << requestidToString(getRequestId()) + "> " << commandidToString(getCommandId()) << ENDL;
//     if (!nonblockSend(this)){
// }
// }

void RILRequest::processSolicited(RILRequest *rr, Parcel &p)
{
    int error = p.readInt32();

    if (error)
        LOGE << "RESP < " << commandidToString(rr->getCommandId()) << " with error " << error << ENDL;
    else
        LOGI << "RESP < " << commandidToString(rr->getCommandId()) << ENDL;

    rr->mResponse->command_id = rr->getCommandId();
    rr->mResponse->error_code = error;
    rr->mResponse->is_unsocilited = 0;
    clock_gettime(CLOCK_MONOTONIC, &rr->mResponse->finish_time);

    if (error == 0 || p.dataAvail() > 0)
    {
        // either command succeeds or command fails but with data payload
        auto processer = SocilitedProcesser.find(rr->getCommandId());
        if (processer != SocilitedProcesser.end())
        {
            processer->second(p, rr->mResponse);
        }
        else
        {
            LOGE << "undefined response processer for " << commandidToString(rr->getCommandId()) << ENDL;
        }
    }

    // notice caller immediatelly
    rr->mResponse->notify(rr->mResponse->userdata);
    delete rr;
}

void RILRequest::processUnsolicited(Parcel &p)
{
    int cmdid = p.readInt32();

    // mUnsocilitedResponse.error_code = FIELD_INVALID;
    // mUnsocilitedResponse.is_unsocilited = 1;

    LOGI << "RESP < " << responseToString(cmdid) << ENDL;
    // either command succeeds or command fails but with data payload
    auto processer = UnsocilitedProcesser.find(cmdid);
    if (processer != UnsocilitedProcesser.end())
    {
        processer->second(p, nullptr);
    }
    else
    {
        LOGE << "undefined response processer for " << commandidToString(cmdid) << ENDL;
    }
}
