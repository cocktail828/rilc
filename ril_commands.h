#ifndef __RIL_COMMANDS
#define __RIL_COMMANDS

#include <string>
#include "ril.h"
#include "ril_response.h"

class Parcel;
class RilRespose;
std::string responseStrings(Parcel &);
void getDeviceIdentity(RilResponse *response);
void getCDMASubscription(RilResponse *response);
void setPhoneType(int phoneType);
void queryCdmaRoamingPreference(RilResponse *response);
void setCdmaRoamingPreference(int cdmaRoamingType, RilResponse *response);
void setCdmaSubscriptionSource(int cdmaSubscription, RilResponse *response);
void getCdmaSubscriptionSource(RilResponse *response);
void queryTTYMode(RilResponse *rsponse);
void setTTYMode(int ttyMode, RilResponse *rsponse);
void sendCDMAFeatureCode(std::string FeatureCode, RilResponse *rsponse);
void getCdmaBroadcastConfig(RilResponse *rsponse);
// void setCdmaBroadcastConfig(int[] configValuesArray, RilResponse* esponse);
void setCdmaBroadcastActivation(bool activate, RilResponse *rsponse);
void exitEmergencyCallbackMode(RilResponse *rsponse);
void requestIsimAuthentication(std::string nonce, RilResponse *rsponse);

/* response function handlers */
void responseSignalStrength(Parcel &p);

