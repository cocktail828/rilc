#include "ril/ril.h"
#include "ril_request.h"
#include "ril_response.h"
#include "logger.h"

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

void responseStrings(Parcel &p, RILResponse *resp)
{
    if (!resp)
        return;

    int num = p.readInt32();
    const char **data = (const char **)malloc(num * sizeof(char **));
    ERROR_MALLOC0(data);
    for (int i = 0; i < num; i++)
        data[i] = p.readString();

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
        LOGI << NULLSTR(data[i]) << " " << ENDL;
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
}

// private
// void sendScreenState(boolean on)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SCREEN_STATE, null);
//     rr.mp.writeInt(1);
//     rr.mp.writeInt(on ? 1 : 0);

//
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ ": " + on);

//     RILREQUEST::send(rr);
// }

// protected
// void onRadioAvailable()
// {
//     // In case screen state was lost (due to process crash),
//     // this ensures that the RIL knows the correct screen state.

//     // TODO: Should query Power Manager and send the actual
//     // screen state.  Just send true for now.
//     sendScreenState(true);
// }

// private
// RadioState getRadioStateFromInt(int stateInt)
// {
//     RadioState state;

//     /* RIL_RadioState ril.h */
//     switch (stateInt)
//     {
//     case 0:
//         state = RadioState.RADIO_OFF;
//         break;
//     case 1:
//         state = RadioState.RADIO_UNAVAILABLE;
//         break;
//     case 2:
//         state = RadioState.SIM_NOT_READY;
//         break;
//     case 3:
//         state = RadioState.SIM_LOCKED_OR_ABSENT;
//         break;
//     case 4:
//         state = RadioState.SIM_READY;
//         break;
//     case 5:
//         state = RadioState.RUIM_NOT_READY;
//         break;
//     case 6:
//         state = RadioState.RUIM_READY;
//         break;
//     case 7:
//         state = RadioState.RUIM_LOCKED_OR_ABSENT;
//         break;
//     case 8:
//         state = RadioState.NV_NOT_READY;
//         break;
//     case 9:
//         state = RadioState.NV_READY;
//         break;

//     default:
//         throw new RuntimeException(
//             "Unrecognized RIL_RadioState: " + stateInt);
//     }
//     return state;
// }

// private
// void switchToRadioState(RadioState newState)
// {
//     setRadioState(newState);
// }

// private
// String
// retToString(int req, Object ret)
// {
//     if (ret == null)
//         return "";
//     switch (req)
//     {
//     // Don't log these return values, for privacy's sake.
//     case RIL_REQUEST_GET_IMSI:
//     case RIL_REQUEST_GET_IMEI:
//     case RIL_REQUEST_GET_IMEISV:
//         if (!RILJ_LOGV)
//         {
//             // If not versbose logging just return and don't display IMSI and IMEI, IMEISV
//             return "";
//         }
//     }

//     StringBuilder sb;
//     String s;
//     int length;
//     if (ret instanceof int[])
//     {
//         int[] intArray = (int[])ret;
//         length = intArray.length;
//         sb = new StringBuilder("{");
//         if (length > 0)
//         {
//             int i = 0;
//             sb.append(intArray[i++]);
//             while (i < length)
//             {
//                 sb.append(", ").append(intArray[i++]);
//             }
//         }
//         sb.append("}");
//         s = sb.toString();
//     }
//     else if (ret instanceof String[])
//     {
//         String[] strings = (String[])ret;
//         length = strings.length;
//         sb = new StringBuilder("{");
//         if (length > 0)
//         {
//             int i = 0;
//             sb.append(strings[i++]);
//             while (i < length)
//             {
//                 sb.append(", ").append(strings[i++]);
//             }
//         }
//         sb.append("}");
//         s = sb.toString();
//     }
//     else if (req == RIL_REQUEST_GET_CURRENT_CALLS)
//     {
//         ArrayList<DriverCall> calls = (ArrayList<DriverCall>)ret;
//         sb = new StringBuilder(" ");
//         for (DriverCall dc : calls)
//         {
//             sb.append("[").append(dc).append("] ");
//         }
//         s = sb.toString();
//     }
//     else if (req == RIL_REQUEST_GET_NEIGHBORING_CELL_IDS)
//     {
//         ArrayList<NeighboringCellInfo> cells;
//         cells = (ArrayList<NeighboringCellInfo>)ret;
//         sb = new StringBuilder(" ");
//         for (NeighboringCellInfo cell : cells)
//         {
//             sb.append(cell).append(" ");
//         }
//         s = sb.toString();
//     }
//     else
//     {
//         s = ret.toString();
//     }
//     return s;
// }

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

