#include "ril/ril.h"
#include "ril_request.h"
#include "ril_response.h"
#include "logger.h"

#define PROCESSER(i, v) \
    RILCProcesser { i, v, v##Show, v##Free }

/* socilited response handlers */
static RILCProcesser SocilitedResponseProcesser[] = {
    PROCESSER(RIL_REQUEST_GET_SIM_STATUS, responseIccCardStatus),
    PROCESSER(RIL_REQUEST_ENTER_SIM_PIN, responseInts),
    PROCESSER(RIL_REQUEST_ENTER_SIM_PUK, responseInts),
    PROCESSER(RIL_REQUEST_ENTER_SIM_PIN2, responseInts),
    PROCESSER(RIL_REQUEST_ENTER_SIM_PUK2, responseInts),
    PROCESSER(RIL_REQUEST_CHANGE_SIM_PIN, responseInts),
    PROCESSER(RIL_REQUEST_CHANGE_SIM_PIN2, responseInts),
    PROCESSER(RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION, responseInts),
    PROCESSER(RIL_REQUEST_GET_CURRENT_CALLS, responseCallList),
    PROCESSER(RIL_REQUEST_DIAL, responseVoid),
    PROCESSER(RIL_REQUEST_GET_IMSI, responseString),
    PROCESSER(RIL_REQUEST_HANGUP, responseVoid),
    PROCESSER(RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND, responseVoid),
    PROCESSER(RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND, responseVoid),
    PROCESSER(RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE, responseVoid),
    PROCESSER(RIL_REQUEST_CONFERENCE, responseVoid),
    PROCESSER(RIL_REQUEST_UDUB, responseVoid),
    PROCESSER(RIL_REQUEST_LAST_CALL_FAIL_CAUSE, responseInts),
    PROCESSER(RIL_REQUEST_SIGNAL_STRENGTH, responseSignalStrength),
    PROCESSER(RIL_REQUEST_VOICE_REGISTRATION_STATE, responseStrings),
    PROCESSER(RIL_REQUEST_DATA_REGISTRATION_STATE, responseStrings),
    PROCESSER(RIL_REQUEST_OPERATOR, responseStrings),
    PROCESSER(RIL_REQUEST_RADIO_POWER, responseVoid),
    PROCESSER(RIL_REQUEST_DTMF, responseVoid),
    PROCESSER(RIL_REQUEST_SEND_SMS, responseSMS),
    PROCESSER(RIL_REQUEST_SEND_SMS_EXPECT_MORE, responseSMS),
    PROCESSER(RIL_REQUEST_SETUP_DATA_CALL, responseSetupDataCall),
    PROCESSER(RIL_REQUEST_SIM_IO, responseICC_IO),
    PROCESSER(RIL_REQUEST_SEND_USSD, responseVoid),
    PROCESSER(RIL_REQUEST_CANCEL_USSD, responseVoid),
    PROCESSER(RIL_REQUEST_GET_CLIR, responseInts),
    PROCESSER(RIL_REQUEST_SET_CLIR, responseVoid),
    PROCESSER(RIL_REQUEST_QUERY_CALL_FORWARD_STATUS, responseCallForward),
    PROCESSER(RIL_REQUEST_SET_CALL_FORWARD, responseVoid),
    PROCESSER(RIL_REQUEST_QUERY_CALL_WAITING, responseInts),
    PROCESSER(RIL_REQUEST_SET_CALL_WAITING, responseVoid),
    PROCESSER(RIL_REQUEST_SMS_ACKNOWLEDGE, responseVoid),
    PROCESSER(RIL_REQUEST_GET_IMEI, responseString),
    PROCESSER(RIL_REQUEST_GET_IMEISV, responseString),
    PROCESSER(RIL_REQUEST_ANSWER, responseVoid),
    PROCESSER(RIL_REQUEST_DEACTIVATE_DATA_CALL, responseVoid),
    PROCESSER(RIL_REQUEST_QUERY_FACILITY_LOCK, responseInts),
    PROCESSER(RIL_REQUEST_SET_FACILITY_LOCK, responseInts),
    PROCESSER(RIL_REQUEST_CHANGE_BARRING_PASSWORD, responseVoid),
    PROCESSER(RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE, responseInts),
    PROCESSER(RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC, responseVoid),
    PROCESSER(RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL, responseVoid),
    PROCESSER(RIL_REQUEST_QUERY_AVAILABLE_NETWORKS, responseOperatorInfos),
    PROCESSER(RIL_REQUEST_DTMF_START, responseVoid),
    PROCESSER(RIL_REQUEST_DTMF_STOP, responseVoid),
    PROCESSER(RIL_REQUEST_BASEBAND_VERSION, responseString),
    PROCESSER(RIL_REQUEST_SEPARATE_CONNECTION, responseVoid),
    PROCESSER(RIL_REQUEST_SET_MUTE, responseVoid),
    PROCESSER(RIL_REQUEST_GET_MUTE, responseInts),
    PROCESSER(RIL_REQUEST_QUERY_CLIP, responseInts),
    PROCESSER(RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE, responseInts),
    PROCESSER(RIL_REQUEST_DATA_CALL_LIST, responseDataCallList),
    PROCESSER(RIL_REQUEST_RESET_RADIO, responseVoid),
    PROCESSER(RIL_REQUEST_OEM_HOOK_RAW, responseRaw),
    PROCESSER(RIL_REQUEST_OEM_HOOK_STRINGS, responseStrings),
    PROCESSER(RIL_REQUEST_SCREEN_STATE, responseVoid),
    PROCESSER(RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION, responseVoid),
    PROCESSER(RIL_REQUEST_WRITE_SMS_TO_SIM, responseInts),
    PROCESSER(RIL_REQUEST_DELETE_SMS_ON_SIM, responseVoid),
    PROCESSER(RIL_REQUEST_SET_BAND_MODE, responseVoid),
    PROCESSER(RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE, responseInts),
    PROCESSER(RIL_REQUEST_STK_GET_PROFILE, responseString),
    PROCESSER(RIL_REQUEST_STK_SET_PROFILE, responseVoid),
    PROCESSER(RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND, responseString),
    PROCESSER(RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE, responseVoid),
    PROCESSER(RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM, responseInts),
    PROCESSER(RIL_REQUEST_EXPLICIT_CALL_TRANSFER, responseVoid),
    PROCESSER(RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE, responseVoid),
    PROCESSER(RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE, responseGetPreferredNetworkType),
    PROCESSER(RIL_REQUEST_GET_NEIGHBORING_CELL_IDS, responseCellList),
    PROCESSER(RIL_REQUEST_SET_LOCATION_UPDATES, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE, responseInts),
    PROCESSER(RIL_REQUEST_SET_TTY_MODE, responseVoid),
    PROCESSER(RIL_REQUEST_QUERY_TTY_MODE, responseInts),
    PROCESSER(RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE, responseInts),
    PROCESSER(RIL_REQUEST_CDMA_FLASH, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_BURST_DTMF, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_SEND_SMS, responseSMS),
    PROCESSER(RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE, responseVoid),
    PROCESSER(RIL_REQUEST_GSM_GET_BROADCAST_CONFIG, responseGmsBroadcastConfig),
    PROCESSER(RIL_REQUEST_GSM_SET_BROADCAST_CONFIG, responseVoid),
    PROCESSER(RIL_REQUEST_GSM_BROADCAST_ACTIVATION, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG, responseCdmaBroadcastConfig),
    PROCESSER(RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_BROADCAST_ACTIVATION, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_SUBSCRIPTION, responseStrings),
    PROCESSER(RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM, responseInts),
    PROCESSER(RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM, responseVoid),
    PROCESSER(RIL_REQUEST_DEVICE_IDENTITY, responseStrings),
    PROCESSER(RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE, responseVoid),
    PROCESSER(RIL_REQUEST_GET_SMSC_ADDRESS, responseString),
    PROCESSER(RIL_REQUEST_SET_SMSC_ADDRESS, responseVoid),
    PROCESSER(RIL_REQUEST_REPORT_SMS_MEMORY_STATUS, responseVoid),
    PROCESSER(RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING, responseVoid),
    PROCESSER(RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE, responseInts),
    PROCESSER(RIL_REQUEST_ISIM_AUTHENTICATION, responseString),
    PROCESSER(RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU, responseVoid),
    PROCESSER(RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS, responseICC_IO),

    /* request extension from unisoc */
    PROCESSER(RIL_REQUEST_VOICE_RADIO_TECH, responseInts),
    PROCESSER(RIL_REQUEST_GET_CELL_INFO_LIST, responseCellInfoList), // TODO
    PROCESSER(RIL_REQUEST_SET_UNSOL_CELL_INFO_LIST_RATE, responseVoid),
    PROCESSER(RIL_REQUEST_SET_INITIAL_ATTACH_APN, responseVoid),
    PROCESSER(RIL_REQUEST_IMS_REGISTRATION_STATE, responseInts),
    PROCESSER(RIL_REQUEST_IMS_SEND_SMS, responseSMS),
    PROCESSER(RIL_REQUEST_SIM_TRANSMIT_APDU_BASIC, responseSIM_IO),
    PROCESSER(RIL_REQUEST_SIM_OPEN_CHANNEL, responseInts),
    PROCESSER(RIL_REQUEST_SIM_CLOSE_CHANNEL, responseVoid),
    PROCESSER(RIL_REQUEST_SIM_TRANSMIT_APDU_CHANNEL, responseSIM_IO),
    PROCESSER(RIL_REQUEST_NV_READ_ITEM, responseString),
    PROCESSER(RIL_REQUEST_NV_WRITE_ITEM, responseVoid),
    PROCESSER(RIL_REQUEST_NV_WRITE_CDMA_PRL, responseVoid),
    PROCESSER(RIL_REQUEST_NV_RESET_CONFIG, responseVoid),
    PROCESSER(RIL_REQUEST_SET_UICC_SUBSCRIPTION, responseVoid),
    PROCESSER(RIL_REQUEST_ALLOW_DATA, responseVoid),
    PROCESSER(RIL_REQUEST_GET_HARDWARE_CONFIG, responseHardwareConfig),
    PROCESSER(RIL_REQUEST_SIM_AUTHENTICATION, responseSIM_IO),
    PROCESSER(RIL_REQUEST_GET_DC_RT_INFO, responseDcRtInfo),
    PROCESSER(RIL_REQUEST_SET_DC_RT_INFO_RATE, responseVoid),
    PROCESSER(RIL_REQUEST_SET_DATA_PROFILE, responseVoid),
    PROCESSER(RIL_REQUEST_SHUTDOWN, responseVoid),
    PROCESSER(RIL_REQUEST_GET_RADIO_CAPABILITY, responseRadioCapability),
    PROCESSER(RIL_REQUEST_SET_RADIO_CAPABILITY, responseRadioCapability),
    PROCESSER(RIL_REQUEST_START_LCE, responseLceStatus),
    PROCESSER(RIL_REQUEST_STOP_LCE, responseLceStatus),
    PROCESSER(RIL_REQUEST_PULL_LCEDATA, responseLceData),
    PROCESSER(RIL_REQUEST_GET_ACTIVITY_INFO, responseActivityData),
};

RILCProcesser *rilcFindSocilitedProcesser(int cmdid)
{
    int max_num = sizeof(SocilitedResponseProcesser) / sizeof(RILCProcesser);

    for (int i = 0; i < max_num; i++)
    {
        if (SocilitedResponseProcesser[i].commandid == cmdid)
            return &SocilitedResponseProcesser[i];
    }
    return nullptr;
}

/* unsocilited response handlers */
static RILCProcesser UnSocilitedResponseProcesser[] = {
    PROCESSER(RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED, responseVoid),
    PROCESSER(RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED, responseVoid),
    PROCESSER(RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED, responseVoid),
    PROCESSER(RIL_UNSOL_RESPONSE_NEW_SMS, responseString),
    PROCESSER(RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT, responseString),
    PROCESSER(RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM, responseInts),
    PROCESSER(RIL_UNSOL_ON_USSD, responseStrings),
    PROCESSER(RIL_UNSOL_ON_USSD_REQUEST, responseVoid),
    PROCESSER(RIL_UNSOL_NITZ_TIME_RECEIVED, responseString),
    PROCESSER(RIL_UNSOL_SIGNAL_STRENGTH, responseSignalStrength),
    PROCESSER(RIL_UNSOL_DATA_CALL_LIST_CHANGED, responseDataCallList),
    PROCESSER(RIL_UNSOL_SUPP_SVC_NOTIFICATION, responseSsn),
    PROCESSER(RIL_UNSOL_STK_SESSION_END, responseVoid),
    PROCESSER(RIL_UNSOL_STK_PROACTIVE_COMMAND, responseString),
    PROCESSER(RIL_UNSOL_STK_EVENT_NOTIFY, responseString),
    PROCESSER(RIL_UNSOL_STK_CALL_SETUP, responseInts),
    PROCESSER(RIL_UNSOL_SIM_SMS_STORAGE_FULL, responseVoid),
    PROCESSER(RIL_UNSOL_SIM_REFRESH, responseInts),
    PROCESSER(RIL_UNSOL_CALL_RING, responseCallRing),
    PROCESSER(RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED, responseVoid),
    PROCESSER(RIL_UNSOL_RESPONSE_CDMA_NEW_SMS, responseCdmaSms),
    PROCESSER(RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS, responseRaw),
    PROCESSER(RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL, responseVoid),
    PROCESSER(RIL_UNSOL_RESTRICTED_STATE_CHANGED, responseInts),
    PROCESSER(RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE, responseVoid),
    PROCESSER(RIL_UNSOL_CDMA_CALL_WAITING, responseCdmaCallWaiting), // TODO
    PROCESSER(RIL_UNSOL_CDMA_OTA_PROVISION_STATUS, responseInts),
    PROCESSER(RIL_UNSOL_CDMA_INFO_REC, responseCdmaInformationRecord), // TODO
    PROCESSER(RIL_UNSOL_OEM_HOOK_RAW, responseRaw),
    PROCESSER(RIL_UNSOL_RINGBACK_TONE, responseInts),
    PROCESSER(RIL_UNSOL_RESEND_INCALL_MUTE, responseVoid),
    PROCESSER(RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED, responseInts),
    PROCESSER(RIL_UNSOL_CDMA_PRL_CHANGED, responseInts),
    PROCESSER(RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE, responseVoid),
    PROCESSER(RIL_UNSOL_RIL_CONNECTED, responseInts),
    PROCESSER(RIL_UNSOL_VOICE_RADIO_TECH_CHANGED, responseInts),
    PROCESSER(RIL_UNSOL_CELL_INFO_LIST, responseCellInfoList), // TODO
    PROCESSER(RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED, responseVoid),
    PROCESSER(RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED, responseInts),
    PROCESSER(RIL_UNSOL_SRVCC_STATE_NOTIFY, responseInts),
    PROCESSER(RIL_UNSOL_HARDWARE_CONFIG_CHANGED, responseHardwareConfig),
    PROCESSER(RIL_UNSOL_DC_RT_INFO_CHANGED, responseDcRtInfo),
    PROCESSER(RIL_UNSOL_RADIO_CAPABILITY, responseRadioCapability),
    PROCESSER(RIL_UNSOL_ON_SS, responseSSData), // TODO
    PROCESSER(RIL_UNSOL_STK_CC_ALPHA_NOTIFY, responseString),
    PROCESSER(RIL_UNSOL_LCEDATA_RECV, responseLceData),
};

RILCProcesser *rilcFindUnSocilitedProcesser(int cmdid)
{
    int max_num = sizeof(UnSocilitedResponseProcesser) / sizeof(RILCProcesser);
    for (int i = 0; i < max_num; i++)
    {
        if (UnSocilitedResponseProcesser[i].commandid == cmdid)
            return &UnSocilitedResponseProcesser[i];
    }
    return nullptr;
}

#define NULLSTR(s) (s == nullptr ? "" : s)
#define SAFETYFREE(v)        \
    do                       \
    {                        \
        if (v)               \
            free((void *)v); \
        v = nullptr;         \
    } while (0)

#define ERROR_MALLOC0(v)                     \
    do                                       \
    {                                        \
        if (!v)                              \
        {                                    \
            LOGE << "out of memory" << ENDL; \
            return;                          \
        }                                    \
    } while (0);

static int ril_version = 0;

void set_ril_version(int ver)
{
    ril_version = ver;
}

int get_ril_version()
{
    return ril_version;
}

/***********************************************************************************/
/**************************** RILC CONCRETE RESPONSE *******************************/
/***********************************************************************************/
void responseStrings(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    int num = p.readInt32();
    const char **data = nullptr;

    if (num <= 0)
    {
        num = 0;
    }
    else
    {
        data = (const char **)malloc(num * sizeof(char **));
        ERROR_MALLOC0(data);
        for (int i = 0; i < num; i++)
            data[i] = p.readString();
    }

    resp->responseType = TYPE_STRING_ARR;
    resp->responseData.array.data = data;
    resp->responseData.array.num = num;
}

void responseStringsShow(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    LOGI << "UNMARSHAL: num of string " << num << ENDL;
    const char **data = (const char **)resp->responseData.array.data;
    for (int i = 0; i < num; i++)
        LOGI << NULLSTR(data[i]) << ENDL;
}

void responseStringsFree(RILResponse *resp)
{
    int num = resp->responseData.array.num;
    const char **data = (const char **)resp->responseData.array.data;
    for (int i = 0; i < num; i++)
        SAFETYFREE(data[i]);
    SAFETYFREE(data);
}

void responseString(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    resp->responseData.value_string = p.readString();
    resp->responseType = TYPE_STRING;
}

void responseStringShow(RILResponse *resp)
{
    if (!resp)
        return;
    LOGI << "UNMARSHAL: " << NULLSTR(resp->responseData.value_string) << ENDL;
}

void responseStringFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.value_string);
}