// [RIL_REQUEST_GET_SIM_STATUS] = responseIccCardStatus),
// [RIL_REQUEST_ENTER_SIM_PIN] = responseInts,
// [RIL_REQUEST_ENTER_SIM_PUK] = responseInts,
// [RIL_REQUEST_ENTER_SIM_PIN2] = responseInts,
// [RIL_REQUEST_ENTER_SIM_PUK2] = responseInts,
// [RIL_REQUEST_CHANGE_SIM_PIN] = responseInts,
// [RIL_REQUEST_CHANGE_SIM_PIN2] = responseInts,
// [RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION] = responseInts,
// [RIL_REQUEST_GET_CURRENT_CALLS] = responseCallList,
// [RIL_REQUEST_DIAL] = responseVoid,
// [RIL_REQUEST_GET_IMSI] = responseStrings,
// [RIL_REQUEST_HANGUP] = responseVoid,
// [RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND] = responseVoid,
// [RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND] = responseVoid,
// [RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE] = responseVoid,
// [RIL_REQUEST_CONFERENCE] = responseVoid,
// [RIL_REQUEST_UDUB] = responseVoid,
// [RIL_REQUEST_LAST_CALL_FAIL_CAUSE] = responseInts,
// [RIL_REQUEST_SIGNAL_STRENGTH] = responseSignalStrength,
// [RIL_REQUEST_VOICE_REGISTRATION_STATE] = responseStrings,
// [RIL_REQUEST_DATA_REGISTRATION_STATE] = responseStrings,
// [RIL_REQUEST_OPERATOR] = responseStrings,
// [RIL_REQUEST_RADIO_POWER] = responseVoid,
// [RIL_REQUEST_DTMF] = responseVoid,
// [RIL_REQUEST_SEND_SMS] = responseSMS,
// [RIL_REQUEST_SEND_SMS_EXPECT_MORE] = responseSMS,
// [RIL_REQUEST_SETUP_DATA_CALL] = responseSetupDataCall,
// [RIL_REQUEST_SIM_IO] = responseICC_IO,
// [RIL_REQUEST_SEND_USSD] = responseVoid,
// [RIL_REQUEST_CANCEL_USSD] = responseVoid,
// [RIL_REQUEST_GET_CLIR] = responseInts,
// [RIL_REQUEST_SET_CLIR] = responseVoid,
// [RIL_REQUEST_QUERY_CALL_FORWARD_STATUS] = responseCallForward,
// [RIL_REQUEST_SET_CALL_FORWARD] = responseVoid,
// [RIL_REQUEST_QUERY_CALL_WAITING] = responseInts,
// [RIL_REQUEST_SET_CALL_WAITING] = responseVoid,
// [RIL_REQUEST_SMS_ACKNOWLEDGE] = responseVoid,
// [RIL_REQUEST_GET_IMEI] = responseString,
// [RIL_REQUEST_GET_IMEISV] = responseString,
// [RIL_REQUEST_ANSWER] = responseVoid,
// [RIL_REQUEST_DEACTIVATE_DATA_CALL] = responseVoid,
// [RIL_REQUEST_QUERY_FACILITY_LOCK] = responseInts,
// [RIL_REQUEST_SET_FACILITY_LOCK] = responseInts,
// [RIL_REQUEST_CHANGE_BARRING_PASSWORD] = responseVoid,
// [RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE] = responseInts,
// [RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC] = responseVoid,
// [RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL] = responseVoid,
// [RIL_REQUEST_QUERY_AVAILABLE_NETWORKS] = responseOperatorInfos,
// [RIL_REQUEST_DTMF_START] = responseVoid,
// [RIL_REQUEST_DTMF_STOP] = responseVoid,
// [RIL_REQUEST_BASEBAND_VERSION] = responseString,
// [RIL_REQUEST_SEPARATE_CONNECTION] = responseVoid,
// [RIL_REQUEST_SET_MUTE] = responseVoid,
// [RIL_REQUEST_GET_MUTE] = responseInts,
// [RIL_REQUEST_QUERY_CLIP] = responseInts,
// [RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE] = responseInts,
// [RIL_REQUEST_DATA_CALL_LIST] = responseDataCallList,
// [RIL_REQUEST_RESET_RADIO] = responseVoid,
// [RIL_REQUEST_OEM_HOOK_RAW] = responseRaw,
// [RIL_REQUEST_OEM_HOOK_STRINGS] = responseStrings,
// [RIL_REQUEST_SCREEN_STATE] = responseVoid,
// [RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION] = responseVoid,
// [RIL_REQUEST_WRITE_SMS_TO_SIM] = responseInts,
// [RIL_REQUEST_DELETE_SMS_ON_SIM] = responseVoid,
// [RIL_REQUEST_SET_BAND_MODE] = responseVoid,
// [RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE] = responseInts,
// [RIL_REQUEST_STK_GET_PROFILE] = responseString,
// [RIL_REQUEST_STK_SET_PROFILE] = responseVoid,
// [RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND] = responseString,
// [RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE] = responseVoid,
// [RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM] = responseInts,
// [RIL_REQUEST_EXPLICIT_CALL_TRANSFER] = responseVoid,
// [RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE] = responseVoid,
// [RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE] = responseGetPreferredNetworkType,
// [RIL_REQUEST_GET_NEIGHBORING_CELL_IDS] = responseCellList,
// [RIL_REQUEST_SET_LOCATION_UPDATES] = responseVoid,
// [RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE] = responseVoid,
// [RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE] = responseVoid,
// [RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE] = responseInts,
// [RIL_REQUEST_SET_TTY_MODE] = responseVoid,
// [RIL_REQUEST_QUERY_TTY_MODE] = responseInts,
// [RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE] = responseVoid,
// [RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE] = responseInts,
// [RIL_REQUEST_CDMA_FLASH] = responseVoid,
// [RIL_REQUEST_CDMA_BURST_DTMF] = responseVoid,
// [RIL_REQUEST_CDMA_SEND_SMS] = responseSMS,
// [RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE] = responseVoid,
// [RIL_REQUEST_GSM_GET_BROADCAST_CONFIG] = responseGmsBroadcastConfig,
// [RIL_REQUEST_GSM_SET_BROADCAST_CONFIG] = responseVoid,
// [RIL_REQUEST_GSM_BROADCAST_ACTIVATION] = responseVoid,
// [RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG] = responseCdmaBroadcastConfig,
// [RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG] = responseVoid,
// [RIL_REQUEST_CDMA_BROADCAST_ACTIVATION] = responseVoid,
// [RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY] = responseVoid,
// [RIL_REQUEST_CDMA_SUBSCRIPTION] = responseStrings,
// [RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM] = responseInts,
// [RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM] = responseVoid,
// [RIL_REQUEST_DEVICE_IDENTITY] = responseStrings,
// [RIL_REQUEST_GET_SMSC_ADDRESS] = responseString,
// [RIL_REQUEST_SET_SMSC_ADDRESS] = responseVoid,
// [RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE] = responseVoid,
// [RIL_REQUEST_REPORT_SMS_MEMORY_STATUS] = responseVoid,
// [RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING] = responseVoid,
// [RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE] = responseInts,
// [RIL_REQUEST_ISIM_AUTHENTICATION] = responseString,
// [RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU] = responseVoid,
// [RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS] = responseICC_IO)},

#endif //__RIL_COMMANDS