void responseSuppServiceNotification(Parcel &p, RILResponse *resp)
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
    {
        response->sAddress.digits[digitCount] = p.readInt32();
    }

    response->sSubAddress.subaddressType = static_cast<RIL_CDMA_SMS_SubaddressType>(p.readInt32());
    response->sSubAddress.odd = p.readInt32();
    response->sSubAddress.number_of_digits = p.readInt32();
    digitLimit = response->sSubAddress.number_of_digits < RIL_CDMA_SMS_SUBADDRESS_MAX ? response->sSubAddress.number_of_digits : RIL_CDMA_SMS_SUBADDRESS_MAX;
    for (digitCount = 0; digitCount < digitLimit; digitCount++)
    {
        response->sSubAddress.digits[digitCount] = p.readInt32();
    }
    //     SmsMessage sms;
    digitLimit = response->uBearerDataLen < RIL_CDMA_SMS_BEARER_DATA_MAX ? response->uBearerDataLen : RIL_CDMA_SMS_BEARER_DATA_MAX;
    response->uBearerDataLen = p.readInt32();
    //     sms = SmsMessage.newFromParcel(p);
    for (digitCount = 0; digitCount < digitLimit; digitCount++)
    {
        response->aBearerData[digitCount] = p.readInt32();
    }

    resp->responseType = TYPE_STRUCT;
    resp->responseData.array.num = 1;
    resp->responseData.array.data = response;
}

void responseSuppServiceNotificationShow(RILResponse *resp)
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

void responseSuppServiceNotificationFree(RILResponse *resp)
{
    if (!resp)
        return;

    SAFETYFREE(resp->responseData.array.data);
}

void responseRaw(Parcel &p, RILResponse *resp)
{
    // int response_len = p.readInt32();
    // if (!resp)
    //     return;

    // uint8_t* response = ;

    // if (!response || !resp)
    //     return;

    // (void)response_len;
    // resp->responseType = TYPE_INT;
    // resp->responseData.value_int = response;
}

void responseRawShow(RILResponse *resp)
{
    // int response;
    // int response_len;
    // response_len = p.readInt32();
    // response = p.readInt32();

    // if (!response || !resp)
    //     return;

    // (void)response_len;
    // resp->responseType = TYPE_INT;
    // resp->responseData.value_int = response;
}

void responseRawFree(RILResponse *resp)
{
    // int response;
    // int response_len;
    // response_len = p.readInt32();
    // response = p.readInt32();

    // if (!response || !resp)
    //     return;

    // (void)response_len;
    // resp->responseType = TYPE_INT;
    // resp->responseData.value_int = response;
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
    LOGI << "  simResponse = " << response->simResponse << ENDL;
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

//     int num;
//     int voiceSettings;
//     ArrayList<DriverCall> response;
//     DriverCall dc;

//     num = p.readInt32();
//     response = new ArrayList<DriverCall>(num);

//     for (int i = 0; i < num; i++)
//     {
//         dc = new DriverCall();

//         dc.state = DriverCall.stateFromCLCC(p.readInt32());
//         dc.index = p.readInt32();
//         dc.TOA = p.readInt32();
//         dc.isMpty = (0 != p.readInt32());
//         dc.isMT = (0 != p.readInt32());
//         dc.als = p.readInt32();
//         voiceSettings = p.readInt32();
//         dc.isVoice = (0 == voiceSettings) ? false : true;
//         dc.isVoicePrivacy = (0 != p.readInt32());
//         dc.number = p.readString();
//         int np = p.readInt32();
//         dc.numberPresentation = DriverCall.presentationFromCLIP(np);
//         dc.name = p.readString();
//         dc.namePresentation = p.readInt32();
//         int uusInfoPresent = p.readInt32();
//         if (uusInfoPresent == 1)
//         {
//             dc.uusInfo = new UUSInfo();
//             dc.uusInfo.setType(p.readInt32());
//             dc.uusInfo.setDcs(p.readInt32());
//             byte[] userData = p.createByteArray();
//             dc.uusInfo.setUserData(userData);
//             riljLogv(String.format("Incoming UUS : type=%d, dcs=%d, length=%d",
//                                    dc.uusInfo.getType(), dc.uusInfo.getDcs(),
//                                    dc.uusInfo.getUserData().length));
//             riljLogv("Incoming UUS : data (string)=" + new String(dc.uusInfo.getUserData()));
//             riljLogv("Incoming UUS : data (hex): " + IccUtils.bytesToHexString(dc.uusInfo.getUserData()));
//         }
//         else
//         {
//             riljLogv("Incoming UUS : NOT present!");
//         }

//         // Make sure there's a leading + on addresses with a TOA of 145
//         dc.number = PhoneNumberUtils.stringFromStringAndTOA(dc.number, dc.TOA);

//         response.add(dc);

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
    return responseDataCallList(p, resp);
}