void responseInts(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    int num = p.readInt32();
    int *data = (int *)malloc(num * sizeof(int));
    ERROR_MALLOC0(data);
    for (int i = 0; i < num; i++)
        data[i] = p.readInt32();

    resp->responseType = TYPE_INT_ARR;
    resp->responseData.array.data = data;
    resp->responseData.array.num = num;
}

void responseIntsShow(RILResponse *resp)
{
    if (!resp)
        return;
    LOGI << "UNMARSHAL: num of int = " << resp->responseData.array.num;
    int *data = (int *)resp->responseData.array.data;
    for (int i = 0; i < resp->responseData.array.num; i++)
        LOGI << data[i] << ENDL;
}

void responseIntsFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseVoid(Parcel &p, RILResponse *resp)
{
    if (resp)
        return;

    resp->responseType = TYPE_VOID;
    LOGI << "UNMARSHAL: void response, error = " << resp->errorCode << ENDL;
}

void responseVoidShow(RILResponse *resp)
{
    if (resp)
        LOGI << "UNMARSHAL: void response, error = " << resp->errorCode << ENDL;
}

void responseVoidFree(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCallForward(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SuppSvcNotification *response = (RIL_SuppSvcNotification *)malloc(sizeof(RIL_SuppSvcNotification));
    ERROR_MALLOC0(response);

    response->notificationType = p.readInt32();
    response->code = p.readInt32();
    response->index = p.readInt32();
    response->type = p.readInt32();
    response->number = p.readString();

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseCallForwardShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SuppSvcNotification *response = (RIL_SuppSvcNotification *)resp->responseData.array.data;
    LOGI << "UNMARSHALL:" << ENDL;
    LOGI << "  notificationType = " << response->notificationType << ENDL;
    LOGI << "  code  = " << response->code << ENDL;
    LOGI << "  index = " << response->index << ENDL;
    LOGI << "  type  = " << response->type << ENDL;
    LOGI << "  number= " << NULLSTR(response->number) << ENDL;
}

void responseCallForwardFree(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SuppSvcNotification *response = (RIL_SuppSvcNotification *)resp->responseData.array.data;
    SAFETYFREE(response->number);
    SAFETYFREE(resp->responseData.array.data);
}

void responseCdmaSms(Parcel &p, RILResponse *resp)
{
    int digitCount;
    int digitLimit;
    if (!resp)
        return;

    RIL_CDMA_SMS_Message *response = (RIL_CDMA_SMS_Message *)malloc(sizeof(RIL_CDMA_SMS_Message));
    ERROR_MALLOC0(response);

    response->uTeleserviceID = p.readInt32();
    response->bIsServicePresent = p.readInt32();
    response->uServicecategory = p.readInt32();
    response->sAddress.digit_mode = static_cast<RIL_CDMA_SMS_DigitMode>(p.readInt32());
    response->sAddress.number_mode = static_cast<RIL_CDMA_SMS_NumberMode>(p.readInt32());
    response->sAddress.number_type = static_cast<RIL_CDMA_SMS_NumberType>(p.readInt32());
    response->sAddress.number_plan = static_cast<RIL_CDMA_SMS_NumberPlan>(p.readInt32());
    response->sAddress.number_of_digits = p.readInt32();
    digitLimit = response->sAddress.number_of_digits < RIL_CDMA_SMS_ADDRESS_MAX ? response->sAddress.number_of_digits : RIL_CDMA_SMS_ADDRESS_MAX;
    for (digitCount = 0; digitCount < digitLimit; digitCount++)
        response->sAddress.digits[digitCount] = p.readInt32();

    response->sSubAddress.subaddressType = static_cast<RIL_CDMA_SMS_SubaddressType>(p.readInt32());
    response->sSubAddress.odd = p.readInt32();
    response->sSubAddress.number_of_digits = p.readInt32();
    digitLimit = response->sSubAddress.number_of_digits < RIL_CDMA_SMS_SUBADDRESS_MAX ? response->sSubAddress.number_of_digits : RIL_CDMA_SMS_SUBADDRESS_MAX;
    for (digitCount = 0; digitCount < digitLimit; digitCount++)
        response->sSubAddress.digits[digitCount] = p.readInt32();

    // SmsMessage sms;
    digitLimit = response->uBearerDataLen < RIL_CDMA_SMS_BEARER_DATA_MAX ? response->uBearerDataLen : RIL_CDMA_SMS_BEARER_DATA_MAX;
    response->uBearerDataLen = p.readInt32();
    // sms = SmsMessage.newFromParcel(p);
    for (digitCount = 0; digitCount < digitLimit; digitCount++)
    {
        response->aBearerData[digitCount] = p.readInt32();
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseCdmaSmsShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_CDMA_SMS_Message *response = (RIL_CDMA_SMS_Message *)resp->responseData.array.data;

    LOGI << "  uTeleserviceID = " << response->uTeleserviceID << ENDL;
    LOGI << "  bIsServicePresent = " << response->bIsServicePresent << ENDL;
    LOGI << "  uServicecategory = " << response->uServicecategory << ENDL;
    LOGI << "  sAddress.digit_mode  = " << response->sAddress.digit_mode << ENDL;
    LOGI << "  sAddress.number_mode = " << response->sAddress.number_mode << ENDL;
    LOGI << "  sAddress.number_type = " << response->sAddress.number_type << ENDL;
    LOGI << "  sAddress.number_plan = " << response->sAddress.number_plan << ENDL;
    LOGI << "  sAddress.number_of_digits = " << response->sAddress.number_of_digits << ENDL;
    int digitLimit = response->sAddress.number_of_digits < RIL_CDMA_SMS_ADDRESS_MAX ? response->sAddress.number_of_digits : RIL_CDMA_SMS_ADDRESS_MAX;
    for (int digitCount = 0; digitCount < digitLimit; digitCount++)
        LOGI << "    digits[" << digitCount << "]" << response->sAddress.digits[digitCount] << ENDL;

    LOGI << "  sSubAddress.subaddressType = " << response->sSubAddress.subaddressType << ENDL;
    LOGI << "  sSubAddress.odd = " << response->sSubAddress.odd << ENDL;
    LOGI << "  sSubAddress.number_of_digits = " << response->sSubAddress.number_of_digits << ENDL;

    digitLimit = response->sSubAddress.number_of_digits < RIL_CDMA_SMS_SUBADDRESS_MAX ? response->sSubAddress.number_of_digits : RIL_CDMA_SMS_SUBADDRESS_MAX;
    for (int digitCount = 0; digitCount < digitLimit; digitCount++)
        LOGI << "    digits[" << digitCount << "]" << response->sSubAddress.digits[digitCount] << ENDL;
}

void responseCdmaSmsFree(RILResponse *resp)
{
    if (!resp)
        return;

    SAFETYFREE(resp->responseData.array.data);
}

void responseRaw(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    uint8_t *response = nullptr;
    int response_len = p.readInt32();
    if (response_len == -1)
    {
        response_len = 0;
    }
    else
    {
        response = (uint8_t *)malloc(response_len);
        ERROR_MALLOC0(response);
        memcpy(response, p.readInplace(response_len), response_len);
    }

    resp->responseType = TYPE_RAWDATA;
    resp->responseData.array.num = response_len;
    resp->responseData.array.data = response;
}

void responseRawShow(RILResponse *resp)
{
    if (!resp)
        return;

    LOGI << "UNMARSHALL: rawdara" << ENDL;
    uint8_t *data = (uint8_t *)resp->responseData.array.data;
    for (int i = 0; i < resp->responseData.array.num; i++)
        LOGI << "  [" << i << "] = " << data[i] << ENDL;
}

void responseRawFree(RILResponse *resp)
{
    if (!resp)
        return;

    SAFETYFREE(resp->responseData.array.data);
}

void responseSMS(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_SMS_Response *response = (RIL_SMS_Response *)malloc(sizeof(RIL_SMS_Response));
    ERROR_MALLOC0(response);

    response->messageRef = p.readInt32();
    response->ackPDU = p.readString();
    response->errorCode = p.readInt32();

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseSMSShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SMS_Response *response = (RIL_SMS_Response *)resp->responseData.array.data;
    LOGI << "UNMARSHALL:" << ENDL;
    LOGI << "  messageRef = " << response->messageRef << ENDL;
    LOGI << "  ackPDU = " << response->ackPDU << ENDL;
    LOGI << "  errorCode = " << response->errorCode << ENDL;
}

void responseSMSFree(RILResponse *resp)
{
    if (!resp)
        return;

    SAFETYFREE(resp->responseData.array.data);
}

void responseICC_IO(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SIM_IO_Response *response = (RIL_SIM_IO_Response *)malloc(sizeof(RIL_SIM_IO_Response));
    ERROR_MALLOC0(response);
    response->sw1 = p.readInt32();
    response->sw2 = p.readInt32();
    response->simResponse = p.readString();

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseICC_IOShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SIM_IO_Response *response = (RIL_SIM_IO_Response *)resp->responseData.array.data;
    LOGI << "  sw1 = " << response->sw1 << ENDL;
    LOGI << "  sw2 = " << response->sw2 << ENDL;
    LOGI << "  simResponse = " << NULLSTR(response->simResponse) << ENDL;
}

void responseICC_IOFree(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SIM_IO_Response *response = (RIL_SIM_IO_Response *)resp->responseData.array.data;
    SAFETYFREE(response->simResponse);
    SAFETYFREE(resp->responseData.array.data);
}

void responseIccCardStatus(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    RIL_CardStatus_v6 *response = (RIL_CardStatus_v6 *)malloc(sizeof(RIL_CardStatus_v6));
    ERROR_MALLOC0(response);

    response->card_state = static_cast<RIL_CardState>(p.readInt32());
    response->universal_pin_state = static_cast<RIL_PinState>(p.readInt32());
    response->gsm_umts_subscription_app_index = p.readInt32();
    response->cdma_subscription_app_index = p.readInt32();
    response->ims_subscription_app_index = p.readInt32();
    response->num_applications = p.readInt32();
    for (int i = 0; i < response->num_applications; i++)
    {
        response->applications[i].app_type = static_cast<RIL_AppType>(p.readInt32());
        response->applications[i].app_state = static_cast<RIL_AppState>(p.readInt32());
        response->applications[i].perso_substate = static_cast<RIL_PersoSubstate>(p.readInt32());
        response->applications[i].aid_ptr = p.readString();
        response->applications[i].app_label_ptr = p.readString();
        response->applications[i].pin1_replaced = p.readInt32();
        response->applications[i].pin1 = static_cast<RIL_PinState>(p.readInt32());
        response->applications[i].pin2 = static_cast<RIL_PinState>(p.readInt32());
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseIccCardStatusShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_CardStatus_v6 *response = (RIL_CardStatus_v6 *)resp->responseData.array.data;
    LOGI << "UNMARSHALL" << ENDL;
    LOGI << "  response->card_state = " << response->card_state << ENDL;
    LOGI << "  response->universal_pin_state = " << response->universal_pin_state << ENDL;
    LOGI << "  response->gsm_umts_subscription_app_index = " << response->gsm_umts_subscription_app_index << ENDL;
    LOGI << "  response->cdma_subscription_app_index     = " << response->cdma_subscription_app_index << ENDL;
    LOGI << "  response->ims_subscription_app_index      = " << response->ims_subscription_app_index << ENDL;
    LOGI << "  response->num_applications = " << response->num_applications << ENDL;
    for (int i = 0; i < response->num_applications; i++)
    {
        LOGI << "  [" << i << "] app_type = " << response->applications[i].app_type << ENDL;
        LOGI << "  [" << i << "] app_state = " << response->applications[i].app_state << ENDL;
        LOGI << "  [" << i << "] perso_substate = " << response->applications[i].perso_substate << ENDL;
        LOGI << "  [" << i << "] aid_ptr = " << NULLSTR(response->applications[i].aid_ptr) << ENDL;
        LOGI << "  [" << i << "] app_label_ptr = " << NULLSTR(response->applications[i].app_label_ptr) << ENDL;
        LOGI << "  [" << i << "] pin1_replaced = " << response->applications[i].pin1_replaced << ENDL;
        LOGI << "  [" << i << "] pin1 = " << response->applications[i].pin1 << ENDL;
        LOGI << "  [" << i << "] pin2 = " << response->applications[i].pin2 << ENDL;
    }
}

void responseIccCardStatusFree(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_CardStatus_v6 *response = (RIL_CardStatus_v6 *)resp->responseData.array.data;
    for (int i = 0; i < response->num_applications; i++)
    {
        SAFETYFREE(response->applications[i].aid_ptr);
        SAFETYFREE(response->applications[i].app_label_ptr);
    }
    SAFETYFREE(resp->responseData.array.data);
}

void responseCallList(Parcel &p, RILResponse *resp)
{
    int num = p.readInt32();
    if (!resp)
        return;
    RIL_Call *response = (RIL_Call *)malloc(sizeof(RIL_Call) * num);
    ERROR_MALLOC0(response);

    for (int i = 0; i < num; i++)
    {
        response[i].state = static_cast<RIL_CallState>(p.readInt32());
        response[i].index = p.readInt32();
        response[i].toa = p.readInt32();
        response[i].isMpty = p.readInt32();
        response[i].isMT = p.readInt32();
        response[i].als = p.readInt32();
        response[i].isVoice = p.readInt32();
        response[i].isVoicePrivacy = p.readInt32();
        response[i].number = p.readString();
        response[i].numberPresentation = p.readInt32();
        response[i].name = p.readString();
        response[i].namePresentation = p.readInt32();
        int ifhasUUInfo = p.readInt32();
        if (ifhasUUInfo)
        {
            response[i].uusInfo = (RIL_UUS_Info *)malloc(sizeof(RIL_UUS_Info));
            if (response[i].uusInfo)
            {
                response[i].uusInfo->uusType = static_cast<RIL_UUS_Type>(p.readInt32());
                response[i].uusInfo->uusDcs = static_cast<RIL_UUS_DCS>(p.readInt32());
                response[i].uusInfo->uusLength = p.readInt32();
                response[i].uusInfo->uusData = p.readString(); //to do this may not right
            }
        }
        else
        {
            response[i].uusInfo = nullptr;
        }
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = num;
    resp->responseData.array.data = response;
}

void responseCallListShow(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    RIL_Call *response = (RIL_Call *)resp->responseData.array.data;
    LOGI << "UNMARSHALL: num of struct = " << num << ENDL;
    for (int i = 0; i < num; i++)
    {
        LOGI << "  state = " << response[i].state << ENDL;
        LOGI << "  index = " << response[i].index << ENDL;
        LOGI << "  toa   = " << response[i].toa << ENDL;
        LOGI << "  isMpty= " << response[i].isMpty << ENDL;
        LOGI << "  isMT  = " << response[i].isMT << ENDL;
        LOGI << "  als   = " << response[i].als << ENDL;
        LOGI << "  isVoice = " << response[i].isVoice << ENDL;
        LOGI << "  isVoicePrivacy = " << response[i].isVoicePrivacy << ENDL;
        LOGI << "  number = " << NULLSTR(response[i].number) << ENDL;
        LOGI << "  numberPresentation = " << response[i].numberPresentation << ENDL;
        LOGI << "  name = " << NULLSTR(response[i].name) << ENDL;
        LOGI << "  namePresentation = " << response[i].namePresentation << ENDL;

        LOGI << "  namePresentation = " << response[i].namePresentation << ENDL;
        if (response[i].uusInfo)
        {
            LOGI << "  uusType = " << response[i].uusInfo->uusType << ENDL;
            LOGI << "  uusDcs = " << response[i].uusInfo->uusDcs << ENDL;
            LOGI << "  uusLength = " << response[i].uusInfo->uusLength << ENDL;
            LOGI << "  uusData = " << NULLSTR(response[i].uusInfo->uusData) << ENDL;
        }
    }
}

void responseCallListFree(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    RIL_Call *response = (RIL_Call *)resp->responseData.array.data;
    LOGI << "UNMARSHALL: num of struct = " << num << ENDL;
    for (int i = 0; i < num; i++)
    {
        SAFETYFREE(response[i].number);
        SAFETYFREE(response[i].name);
        if (response[i].uusInfo)
        {
            SAFETYFREE(response[i].uusInfo->uusData);
            SAFETYFREE(response[i].uusInfo);
        }
    }
    SAFETYFREE(resp->responseData.array.data);
}

void responseDataCallList(Parcel &p, RILResponse *resp)
{
    int dontCare = p.readInt32();
    int num = p.readInt32();
    if (!resp)
        return;

    RIL_Data_Call_Response_v9 *response = (RIL_Data_Call_Response_v9 *)malloc(sizeof(RIL_Data_Call_Response_v9) * num);
    ERROR_MALLOC0(response);
    (void)dontCare;
    for (int i = 0; i < num; i++)
    {
        response[i].status = p.readInt32();
        response[i].suggestedRetryTime = p.readInt32();
        response[i].cid = p.readInt32();
        response[i].active = p.readInt32();
        response[i].type = p.readString();
        response[i].ifname = p.readString();
        response[i].addresses = p.readString();
        response[i].dnses = p.readString();
        response[i].gateways = p.readString();
        response[i].pcscf = p.readString();
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = num;
    resp->responseData.array.data = response;
}

void responseDataCallListShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_Data_Call_Response_v9 *response = (RIL_Data_Call_Response_v9 *)resp->responseData.array.data;
    int num = resp->responseData.array.num;
    LOGI << "UNMARSHALL: num of struct " << num << ENDL;
    for (int i = 0; i < num; i++)
    {
        LOGI << "  status   = " << response[i].status << ENDL;
        LOGI << "  suggestedRetryTime = " << response[i].suggestedRetryTime << ENDL;
        LOGI << "  cid      = " << response[i].cid << ENDL;
        LOGI << "  active   = " << response[i].active << ENDL;
        LOGI << "  type     = " << NULLSTR(response[i].type) << ENDL;
        LOGI << "  ifname   = " << NULLSTR(response[i].ifname) << ENDL;
        LOGI << "  addresses= " << NULLSTR(response[i].addresses) << ENDL;
        LOGI << "  dnses    = " << NULLSTR(response[i].dnses) << ENDL;
        LOGI << "  gateways = " << NULLSTR(response[i].gateways) << ENDL;
        LOGI << "  pcscf    = " << NULLSTR(response[i].pcscf) << ENDL;
    }
}

void responseDataCallListFree(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_Data_Call_Response_v9 *response = (RIL_Data_Call_Response_v9 *)resp->responseData.array.data;
    int num = resp->responseData.array.num;
    for (int i = 0; i < num; i++)
    {
        SAFETYFREE(response[i].type);
        SAFETYFREE(response[i].ifname);
        SAFETYFREE(response[i].addresses);
        SAFETYFREE(response[i].dnses);
        SAFETYFREE(response[i].gateways);
        SAFETYFREE(response[i].pcscf);
    }
    SAFETYFREE(resp->responseData.array.data);
}

void responseSetupDataCall(Parcel &p, RILResponse *resp)
{
    responseDataCallList(p, resp);
}

void responseSetupDataCallShow(RILResponse *resp)
{
    responseDataCallListShow(resp);
}

void responseSetupDataCallFree(RILResponse *resp)
{
    responseDataCallListFree(resp);
}

void responseOperatorInfos(Parcel &p, RILResponse *resp)
{
    responseStrings(p, resp);
}

void responseOperatorInfosShow(RILResponse *resp)
{
    responseStringShow(resp);
}

void responseOperatorInfosFree(RILResponse *resp)
{
    responseStringFree(resp);
}

void responseCellList(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    int num = p.readInt32();
    RIL_NeighboringCell *response = (RIL_NeighboringCell *)malloc(num * sizeof(RIL_NeighboringCell));
    ERROR_MALLOC0(response);
    for (int i = 0; i < num; i++)
    {
        response[i].rssi = p.readInt32();
        response[i].cid = p.readString();
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = num;
    resp->responseData.array.data = response;
}

void responseCellListShow(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    RIL_NeighboringCell *response = (RIL_NeighboringCell *)resp->responseData.array.data;
    LOGI << "UNMARSHALL: num of struct " << num << ENDL;
    for (int i = 0; i < num; i++)
    {
        LOGI << "RIL_NeighboringCell[" << i << "] cid = " << NULLSTR(response[i].cid) << ENDL;
        LOGI << "RIL_NeighboringCell[" << i << "] rssi = " << response[i].rssi << ENDL;
    }
}

void responseCellListFree(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    RIL_NeighboringCell *response = (RIL_NeighboringCell *)resp->responseData.array.data;
    LOGI << "UNMARSHALL: num of struct " << num << ENDL;
    for (int i = 0; i < num; i++)
        SAFETYFREE(response[i].cid);
    SAFETYFREE(resp->responseData.array.data);
}

void responseGetPreferredNetworkType(Parcel &p, RILResponse *resp)
{
    responseInts(p, resp);
}

void responseGetPreferredNetworkTypeShow(RILResponse *resp)
{
    responseIntsShow(resp);
}

void responseGetPreferredNetworkTypeFree(RILResponse *resp)
{
    responseIntsFree(resp);
}

void responseGmsBroadcastConfig(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    int num = p.readInt32();
    RIL_GSM_BroadcastSmsConfigInfo *response = (RIL_GSM_BroadcastSmsConfigInfo *)malloc(num * sizeof(RIL_GSM_BroadcastSmsConfigInfo));
    ERROR_MALLOC0(response);

    for (int i = 0; i < num; i++)
    {
        response[i].fromServiceId = p.readInt32();
        response[i].toServiceId = p.readInt32();
        response[i].fromCodeScheme = p.readInt32();
        response[i].toCodeScheme = p.readInt32();
        response[i].selected = p.readInt32();
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = num;
    resp->responseData.array.data = response;
}

void responseGmsBroadcastConfigShow(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    RIL_GSM_BroadcastSmsConfigInfo *response = (RIL_GSM_BroadcastSmsConfigInfo *)resp->responseData.array.data;
    for (int i = 0; i < num; i++)
    {
        LOGI << "  [" << i << "].fromServiceId = " << response[i].fromServiceId << ENDL;
        LOGI << "  [" << i << "].toServiceId = " << response[i].toServiceId << ENDL;
        LOGI << "  [" << i << "].fromCodeScheme = " << response[i].fromCodeScheme << ENDL;
        LOGI << "  [" << i << "].toCodeScheme = " << response[i].toCodeScheme << ENDL;
        LOGI << "  [" << i << "].selected = " << response[i].selected << ENDL;
    }
}

void responseGmsBroadcastConfigFree(RILResponse *resp)
{
    if (!resp)
        return;

    SAFETYFREE(resp->responseData.array.data);
}

void responseCdmaBroadcastConfig(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    int num = p.readInt32();
    RIL_CDMA_BroadcastSmsConfigInfo *response = (RIL_CDMA_BroadcastSmsConfigInfo *)malloc(num * sizeof(RIL_CDMA_BroadcastSmsConfigInfo));
    ERROR_MALLOC0(response);

    for (int i = 0; i < num; i++)
    {
        response[i].service_category = p.readInt32();
        response[i].language = p.readInt32();
        response[i].selected = p.readInt32();
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = num;
    resp->responseData.array.data = response;
}

void responseCdmaBroadcastConfigShow(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    RIL_CDMA_BroadcastSmsConfigInfo *response = (RIL_CDMA_BroadcastSmsConfigInfo *)resp->responseData.array.data;

    for (int i = 0; i < num; i++)
    {
        LOGI << "  [" << i << "].service_category = " << response[i].service_category << ENDL;
        LOGI << "  [" << i << "].language = " << response[i].language << ENDL;
        LOGI << "  [" << i << "].selected = " << response[i].selected << ENDL;
    }
}

void responseCdmaBroadcastConfigFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseSignalStrength(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_SignalStrength_v10 *response = (RIL_SignalStrength_v10 *)malloc(sizeof(RIL_SignalStrength_v10));
    ERROR_MALLOC0(response);
    response->GW_SignalStrength.signalStrength = p.readInt32();
    response->GW_SignalStrength.bitErrorRate = p.readInt32();
    response->CDMA_SignalStrength.dbm = p.readInt32();
    response->CDMA_SignalStrength.ecio = p.readInt32();
    response->EVDO_SignalStrength.dbm = p.readInt32();
    response->EVDO_SignalStrength.ecio = p.readInt32();
    response->EVDO_SignalStrength.signalNoiseRatio = p.readInt32();
    response->LTE_SignalStrength.signalStrength = p.readInt32();
    response->LTE_SignalStrength.rsrp = p.readInt32();
    response->LTE_SignalStrength.rsrq = p.readInt32();
    response->LTE_SignalStrength.rssnr = p.readInt32();
    response->LTE_SignalStrength.cqi = p.readInt32();
    response->TD_SCDMA_SignalStrength.rscp = p.readInt32();
#ifdef ORCA_FEATURE_5G
    RIL_NR_SignalStrength NR_SignalStrength;
#endif

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseSignalStrengthShow(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_SignalStrength_v10 *response = (RIL_SignalStrength_v10 *)resp->responseData.array.data;
    LOGI << "UNMARSHALL:" << ENDL;
    LOGI << __LINE__ << (response == nullptr) << ENDL;
    LOGI << "  GW_SignalStrength.signalStrength = " << response->GW_SignalStrength.signalStrength << ENDL;
    LOGI << "  GW_SignalStrength.bitErrorRate   = " << response->GW_SignalStrength.bitErrorRate << ENDL;
    LOGI << "  CDMA_SignalStrength.dbm          = " << response->CDMA_SignalStrength.dbm << ENDL;
    LOGI << "  CDMA_SignalStrength.ecio         = " << response->CDMA_SignalStrength.ecio << ENDL;
    LOGI << "  EVDO_SignalStrength.dbm          = " << response->EVDO_SignalStrength.dbm << ENDL;
    LOGI << "  EVDO_SignalStrength.ecio         = " << response->EVDO_SignalStrength.ecio << ENDL;
    LOGI << "  EVDO_SignalStrength.signalNoiseRatio = " << response->EVDO_SignalStrength.signalNoiseRatio << ENDL;
    LOGI << "  LTE_SignalStrength.signalStrength = " << response->LTE_SignalStrength.signalStrength << ENDL;
    LOGI << "  LTE_SignalStrength.rsrp          = " << response->LTE_SignalStrength.rsrp << ENDL;
    LOGI << "  LTE_SignalStrength.rsrq          = " << response->LTE_SignalStrength.rsrq << ENDL;
    LOGI << "  LTE_SignalStrength.cqi           = " << response->LTE_SignalStrength.cqi << ENDL;
    LOGI << "  TD_SCDMA_SignalStrength.rscp     = " << response->TD_SCDMA_SignalStrength.rscp << ENDL;
}

void responseSignalStrengthFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseCdmaInformationRecord(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCdmaInformationRecordShow(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCdmaInformationRecordFree(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCdmaCallWaiting(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    // RIL_CDMA_CallWaiting_v6 *response = (RIL_CDMA_CallWaiting_v6 *)malloc(sizeof(RIL_CDMA_CallWaiting_v6));

    // response->number = p.readString();
    // response->numberPresentation = p.readInt32();
    // response->name = p.readString();
    // marshallSignalInfoRecord(p, response->signalInfoRecord);

    // if (s_callbacks.version <= LAST_IMPRECISE_RIL_VERSION)
    // {
    //     if (responselen >= sizeof(RIL_CDMA_CallWaiting_v6))
    //     {
    //         p.readInt32(response->number_type);
    //         p.readInt32(response->number_plan);
    //     }
    //     else
    //     {
    //         p.readInt32(0);
    //         p.readInt32(0);
    //     }
    // }
    // else
    // { // RIL version >= 13
    //     p.readInt32(response->number_type);
    //     p.readInt32(response->number_plan);
    // }
}

void responseCdmaCallWaitingShow(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCdmaCallWaitingFree(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCallRing(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_CDMA_SignalInfoRecord *response = (RIL_CDMA_SignalInfoRecord *)malloc(sizeof(RIL_CDMA_SignalInfoRecord));
    ERROR_MALLOC0(response);

    response->isPresent = p.readInt32();
    response->signalType = p.readInt32();
    response->alertPitch = p.readInt32();
    response->signal = p.readInt32();

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseCallRingShow(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_CDMA_SignalInfoRecord *response = (RIL_CDMA_SignalInfoRecord *)resp->responseData.array.data;

    LOGI << "  isPresent = " << response->isPresent << ENDL;
    LOGI << "  signalType = " << response->signalType << ENDL;
    LOGI << "  alertPitch = " << response->alertPitch << ENDL;
    LOGI << "  signal = " << response->signal << ENDL;
}

void responseCallRingFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseCellInfoList(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCellInfoListShow(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseCellInfoListFree(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseSIM_IO(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_SIM_IO_Response *response = (RIL_SIM_IO_Response *)malloc(sizeof(RIL_SIM_IO_Response));
    ERROR_MALLOC0(response);

    response->sw1 = p.readInt32();
    response->sw2 = p.readInt32();
    response->simResponse = p.readString();

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseSIM_IOShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_SIM_IO_Response *response = (RIL_SIM_IO_Response *)resp->responseData.array.data;
    LOGI << "UNMARSHALL" << ENDL;
    LOGI << "  sw1 = " << response->sw1 << ENDL;
    LOGI << "  sw2 = " << response->sw2 << ENDL;
    LOGI << "  simResponse = " << NULLSTR(response->simResponse) << ENDL;
}

void responseSIM_IOFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseHardwareConfig(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    int num = p.readInt32();
    RIL_HardwareConfig *response = (RIL_HardwareConfig *)malloc(num * sizeof(RIL_HardwareConfig));
    ERROR_MALLOC0(response);

    for (int i = 0; i < num; i++)
    {
        switch (response[i].type)
        {
        case RIL_HARDWARE_CONFIG_MODEM:
        {
            const char *str = p.readString();
            snprintf(response[i].uuid, 64, "%s", NULLSTR(str));
            p.freeString(str);
            response[i].state = static_cast<RIL_HardwareConfig_State>(p.readInt32());
            response[i].cfg.modem.rat = p.readInt32();
            response[i].cfg.modem.maxVoice = p.readInt32();
            response[i].cfg.modem.maxData = p.readInt32();
            response[i].cfg.modem.maxStandby = p.readInt32();
            break;
        }
        case RIL_HARDWARE_CONFIG_SIM:
        {
            const char *str = p.readString();
            snprintf(response[i].uuid, 64, "%s", NULLSTR(str));
            p.freeString(str);
            response[i].state = static_cast<RIL_HardwareConfig_State>(p.readInt32());
            str = p.readString();
            snprintf(response[i].cfg.sim.modemUuid, 64, "%s", NULLSTR(str));
            p.freeString(str);
            break;
        }
        default:
            break;
        }
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = num;
    resp->responseData.array.data = response;
}

void responseHardwareConfigShow(RILResponse *resp)
{
    if (!resp)
        return;

    int num = resp->responseData.array.num;
    RIL_HardwareConfig *response = (RIL_HardwareConfig *)resp->responseData.array.data;
    for (int i = 0; i < num; i++)
    {
        switch (response[i].type)
        {
        case RIL_HARDWARE_CONFIG_MODEM:
        {
            LOGI << "  [" << i << "].type = RIL_HARDWARE_CONFIG_MODEM" << ENDL;
            LOGI << "  [" << i << "].uuid = " << response[i].uuid << ENDL;
            LOGI << "  [" << i << "].state = " << response[i].state << ENDL;
            LOGI << "  [" << i << "].cfg.modem.rat = " << response[i].cfg.modem.rat << ENDL;
            LOGI << "  [" << i << "].cfg.modem.maxVoice = " << response[i].cfg.modem.maxVoice << ENDL;
            LOGI << "  [" << i << "].cfg.modem.maxData = " << response[i].cfg.modem.maxData << ENDL;
            LOGI << "  [" << i << "].cfg.modem.maxStandby = " << response[i].cfg.modem.maxStandby << ENDL;
            break;
        }
        case RIL_HARDWARE_CONFIG_SIM:
        {
            LOGI << "  [" << i << "].type = RIL_HARDWARE_CONFIG_SIM" << ENDL;
            LOGI << "  [" << i << "].uuid = " << response[i].uuid << ENDL;
            LOGI << "  [" << i << "].state = " << response[i].state << ENDL;
            LOGI << "  [" << i << "].cfg.sim.modemUuid = " << response[i].cfg.sim.modemUuid << ENDL;
            break;
        }
        default:
            break;
        }
    }
}

void responseHardwareConfigFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseDcRtInfo(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_DcRtInfo *response = (RIL_DcRtInfo *)malloc(sizeof(RIL_DcRtInfo));
    response->time = p.readInt64();
    response->powerState = static_cast<RIL_DcPowerStates>(p.readInt32());

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseDcRtInfoShow(RILResponse *resp)
{
    if (!resp)
        return;

    RIL_DcRtInfo *response = (RIL_DcRtInfo *)resp->responseData.array.data;
    LOGI << "  time = " << response->time << ENDL;
    LOGI << "  powerState = " << response->powerState << ENDL;
}

void responseDcRtInfoFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseRadioCapability(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    RIL_RadioCapability *response = (RIL_RadioCapability *)malloc(sizeof(RIL_RadioCapability));
    response->version = p.readInt32();
    response->session = p.readInt32();
    response->phase = p.readInt32();
    response->rat = p.readInt32();
    const char *str = p.readString();
    snprintf(response->logicalModemUuid, 64, "%s", NULLSTR(str));
    p.freeString(str);
    response->status = p.readInt32();
}

void responseRadioCapabilityShow(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_RadioCapability *response = (RIL_RadioCapability *)resp->responseData.array.data;
    LOGI << "  version = " << response->version << ENDL;
    LOGI << "  session = " << response->session << ENDL;
    LOGI << "  phase = " << response->phase << ENDL;
    LOGI << "  rat = " << response->rat << ENDL;
    LOGI << "  logicalModemUuid = " << response->logicalModemUuid << ENDL;
    LOGI << "  status = " << response->status << ENDL;
}

void responseRadioCapabilityFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseLceStatus(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_LceStatusInfo *response = (RIL_LceStatusInfo *)malloc(sizeof(RIL_LceStatusInfo));
    p.read((void *)response, 1); // response->lce_status takes one byte.
    response->actual_interval_ms = p.readInt32();

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseLceStatusShow(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_LceStatusInfo *response = (RIL_LceStatusInfo *)resp->responseData.array.data;
    LOGI << "  lce_status = " << response->lce_status << ENDL;
    LOGI << "  actual_interval_ms = " << response->actual_interval_ms << ENDL;
}

void responseLceStatusFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseLceData(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_LceDataInfo *response = (RIL_LceDataInfo *)malloc(sizeof(RIL_LceDataInfo));
    ERROR_MALLOC0(response);

    response->last_hop_capacity_kbps = p.readInt32();
    p.read((void *)&(response->confidence_level), 1);
    p.read((void *)&(response->lce_suspended), 1);

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseLceDataShow(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_LceDataInfo *response = (RIL_LceDataInfo *)resp->responseData.array.data;
    LOGI << "  last_hop_capacity_kbps = " << response->last_hop_capacity_kbps << ENDL;
    LOGI << "  confidence_level = " << response->confidence_level << ENDL;
    LOGI << "  lce_suspended = " << response->lce_suspended << ENDL;
}

void responseLceDataFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseActivityData(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    RIL_ActivityStatsInfo *response = (RIL_ActivityStatsInfo *)response;
    response->sleep_mode_time_ms = p.readInt32();
    response->idle_mode_time_ms = p.readInt32();
    for (int i = 0; i < RIL_NUM_TX_POWER_LEVELS; i++)
        response->tx_mode_time_ms[i] = p.readInt32();
    response->rx_mode_time_ms = p.readInt32();
}

void responseActivityDataShow(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_ActivityStatsInfo *response = (RIL_ActivityStatsInfo *)resp->responseData.array.data;
    LOGI << "  sleep_mode_time_ms = " << response->sleep_mode_time_ms << ENDL;
    LOGI << "  idle_mode_time_ms = " << response->idle_mode_time_ms << ENDL;
    for (int i = 0; i < RIL_NUM_TX_POWER_LEVELS; i++)
        LOGI << "  [" << i << "].idle_mode_time_ms = " << response->tx_mode_time_ms[i] << ENDL;
    LOGI << "  rx_mode_time_ms = " << response->rx_mode_time_ms << ENDL;

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseActivityDataFree(RILResponse *resp)
{
    if (!resp)
        return;
    SAFETYFREE(resp->responseData.array.data);
}

void responseSSData(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
}

void responseSSDataShow(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseSSDataFree(RILResponse *resp)
{
    if (!resp)
        return;
}

void responseSsn(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;
    RIL_SuppSvcNotification *response = (RIL_SuppSvcNotification *)malloc(sizeof(RIL_SuppSvcNotification));
    response->notificationType = p.readInt32();
    response->code = p.readInt32();
    response->index = p.readInt32();
    response->type = p.readInt32();
    response->number = p.readString();

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseSsnShow(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_SuppSvcNotification *response = (RIL_SuppSvcNotification *)resp->responseData.array.data;
    LOGI << "  notificationType = " << response->notificationType << ENDL;
    LOGI << "  code = " << response->code << ENDL;
    LOGI << "  index = " << response->index << ENDL;
    LOGI << "  type = " << response->type << ENDL;
    LOGI << "  number = " << NULLSTR(response->number) << ENDL;
}

void responseSsnFree(RILResponse *resp)
{
    if (!resp)
        return;
    RIL_SuppSvcNotification *response = (RIL_SuppSvcNotification *)resp->responseData.array.data;
    SAFETYFREE(response->number);
    SAFETYFREE(resp->responseData.array.data);
}

std::string responseToString(int respid)
{
    switch (respid)
    {
    case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
        return "UNSOL_RESPONSE_RADIO_STATE_CHANGED";
    case RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED:
        return "UNSOL_RESPONSE_CALL_STATE_CHANGED";
    case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
        return "UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED";
    case RIL_UNSOL_RESPONSE_NEW_SMS:
        return "UNSOL_RESPONSE_NEW_SMS";
    case RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT:
        return "UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT";
    case RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM:
        return "UNSOL_RESPONSE_NEW_SMS_ON_SIM";
    case RIL_UNSOL_ON_USSD:
        return "UNSOL_ON_USSD";
    case RIL_UNSOL_ON_USSD_REQUEST:
        return "UNSOL_ON_USSD_REQUEST(obsolete)";
    case RIL_UNSOL_NITZ_TIME_RECEIVED:
        return "UNSOL_NITZ_TIME_RECEIVED";
    case RIL_UNSOL_SIGNAL_STRENGTH:
        return "UNSOL_SIGNAL_STRENGTH";
    case RIL_UNSOL_SUPP_SVC_NOTIFICATION:
        return "UNSOL_SUPP_SVC_NOTIFICATION";
    case RIL_UNSOL_STK_SESSION_END:
        return "UNSOL_STK_SESSION_END";
    case RIL_UNSOL_STK_PROACTIVE_COMMAND:
        return "UNSOL_STK_PROACTIVE_COMMAND";
    case RIL_UNSOL_STK_EVENT_NOTIFY:
        return "UNSOL_STK_EVENT_NOTIFY";
    case RIL_UNSOL_STK_CALL_SETUP:
        return "UNSOL_STK_CALL_SETUP";
    case RIL_UNSOL_SIM_SMS_STORAGE_FULL:
        return "UNSOL_SIM_SMS_STORAGE_FUL";
    case RIL_UNSOL_SIM_REFRESH:
        return "UNSOL_SIM_REFRESH";
    case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
        return "UNSOL_DATA_CALL_LIST_CHANGED";
    case RIL_UNSOL_CALL_RING:
        return "UNSOL_CALL_RING";
    case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
        return "UNSOL_RESPONSE_SIM_STATUS_CHANGED";
    case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
        return "UNSOL_NEW_CDMA_SMS";
    case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
        return "UNSOL_NEW_BROADCAST_SMS";
    case RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL:
        return "UNSOL_CDMA_RUIM_SMS_STORAGE_FULL";
    case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
        return "UNSOL_RESTRICTED_STATE_CHANGED";
    case RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE:
        return "UNSOL_ENTER_EMERGENCY_CALLBACK_MODE";
    case RIL_UNSOL_CDMA_CALL_WAITING:
        return "UNSOL_CDMA_CALL_WAITING";
    case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
        return "UNSOL_CDMA_OTA_PROVISION_STATUS";
    case RIL_UNSOL_CDMA_INFO_REC:
        return "UNSOL_CDMA_INFO_REC";
    case RIL_UNSOL_OEM_HOOK_RAW:
        return "UNSOL_OEM_HOOK_RAW";
    case RIL_UNSOL_RINGBACK_TONE:
        return "UNSOL_RINGBACK_TONE";
    case RIL_UNSOL_RESEND_INCALL_MUTE:
        return "UNSOL_RESEND_INCALL_MUTE";
    case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
        return "UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED";
    case RIL_UNSOL_CDMA_PRL_CHANGED:
        return "UNSOL_CDMA_PRL_CHANGED";
    case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
        return "UNSOL_EXIT_EMERGENCY_CALLBACK_MODE";
    case RIL_UNSOL_RIL_CONNECTED:
        return "UNSOL_RIL_CONNECTED";
    case RIL_UNSOL_VOICE_RADIO_TECH_CHANGED:
        return "UNSOL_VOICE_RADIO_TECH_CHANGED";
    case RIL_UNSOL_CELL_INFO_LIST:
        return "UNSOL_CELL_INFO_LIST";
    case RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED:
        return "RESPONSE_IMS_NETWORK_STATE_CHANGED";
    case RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED:
        return "UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED";
    case RIL_UNSOL_SRVCC_STATE_NOTIFY:
        return "UNSOL_SRVCC_STATE_NOTIFY";
    case RIL_UNSOL_HARDWARE_CONFIG_CHANGED:
        return "HARDWARE_CONFIG_CHANGED";
    case RIL_UNSOL_DC_RT_INFO_CHANGED:
        return "UNSOL_DC_RT_INFO_CHANGED";
    case RIL_UNSOL_RADIO_CAPABILITY:
        return "UNSOL_RADIO_CAPABILITY";
    case RIL_RESPONSE_ACKNOWLEDGEMENT:
        return "RIL_RESPONSE_ACKNOWLEDGEMENT";
    /* IMS unsolicited response */
    case RIL_UNSOL_RESPONSE_IMS_CALL_STATE_CHANGED:
        return "UNSOL_IMS_CALL_STATE_CHANGED";
    case RIL_UNSOL_RESPONSE_VIDEO_QUALITY:
        return "UNSOL_VIDEO_QUALITY";
    case RIL_UNSOL_RESPONSE_IMS_BEARER_ESTABLISTED:
        return "UNSOL_RESPONSE_IMS_BEARER_ESTABLISTED";
    case RIL_UNSOL_IMS_HANDOVER_REQUEST:
        return "UNSOL_IMS_HANDOVER_REQUEST";
    case RIL_UNSOL_IMS_HANDOVER_STATUS_CHANGE:
        return "UNSOL_IMS_HANDOVER_STATUS_CHANGE";
    case RIL_UNSOL_IMS_NETWORK_INFO_CHANGE:
        return "UNSOL_IMS_NETWORK_INFO_CHANGE";
    case RIL_UNSOL_IMS_REGISTER_ADDRESS_CHANGE:
        return "UNSOL_IMS_REGISTER_ADDRESS_CHANGE";
    case RIL_UNSOL_IMS_WIFI_PARAM:
        return "UNSOL_IMS_WIFI_PARAM";
    case RIL_UNSOL_IMS_NETWORK_STATE_CHANGED:
        return "UNSOL_IMS_NETWORK_STATE_CHANGED";
    /* videophone */
    case RIL_EXT_UNSOL_VIDEOPHONE_CODEC:
        return "UNSOL_VIDEOPHONE_CODEC";
    case RIL_EXT_UNSOL_VIDEOPHONE_DSCI:
        return "UNSOL_VIDEOPHONE_DSCI";
    case RIL_EXT_UNSOL_VIDEOPHONE_STRING:
        return "UNSOL_VIDEOPHONE_STRING";
    case RIL_EXT_UNSOL_VIDEOPHONE_REMOTE_MEDIA:
        return "UNSOL_VIDEOPHONE_REMOTE_MEDIA";
    case RIL_EXT_UNSOL_VIDEOPHONE_MM_RING:
        return "UNSOL_VIDEOPHONE_MM_RING";
    case RIL_EXT_UNSOL_VIDEOPHONE_RELEASING:
        return "UNSOL_VIDEOPHONE_RELEASING";
    case RIL_EXT_UNSOL_VIDEOPHONE_RECORD_VIDEO:
        return "UNSOL_VIDEOPHONE_RECORD_VIDEO";
    case RIL_EXT_UNSOL_VIDEOPHONE_MEDIA_START:
        return "UNSOL_VIDEOPHONE_MEDIA_START";

    case RIL_EXT_UNSOL_ECC_NETWORKLIST_CHANGED:
        return "UNSOL_ECC_NETWORKLIST_CHANGED";
    case RIL_EXT_UNSOL_RAU_SUCCESS:
        return "UNSOL_RAU_SUCCESS";
    case RIL_EXT_UNSOL_CLEAR_CODE_FALLBACK:
        return "UNSOL_CLEAR_CODE_FALLBACK";
    case RIL_EXT_UNSOL_RIL_CONNECTED:
        return "UNSOL_RIL_CONNECTED";
    case RIL_EXT_UNSOL_SIMLOCK_STATUS_CHANGED:
        return "UNSOL_SIMLOCK_STATUS_CHANGED";
    case RIL_EXT_UNSOL_SIMLOCK_SIM_EXPIRED:
        return "UNSOL_SIMLOCK_SIM_EXPIRED";
    case RIL_EXT_UNSOL_BAND_INFO:
        return "UNSOL_BAND_INFO";
    case RIL_EXT_UNSOL_SWITCH_PRIMARY_CARD:
        return "UNSOL_SWITCH_PRIMARY_CARD";
    case RIL_EXT_UNSOL_SIM_PS_REJECT:
        return "UNSOL_SIM_PS_REJECT";
    case RIL_EXT_UNSOL_SETUP_DATA_FOR_CP:
        return "UNSOL_SETUP_DATA_FOR_CP";
    case RIL_EXT_UNSOL_SIMMGR_SIM_STATUS_CHANGED:
        return "UNSOL_SIMMGR_SIM_STATUS_CHANGED";
    case RIL_EXT_UNSOL_RADIO_CAPABILITY_CHANGED:
        return "UNSOL_RADIO_CAPABILITY_CHANGED";
    case RIL_EXT_UNSOL_EARLY_MEDIA:
        return "UNSOL_EARLY_MEDIA";
    case RIL_EXT_UNSOL_DATA_PDP_INFO:
        return "UNSOL_DATA_PDP_INFO";
    case RIL_EXT_UNSOL_PPP_RSP:
        return "UNSOL_PPP_RSP";
    case RIL_EXT_UNSOL_PPP_DATA_PDP_INFO:
        return "UNSOL_PPP_DATA_PDP_INFO";
#ifdef ORCA_FEATURE_5G
    case RIL_EXT_UNSOL_PHYSICAL_CHANNEL_CONFIG:
        return "EXT_UNSOL_PHYSICAL_CHANNEL_CONFIG";
    case RIL_EXT_UNSOL_NETWORK_SCAN_RESULT:
        return "RIL_EXT_UNSOL_NETWORK_SCAN_RESULT";
    case RIL_EXT_UNSOL_SIGNAL_STRENGTH:
        return "RIL_EXT_UNSOL_SIGNAL_STRENGTH";
    case RIL_EXT_UNSOL_SIGNAL_CONN_STATUS:
        return "UNSOL_SIGNAL_CONN_STATUS";
#endif
    default:
        return "<unknown request>";
    }
}
