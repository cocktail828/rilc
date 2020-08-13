#ifndef __RIL_COMMANDS
#define __RIL_COMMANDS

#include <string>
#include "ril.h"

class Parcel;
typedef (*response_func)(Parcel &);
typedef struct
{
    int commandid;
    void *request_func;
    response_func response_function;
} ril_command;

class Parcel;
class Message;
std::string responseStrings(Parcel &);
void getDeviceIdentity(Message response);
void getCDMASubscription(Message response);
void setPhoneType(int phoneType);
void queryCdmaRoamingPreference(Message response);
void setCdmaRoamingPreference(int cdmaRoamingType, Message response);
void setCdmaSubscriptionSource(int cdmaSubscription, Message response);
void getCdmaSubscriptionSource(Message response);
void queryTTYMode(Message response);
void setTTYMode(int ttyMode, Message response);
void sendCDMAFeatureCode(std::string FeatureCode, Message response);
void getCdmaBroadcastConfig(Message response);
// void setCdmaBroadcastConfig(int[] configValuesArray, Message response);
void setCdmaBroadcastActivation(bool activate, Message response);
void exitEmergencyCallbackMode(Message response);
void requestIsimAuthentication(std::string nonce, Message response);

#define CVFUNC(v) reinterpret_cast<void *>(v)
static ril_command ril_commands[] = {
    {RIL_REQUEST_GET_SIM_STATUS, CVFUNC(responseIccCardStatus)},
    {RIL_REQUEST_ENTER_SIM_PIN, CVFUNC(responseInts)},
    {RIL_REQUEST_ENTER_SIM_PUK, CVFUNC(responseInts)},
    {RIL_REQUEST_ENTER_SIM_PIN2, CVFUNC(responseInts)},
    {RIL_REQUEST_ENTER_SIM_PUK2, CVFUNC(responseInts)},
    {RIL_REQUEST_CHANGE_SIM_PIN, CVFUNC(responseInts)},
    {RIL_REQUEST_CHANGE_SIM_PIN2, CVFUNC(responseInts)},
    {RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION, CVFUNC(responseInts)},
    {RIL_REQUEST_GET_CURRENT_CALLS, CVFUNC(responseCallList)},
    {RIL_REQUEST_DIAL, CVFUNC(responseVoid)},
    {RIL_REQUEST_GET_IMSI, CVFUNC(responseStrings)},
    {RIL_REQUEST_HANGUP, CVFUNC(responseVoid)},
    {RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND, CVFUNC(responseVoid)},
    {RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND, CVFUNC(responseVoid)},
    {RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE, CVFUNC(responseVoid)},
    {RIL_REQUEST_CONFERENCE, CVFUNC(responseVoid)},
    {RIL_REQUEST_UDUB, CVFUNC(responseVoid)},
    {RIL_REQUEST_LAST_CALL_FAIL_CAUSE, CVFUNC(responseInts)},
    {RIL_REQUEST_SIGNAL_STRENGTH, CVFUNC(responseSignalStrength)},
    {RIL_REQUEST_VOICE_REGISTRATION_STATE, CVFUNC(responseStrings)},
    {RIL_REQUEST_DATA_REGISTRATION_STATE, CVFUNC(responseStrings)},
    {RIL_REQUEST_OPERATOR, CVFUNC(responseStrings)},
    {RIL_REQUEST_RADIO_POWER, CVFUNC(responseVoid)},
    {RIL_REQUEST_DTMF, CVFUNC(responseVoid)},
    {RIL_REQUEST_SEND_SMS, CVFUNC(responseSMS)},
    {RIL_REQUEST_SEND_SMS_EXPECT_MORE, CVFUNC(responseSMS)},
    {RIL_REQUEST_SETUP_DATA_CALL, CVFUNC(responseSetupDataCall)},
    {RIL_REQUEST_SIM_IO, CVFUNC(responseICC_IO)},
    {RIL_REQUEST_SEND_USSD, CVFUNC(responseVoid)},
    {RIL_REQUEST_CANCEL_USSD, CVFUNC(responseVoid)},
    {RIL_REQUEST_GET_CLIR, CVFUNC(responseInts)},
    {RIL_REQUEST_SET_CLIR, CVFUNC(responseVoid)},
    {RIL_REQUEST_QUERY_CALL_FORWARD_STATUS, CVFUNC(responseCallForward)},
    {RIL_REQUEST_SET_CALL_FORWARD, CVFUNC(responseVoid)},
    {RIL_REQUEST_QUERY_CALL_WAITING, CVFUNC(responseInts)},
    {RIL_REQUEST_SET_CALL_WAITING, CVFUNC(responseVoid)},
    {RIL_REQUEST_SMS_ACKNOWLEDGE, CVFUNC(responseVoid)},
    {RIL_REQUEST_GET_IMEI, CVFUNC(responseString)},
    {RIL_REQUEST_GET_IMEISV, CVFUNC(responseString)},
    {RIL_REQUEST_ANSWER, CVFUNC(responseVoid)},
    {RIL_REQUEST_DEACTIVATE_DATA_CALL, CVFUNC(responseVoid)},
    {RIL_REQUEST_QUERY_FACILITY_LOCK, CVFUNC(responseInts)},
    {RIL_REQUEST_SET_FACILITY_LOCK, CVFUNC(responseInts)},
    {RIL_REQUEST_CHANGE_BARRING_PASSWORD, CVFUNC(responseVoid)},
    {RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE, CVFUNC(responseInts)},
    {RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC, CVFUNC(responseVoid)},
    {RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL, CVFUNC(responseVoid)},
    {RIL_REQUEST_QUERY_AVAILABLE_NETWORKS, CVFUNC(responseOperatorInfos)},
    {RIL_REQUEST_DTMF_START, CVFUNC(responseVoid)},
    {RIL_REQUEST_DTMF_STOP, CVFUNC(responseVoid)},
    {RIL_REQUEST_BASEBAND_VERSION, CVFUNC(responseString)},
    {RIL_REQUEST_SEPARATE_CONNECTION, CVFUNC(responseVoid)},
    {RIL_REQUEST_SET_MUTE, CVFUNC(responseVoid)},
    {RIL_REQUEST_GET_MUTE, CVFUNC(responseInts)},
    {RIL_REQUEST_QUERY_CLIP, CVFUNC(responseInts)},
    {RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE, CVFUNC(responseInts)},
    {RIL_REQUEST_DATA_CALL_LIST, CVFUNC(responseDataCallList)},
    {RIL_REQUEST_RESET_RADIO, CVFUNC(responseVoid)},
    {RIL_REQUEST_OEM_HOOK_RAW, CVFUNC(responseRaw)},
    {RIL_REQUEST_OEM_HOOK_STRINGS, CVFUNC(responseStrings)},
    {RIL_REQUEST_SCREEN_STATE, CVFUNC(responseVoid)},
    {RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION, CVFUNC(responseVoid)},
    {RIL_REQUEST_WRITE_SMS_TO_SIM, CVFUNC(responseInts)},
    {RIL_REQUEST_DELETE_SMS_ON_SIM, CVFUNC(responseVoid)},
    {RIL_REQUEST_SET_BAND_MODE, CVFUNC(responseVoid)},
    {RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE, CVFUNC(responseInts)},
    {RIL_REQUEST_STK_GET_PROFILE, CVFUNC(responseString)},
    {RIL_REQUEST_STK_SET_PROFILE, CVFUNC(responseVoid)},
    {RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND, CVFUNC(responseString)},
    {RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE, CVFUNC(responseVoid)},
    {RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM, CVFUNC(responseInts)},
    {RIL_REQUEST_EXPLICIT_CALL_TRANSFER, CVFUNC(responseVoid)},
    {RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE, CVFUNC(responseVoid)},
    {RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE, CVFUNC(responseGetPreferredNetworkType)},
    {RIL_REQUEST_GET_NEIGHBORING_CELL_IDS, CVFUNC(responseCellList)},
    {RIL_REQUEST_SET_LOCATION_UPDATES, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE, CVFUNC(responseInts)},
    {RIL_REQUEST_SET_TTY_MODE, CVFUNC(responseVoid)},
    {RIL_REQUEST_QUERY_TTY_MODE, CVFUNC(responseInts)},
    {RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE, CVFUNC(responseInts)},
    {RIL_REQUEST_CDMA_FLASH, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_BURST_DTMF, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_SEND_SMS, CVFUNC(responseSMS)},
    {RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE, CVFUNC(responseVoid)},
    {RIL_REQUEST_GSM_GET_BROADCAST_CONFIG, CVFUNC(responseGmsBroadcastConfig)},
    {RIL_REQUEST_GSM_SET_BROADCAST_CONFIG, CVFUNC(responseVoid)},
    {RIL_REQUEST_GSM_BROADCAST_ACTIVATION, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG, CVFUNC(responseCdmaBroadcastConfig)},
    {RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_BROADCAST_ACTIVATION, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_SUBSCRIPTION, CVFUNC(responseStrings)},
    {RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM, CVFUNC(responseInts)},
    {RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM, CVFUNC(responseVoid)},
    {RIL_REQUEST_DEVICE_IDENTITY, CVFUNC(responseStrings)},
    {RIL_REQUEST_GET_SMSC_ADDRESS, CVFUNC(responseString)},
    {RIL_REQUEST_SET_SMSC_ADDRESS, CVFUNC(responseVoid)},
    {RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE, CVFUNC(responseVoid)},
    {RIL_REQUEST_REPORT_SMS_MEMORY_STATUS, CVFUNC(responseVoid)},
    {RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING, CVFUNC(responseVoid)},
    {RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE, CVFUNC(responseInts)},
    {RIL_REQUEST_ISIM_AUTHENTICATION, CVFUNC(responseString)},
    {RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU, CVFUNC(responseVoid)},
    {RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS, CVFUNC(responseICC_IO)},
    {0, 0, 0}};

#endif //__RIL_COMMANDS