void responseSetupDataCallShow(RILResponse *resp)
{
    return responseDataCallListShow(resp);
}

void responseSetupDataCallFree(RILResponse *resp)
{
    return responseDataCallListFree(resp);
}

void responseOperatorInfos(Parcel &p, RILResponse *resp)
{
    //     String strings[] = (String[])responseStrings(p);
    //     ArrayList<OperatorInfo> ret;

    //     if (strings.length % 4 != 0)
    //     {
    //         throw new RuntimeException(
    //             "RIL_REQUEST_QUERY_AVAILABLE_NETWORKS: invalid response. Got " + strings.length + " strings, expected multible of 4");
    //     }

    //     ret = new ArrayList<OperatorInfo>(strings.length / 4);

    //     for (int i = 0; i < strings.length; i += 4)
    //     {
    //         ret.add(
    //             new OperatorInfo(
    //                 strings[i + 0],
    //                 strings[i + 1],
    //                 strings[i + 2],
    //                 strings[i + 3]));
    //     }
}

void responseOperatorInfosShow(RILResponse *resp) {}

void responseOperatorInfosFree(RILResponse *resp) {}

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
    //     int num;
    //     ArrayList<SmsBroadcastConfigInfo> response;
    //     SmsBroadcastConfigInfo info;

    //     num = p.readInt32();
    //     response = new ArrayList<SmsBroadcastConfigInfo>(num);

    //     for (int i = 0; i < num; i++)
    //     {
    //         int fromId = p.readInt32();
    //         int toId = p.readInt32();
    //         int fromScheme = p.readInt32();
    //         int toScheme = p.readInt32();
    //         boolean selected = (p.readInt32() == 1);

    //         info = new SmsBroadcastConfigInfo(fromId, toId, fromScheme,
    //                                           toScheme, selected);
    //         response.add(info);
    //     }
}

void responseCdmaBroadcastConfig(Parcel &p, RILResponse *resp)
{
    //     int numServiceCategories;
    //     int response[];

    //     numServiceCategories = p.readInt32();

    //     if (numServiceCategories == 0)
    //     {
    //         // TODO: The logic of providing default values should
    //         // not be done by this transport layer. And needs to
    //         // be done by the vendor ril or application logic.
    //         int numInts;
    //         numInts = CDMA_BROADCAST_SMS_NO_OF_SERVICE_CATEGORIES * CDMA_BSI_NO_OF_INTS_STRUCT + 1;
    //         response = new int[numInts];

    //         // Faking a default record for all possible records.
    //         response[0] = CDMA_BROADCAST_SMS_NO_OF_SERVICE_CATEGORIES;

    //         // Loop over CDMA_BROADCAST_SMS_NO_OF_SERVICE_CATEGORIES set 'english' as
    //         // default language and selection status to false for all.
    //         for (int i = 1; i < numInts; i += CDMA_BSI_NO_OF_INTS_STRUCT)
    //         {
    //             response[i + 0] = i / CDMA_BSI_NO_OF_INTS_STRUCT;
    //             response[i + 1] = 1;
    //             response[i + 2] = 0;
    //         }
    //     }
    //     else
    //     {
    //         int numInts;
    //         numInts = (numServiceCategories * CDMA_BSI_NO_OF_INTS_STRUCT) + 1;
    //         response = new int[numInts];

    //         response[0] = numServiceCategories;
    //         for (int i = 1; i < numInts; i++)
    //         {
    //             response[i] = p.readInt32();
    //         }
    //     }
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
    //     int numberOfInfoRecs;
    //     ArrayList<CdmaInformationRecords> response;

    //     /**
    //          * Loop through all of the information records unmarshalling them
    //          * and converting them to Java Objects.
    //          */
    //     numberOfInfoRecs = p.readInt32();
    //     response = new ArrayList<CdmaInformationRecords>(numberOfInfoRecs);

    //     for (int i = 0; i < numberOfInfoRecs; i++)
    //     {
    //         CdmaInformationRecords InfoRec = new CdmaInformationRecords(p);
    //         response.add(InfoRec);
    //     }
}
void responseCdmaInformationRecordShow(RILResponse *resp) {}
void responseCdmaInformationRecordFree(RILResponse *resp) {}

void responseCdmaCallWaiting(Parcel &p, RILResponse *resp)
{
    //     CdmaCallWaitingNotification notification = new CdmaCallWaitingNotification();

    //     notification.number = p.readString();
    //     notification.numberPresentation = notification.presentationFromCLIP(p.readInt32());
    //     notification.name = p.readString();
    //     notification.namePresentation = notification.numberPresentation;
    //     notification.isPresent = p.readInt32();
    //     notification.signalType = p.readInt32();
    //     notification.alertPitch = p.readInt32();
    //     notification.signal = p.readInt32();
    //     notification.numberType = p.readInt32();
    //     notification.numberPlan = p.readInt32();
}
void responseCdmaCallWaitingShow(RILResponse *resp) {}
void responseCdmaCallWaitingFree(RILResponse *resp) {}

void responseCallRing(Parcel &p, RILResponse *resp)
{
    //     char response[] = new char[4];

    //     response[0] = (char)p.readInt32(); // isPresent
    //     response[1] = (char)p.readInt32(); // signalType
    //     response[2] = (char)p.readInt32(); // alertPitch
    //     response[3] = (char)p.readInt32(); // signal
}

void responseCallRingShow(RILResponse *resp) {}
void responseCallRingFree(RILResponse *resp) {}

void responseCdmaSms(Parcel &, RILResponse *)
{
}
void responseCdmaSmsShow(RILResponse *) {}
void responseCdmaSmsFree(RILResponse *) {}

// private
// void notifyRegistrantsCdmaInfoRec(CdmaInformationRecords infoRec)
// {
//     int response = RIL_UNSOL_CDMA_INFO_REC;
//     if (infoRec.record instanceof CdmaInformationRecords.CdmaDisplayInfoRec)
//     {
//         if (mDisplayInfoRegistrants != null)
//         {
//
//                 unsljLogRet(response, infoRec.record);
//             mDisplayInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaSignalInfoRec)
//     {
//         if (mSignalInfoRegistrants != null)
//         {
//
//                 unsljLogRet(response, infoRec.record);
//             mSignalInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaNumberInfoRec)
//     {
//         if (mNumberInfoRegistrants != null)
//         {
//
//                 unsljLogRet(response, infoRec.record);
//             mNumberInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaRedirectingNumberInfoRec)
//     {
//         if (mRedirNumInfoRegistrants != null)
//         {
//
//                 unsljLogRet(response, infoRec.record);
//             mRedirNumInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaLineControlInfoRec)
//     {
//         if (mLineControlInfoRegistrants != null)
//         {
//
//                 unsljLogRet(response, infoRec.record);
//             mLineControlInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaT53ClirInfoRec)
//     {
//         if (mT53ClirInfoRegistrants != null)
//         {
//
//                 unsljLogRet(response, infoRec.record);
//             mT53ClirInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaT53AudioControlInfoRec)
//     {
//         if (mT53AudCntrlInfoRegistrants != null)
//         {
//
//                 unsljLogRet(response, infoRec.record);
//             mT53AudCntrlInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
// }

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
        return "UNSOL_ON_USSD_REQUEST";
    case RIL_UNSOL_NITZ_TIME_RECEIVED:
        return "UNSOL_NITZ_TIME_RECEIVED";
    case RIL_UNSOL_SIGNAL_STRENGTH:
        return "UNSOL_SIGNAL_STRENGTH";
    case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
        return "UNSOL_DATA_CALL_LIST_CHANGED";
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
        return "UNSOL_SIM_SMS_STORAGE_FULL";
    case RIL_UNSOL_SIM_REFRESH:
        return "UNSOL_SIM_REFRESH";
    case RIL_UNSOL_CALL_RING:
        return "UNSOL_CALL_RING";
    case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
        return "UNSOL_RESPONSE_SIM_STATUS_CHANGED";
    case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
        return "UNSOL_RESPONSE_CDMA_NEW_SMS";
    case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
        return "UNSOL_RESPONSE_NEW_BROADCAST_SMS";
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
        return "UNSOL_RINGBACK_TONG";
    case RIL_UNSOL_RESEND_INCALL_MUTE:
        return "UNSOL_RESEND_INCALL_MUTE";
    case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
        return "CDMA_SUBSCRIPTION_SOURCE_CHANGED";
    case RIL_UNSOL_CDMA_PRL_CHANGED:
        return "UNSOL_CDMA_PRL_CHANGED";
    case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
        return "UNSOL_EXIT_EMERGENCY_CALLBACK_MODE";
    case RIL_UNSOL_RIL_CONNECTED:
        return "UNSOL_RIL_CONNECTED";
    case RIL_UNSOL_VOICE_RADIO_TECH_CHANGED:
        return "RIL_UNSOL_VOICE_RADIO_TECH_CHANGED";
    case RIL_UNSOL_CELL_INFO_LIST:
        return "RIL_UNSOL_CELL_INFO_LIST";
    case RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED:
        return "RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED";
    case RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED:
        return "RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED";
    case RIL_UNSOL_SRVCC_STATE_NOTIFY:
        return "RIL_UNSOL_SRVCC_STATE_NOTIFY";
    case RIL_UNSOL_HARDWARE_CONFIG_CHANGED:
        return "RIL_UNSOL_HARDWARE_CONFIG_CHANGED";
    case RIL_UNSOL_DC_RT_INFO_CHANGED:
        return "RIL_UNSOL_DC_RT_INFO_CHANGED";
    case RIL_UNSOL_RADIO_CAPABILITY:
        return "RIL_UNSOL_RADIO_CAPABILITY";
    case RIL_UNSOL_ON_SS:
        return "RIL_UNSOL_ON_SS";
    case RIL_UNSOL_STK_CC_ALPHA_NOTIFY:
        return "RIL_UNSOL_STK_CC_ALPHA_NOTIFY";
    case RIL_UNSOL_LCEDATA_RECV:
        return "RIL_UNSOL_LCEDATA_RECV";

    case RIL_UNSOL_RESPONSE_IMS_CALL_STATE_CHANGED:
        return "RIL_UNSOL_RESPONSE_IMS_CALL_STATE_CHANGED";
    case RIL_UNSOL_RESPONSE_VIDEO_QUALITY:
        return "RIL_UNSOL_RESPONSE_VIDEO_QUALITY";
    case RIL_UNSOL_RESPONSE_IMS_BEARER_ESTABLISTED:
        return "RIL_UNSOL_RESPONSE_IMS_BEARER_ESTABLISTED";
    case RIL_UNSOL_IMS_HANDOVER_REQUEST:
        return "RIL_UNSOL_IMS_HANDOVER_REQUEST";
    case RIL_UNSOL_IMS_HANDOVER_STATUS_CHANGE:
        return "RIL_UNSOL_IMS_HANDOVER_STATUS_CHANGE";
    case RIL_UNSOL_IMS_NETWORK_INFO_CHANGE:
        return "RIL_UNSOL_IMS_NETWORK_INFO_CHANGE";
    case RIL_UNSOL_IMS_REGISTER_ADDRESS_CHANGE:
        return "RIL_UNSOL_IMS_REGISTER_ADDRESS_CHANGE";
    case RIL_UNSOL_IMS_WIFI_PARAM:
        return "RIL_UNSOL_IMS_WIFI_PARAM";
    case RIL_UNSOL_IMS_NETWORK_STATE_CHANGED:
        return "RIL_UNSOL_IMS_NETWORK_STATE_CHANGED";

    case RIL_EXT_UNSOL_VIDEOPHONE_CODEC:
        return "RIL_EXT_UNSOL_VIDEOPHONE_CODEC";
    case RIL_EXT_UNSOL_VIDEOPHONE_DSCI:
        return "RIL_EXT_UNSOL_VIDEOPHONE_DSCI";
    case RIL_EXT_UNSOL_VIDEOPHONE_STRING:
        return "RIL_EXT_UNSOL_VIDEOPHONE_STRING";
    case RIL_EXT_UNSOL_VIDEOPHONE_REMOTE_MEDIA:
        return "RIL_EXT_UNSOL_VIDEOPHONE_REMOTE_MEDIA";
    case RIL_EXT_UNSOL_VIDEOPHONE_MM_RING:
        return "RIL_EXT_UNSOL_VIDEOPHONE_MM_RING";
    case RIL_EXT_UNSOL_VIDEOPHONE_RELEASING:
        return "RIL_EXT_UNSOL_VIDEOPHONE_RELEASING";
    case RIL_EXT_UNSOL_VIDEOPHONE_RECORD_VIDEO:
        return "RIL_EXT_UNSOL_VIDEOPHONE_RECORD_VIDEO";
    case RIL_EXT_UNSOL_VIDEOPHONE_MEDIA_START:
        return "RIL_EXT_UNSOL_VIDEOPHONE_MEDIA_START";
    case RIL_EXT_UNSOL_ECC_NETWORKLIST_CHANGED:
        return "RIL_EXT_UNSOL_ECC_NETWORKLIST_CHANGED";
    case RIL_EXT_UNSOL_RAU_SUCCESS:
        return "RIL_EXT_UNSOL_RAU_SUCCESS";
    case RIL_EXT_UNSOL_CLEAR_CODE_FALLBACK:
        return "RIL_EXT_UNSOL_CLEAR_CODE_FALLBACK";
    case RIL_EXT_UNSOL_RIL_CONNECTED:
        return "RIL_EXT_UNSOL_RIL_CONNECTED";
    case RIL_EXT_UNSOL_SIMLOCK_STATUS_CHANGED:
        return "RIL_EXT_UNSOL_SIMLOCK_STATUS_CHANGED";
    case RIL_EXT_UNSOL_SIMLOCK_SIM_EXPIRED:
        return "RIL_EXT_UNSOL_SIMLOCK_SIM_EXPIRED";
    case RIL_EXT_UNSOL_BAND_INFO:
        return "RIL_EXT_UNSOL_BAND_INFO";
    case RIL_EXT_UNSOL_SWITCH_PRIMARY_CARD:
        return "RIL_EXT_UNSOL_SWITCH_PRIMARY_CARD";
    case RIL_EXT_UNSOL_SIM_PS_REJECT:
        return "RIL_EXT_UNSOL_SIM_PS_REJECT";
    case RIL_EXT_UNSOL_SETUP_DATA_FOR_CP:
        return "RIL_EXT_UNSOL_SETUP_DATA_FOR_CP";
    case RIL_EXT_UNSOL_SIMMGR_SIM_STATUS_CHANGED:
        return "RIL_EXT_UNSOL_SIMMGR_SIM_STATUS_CHANGED";
    case RIL_EXT_UNSOL_RADIO_CAPABILITY_CHANGED:
        return "RIL_EXT_UNSOL_RADIO_CAPABILITY_CHANGED";
    case RIL_EXT_UNSOL_EARLY_MEDIA:
        return "RIL_EXT_UNSOL_EARLY_MEDIA";
    case RIL_EXT_UNSOL_ATROUTER_RSP:
        return "RIL_EXT_UNSOL_ATROUTER_RSP";
    case RIL_EXT_UNSOL_DATA_PDP_INFO:
        return "RIL_EXT_UNSOL_DATA_PDP_INFO";

#ifdef ORCA_FEATURE_5G
    case RIL_EXT_UNSOL_PHYSICAL_CHANNEL_CONFIG:
        return "RIL_EXT_UNSOL_PHYSICAL_CHANNEL_CONFIG";
    case RIL_EXT_UNSOL_NETWORK_SCAN_RESULT:
        return "RIL_EXT_UNSOL_NETWORK_SCAN_RESULT";
    case RIL_EXT_UNSOL_SIGNAL_STRENGTH:
        return "RIL_EXT_UNSOL_SIGNAL_STRENGTH";
    case RIL_EXT_UNSOL_SIGNAL_CONN_STATUS:
        return "RIL_EXT_UNSOL_SIGNAL_CONN_STATUS";
    case RIL_EXT_UNSOL_PPP_RSP:
        return "RIL_EXT_UNSOL_PPP_RSP";
    case RIL_EXT_UNSOL_PPP_DATA_PDP_INFO:
        return "RIL_EXT_UNSOL_PPP_DATA_PDP_INFO";
#else
    case RIL_EXT_UNSOL_PPP_RSP:
        return "RIL_EXT_UNSOL_PPP_RSP";
    case RIL_EXT_UNSOL_PPP_DATA_PDP_INFO:
        return "RIL_EXT_UNSOL_PPP_DATA_PDP_INFO";
#endif
    default:
        return "<unknown reponse>";
    }
}
