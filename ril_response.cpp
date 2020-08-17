#include "ril.h"
#include "ril_request.h"
#include "ril_response.h"
#include "logger.h"

void RilResponse::setResponseID(int id)
{
    mResponseID = id;
}

void RilResponse::setResponseURCInfo(bool isurc)
{
    mIsURC = isurc;
}

void RilResponse::responseStrings(Parcel &p)
{
    int num;
    mRespType = RESP_STR_ARR;

    num = p.readInt();
    for (int i = 0; i < num; i++)
    {
        auto str = p.readString();
        mRespVecString.emplace_back(str);
        p.freeString(str);
    }
}

void RilResponse::responseString(Parcel &p)
{
    const char *response = p.readString();
    mRespString = response;
    p.freeString(response);

    LOGD << "UNMARSHAL: " << mRespString << ENDL;
}

void RilResponse::responseInts(Parcel &p)
{
    int numInts;
    std::vector<int> response;

    numInts = p.readInt();

    for (int i = 0; i < numInts; i++)
    {
        response.emplace_back(p.readInt());
    }
}

void RilResponse::responseVoid(Parcel &p)
{
}

/***** Private Methods ******/

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

void RilResponse::responseCallForward(Parcel &p)
{
    //     int numInfos;
    //     CallForwardInfo infos[];

    //     numInfos = p.readInt();

    //     infos = new CallForwardInfo[numInfos];

    //     for (int i = 0; i < numInfos; i++)
    //     {
    //         infos[i] = new CallForwardInfo();

    //         infos[i].status = p.readInt();
    //         infos[i].reason = p.readInt();
    //         infos[i].serviceClass = p.readInt();
    //         infos[i].toa = p.readInt();
    //         infos[i].number = p.readString();
    //         infos[i].timeSeconds = p.readInt();
    //     }
}

void RilResponse::responseSuppServiceNotification(Parcel &p)
{
    //     SuppServiceNotification notification = new SuppServiceNotification();

    //     notification.notificationType = p.readInt();
    //     notification.code = p.readInt();
    //     notification.index = p.readInt();
    //     notification.type = p.readInt();
    //     notification.number = p.readString();
}

void RilResponse::responseCdmaSms(Parcel &p)
{
    //     SmsMessage sms;
    //     sms = SmsMessage.newFromParcel(p);
}

void RilResponse::responseRaw(Parcel &p)
{
    // int num;
    // byte response[];

    // response = p.createByteArray();

    // return response;
}

void RilResponse::responseSMS(Parcel &p)
{
    int messageRef, errorCode;
    std::string ackPDU;

    messageRef = p.readInt();
    ackPDU = p.readString();
    errorCode = p.readInt();

    // SmsResponse response = new SmsResponse(messageRef, ackPDU, errorCode);
}

void RilResponse::responseICC_IO(Parcel &p)
{
    //     int sw1, sw2;
    //     byte data[] = null;
    //     RilResponse *ret;

    //     sw1 = p.readInt();
    //     sw2 = p.readInt();

    //     String s = p.readString();

    //     if (RILJ_LOGV)
    //         riljLog("< iccIO: " + " 0x" + Integer.toHexString(sw1) + " 0x" + Integer.toHexString(sw2) + " " + s);

    //     return new IccIoResult(sw1, sw2, s);
}

void RilResponse::responseIccCardStatus(Parcel &p)
{
    //     IccCardApplication ca;

    //     IccCardStatus status = new IccCardStatus();
    //     status.setCardState(p.readInt());
    //     status.setUniversalPinState(p.readInt());
    //     status.setGsmUmtsSubscriptionAppIndex(p.readInt());
    //     status.setCdmaSubscriptionAppIndex(p.readInt());
    //     status.setImsSubscriptionAppIndex(p.readInt());
    //     int numApplications = p.readInt();

    //     // limit to maximum allowed applications
    //     if (numApplications > IccCardStatus.CARD_MAX_APPS)
    //     {
    //         numApplications = IccCardStatus.CARD_MAX_APPS;
    //     }
    //     status.setNumApplications(numApplications);

    //     for (int i = 0; i < numApplications; i++)
    //     {
    //         ca = new IccCardApplication();
    //         ca.app_type = ca.AppTypeFromRILInt(p.readInt());
    //         ca.app_state = ca.AppStateFromRILInt(p.readInt());
    //         ca.perso_substate = ca.PersoSubstateFromRILInt(p.readInt());
    //         ca.aid = p.readString();
    //         ca.app_label = p.readString();
    //         ca.pin1_replaced = p.readInt();
    //         ca.pin1 = ca.PinStateFromRILInt(p.readInt());
    //         ca.pin2 = ca.PinStateFromRILInt(p.readInt());
    //         status.addApplication(ca);
    //     }
}

void RilResponse::responseCallList(Parcel &p)
{
    //     int num;
    //     int voiceSettings;
    //     ArrayList<DriverCall> response;
    //     DriverCall dc;

    //     num = p.readInt();
    //     response = new ArrayList<DriverCall>(num);

    //     for (int i = 0; i < num; i++)
    //     {
    //         dc = new DriverCall();

    //         dc.state = DriverCall.stateFromCLCC(p.readInt());
    //         dc.index = p.readInt();
    //         dc.TOA = p.readInt();
    //         dc.isMpty = (0 != p.readInt());
    //         dc.isMT = (0 != p.readInt());
    //         dc.als = p.readInt();
    //         voiceSettings = p.readInt();
    //         dc.isVoice = (0 == voiceSettings) ? false : true;
    //         dc.isVoicePrivacy = (0 != p.readInt());
    //         dc.number = p.readString();
    //         int np = p.readInt();
    //         dc.numberPresentation = DriverCall.presentationFromCLIP(np);
    //         dc.name = p.readString();
    //         dc.namePresentation = p.readInt();
    //         int uusInfoPresent = p.readInt();
    //         if (uusInfoPresent == 1)
    //         {
    //             dc.uusInfo = new UUSInfo();
    //             dc.uusInfo.setType(p.readInt());
    //             dc.uusInfo.setDcs(p.readInt());
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

    //         if (dc.isVoicePrivacy)
    //         {
    //             mVoicePrivacyOnRegistrants.notifyRegistrants();
    //             riljLog("InCall VoicePrivacy is enabled");
    //         }
    //         else
    //         {
    //             mVoicePrivacyOffRegistrants.notifyRegistrants();
    //             riljLog("InCall VoicePrivacy is disabled");
    //         }
    //     }

    //     Collections.sort(response);
}

// private
// DataCallState getDataCallState(Parcel &p, int version)
// {
//     DataCallState dataCall = new DataCallState();

//     dataCall.version = version;
//     if (version < 5)
//     {
//         dataCall.cid = p.readInt();
//         dataCall.active = p.readInt();
//         dataCall.type = p.readString();
//         String addresses = p.readString();
//         if (!TextUtils.isEmpty(addresses))
//         {
//             dataCall.addresses = addresses.split(" ");
//         }
//     }
//     else
//     {
//         dataCall.status = p.readInt();
//         dataCall.suggestedRetryTime = p.readInt();
//         dataCall.cid = p.readInt();
//         dataCall.active = p.readInt();
//         dataCall.type = p.readString();
//         dataCall.ifname = p.readString();
//         if ((dataCall.status == DataConnection.FailCause.NONE.getErrorCode()) &&
//             TextUtils.isEmpty(dataCall.ifname))
//         {
//             throw new RuntimeException("getDataCallState, no ifname");
//         }
//         String addresses = p.readString();
//         if (!TextUtils.isEmpty(addresses))
//         {
//             dataCall.addresses = addresses.split(" ");
//         }
//         String dnses = p.readString();
//         if (!TextUtils.isEmpty(dnses))
//         {
//             dataCall.dnses = dnses.split(" ");
//         }
//         String gateways = p.readString();
//         if (!TextUtils.isEmpty(gateways))
//         {
//             dataCall.gateways = gateways.split(" ");
//         }
//     }
//     return dataCall;
// }

void RilResponse::responseDataCallList(Parcel &p)
{
    //     ArrayList<DataCallState> response;

    //     int ver = p.readInt();
    //     int num = p.readInt();
    //     riljLog("responseDataCallList ver=" + ver + " num=" + num);

    //     response = new ArrayList<DataCallState>(num);
    //     for (int i = 0; i < num; i++)
    //     {
    //         response.add(getDataCallState(p, ver));
    //     }

    //     return response;
}

void RilResponse::responseSetupDataCall(Parcel &p)
{
    //     int ver = p.readInt();
    //     int num = p.readInt();
    //     if (RILJ_LOGV)
    //         riljLog("responseSetupDataCall ver=" + ver + " num=" + num);

    //     DataCallState dataCall;

    //     if (ver < 5)
    //     {
    //         dataCall = new DataCallState();
    //         dataCall.version = ver;
    //         dataCall.cid = Integer.parseInt(p.readString());
    //         dataCall.ifname = p.readString();
    //         if (TextUtils.isEmpty(dataCall.ifname))
    //         {
    //             throw new RuntimeException(
    //                 "RIL_REQUEST_SETUP_DATA_CALL response, no ifname");
    //         }
    //         String addresses = p.readString();
    //         if (!TextUtils.isEmpty(addresses))
    //         {
    //             dataCall.addresses = addresses.split(" ");
    //         }
    //         if (num >= 4)
    //         {
    //             String dnses = p.readString();
    //
    //                 riljLog("responseSetupDataCall got dnses=" + dnses);
    //             if (!TextUtils.isEmpty(dnses))
    //             {
    //                 dataCall.dnses = dnses.split(" ");
    //             }
    //         }
    //         if (num >= 5)
    //         {
    //             String gateways = p.readString();
    //
    //                 riljLog("responseSetupDataCall got gateways=" + gateways);
    //             if (!TextUtils.isEmpty(gateways))
    //             {
    //                 dataCall.gateways = gateways.split(" ");
    //             }
    //         }
    //     }
    //     else
    //     {
    //         if (num != 1)
    //         {
    //             throw new RuntimeException(
    //                 "RIL_REQUEST_SETUP_DATA_CALL response expecting 1 RIL_Data_Call_response_v5" + " got " + num);
    //         }
    //         dataCall = getDataCallState(p, ver);
    //     }
}

void RilResponse::responseOperatorInfos(Parcel &p)
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

void RilResponse::responseCellList(Parcel &p)
{
    //     int num, rssi;
    //     String location;
    //     ArrayList<NeighboringCellInfo> response;
    //     NeighboringCellInfo cell;

    //     num = p.readInt();
    //     response = new ArrayList<NeighboringCellInfo>();

    //     // Determine the radio access type
    //     String radioString = SystemProperties.get(
    //         TelephonyProperties.PROPERTY_DATA_NETWORK_TYPE, "unknown");
    //     int radioType;
    //     if (radioString.equals("GPRS"))
    //     {
    //         radioType = NETWORK_TYPE_GPRS;
    //     }
    //     else if (radioString.equals("EDGE"))
    //     {
    //         radioType = NETWORK_TYPE_EDGE;
    //     }
    //     else if (radioString.equals("UMTS"))
    //     {
    //         radioType = NETWORK_TYPE_UMTS;
    //     }
    //     else if (radioString.equals("HSDPA"))
    //     {
    //         radioType = NETWORK_TYPE_HSDPA;
    //     }
    //     else if (radioString.equals("HSUPA"))
    //     {
    //         radioType = NETWORK_TYPE_HSUPA;
    //     }
    //     else if (radioString.equals("HSPA"))
    //     {
    //         radioType = NETWORK_TYPE_HSPA;
    //     }
    //     else
    //     {
    //         radioType = NETWORK_TYPE_UNKNOWN;
    //     }

    //     // Interpret the location based on radio access type
    //     if (radioType != NETWORK_TYPE_UNKNOWN)
    //     {
    //         for (int i = 0; i < num; i++)
    //         {
    //             rssi = p.readInt();
    //             location = p.readString();
    //             cell = new NeighboringCellInfo(rssi, location, radioType);
    //             response.add(cell);
    //         }
    //     }
}

void RilResponse::responseGetPreferredNetworkType(Parcel &p)
{
    //     int[] response = (int[])responseInts(p);

    //     if (response.length >= 1)
    //     {
    //         // Since this is the response for getPreferredNetworkType
    //         // we'll assume that it should be the value we want the
    //         // vendor ril to take if we reestablish a connection to it.
    //         mPreferredNetworkType = response[0];
    //     }
    //     return response;
}

void RilResponse::responseGmsBroadcastConfig(Parcel &p)
{
    //     int num;
    //     ArrayList<SmsBroadcastConfigInfo> response;
    //     SmsBroadcastConfigInfo info;

    //     num = p.readInt();
    //     response = new ArrayList<SmsBroadcastConfigInfo>(num);

    //     for (int i = 0; i < num; i++)
    //     {
    //         int fromId = p.readInt();
    //         int toId = p.readInt();
    //         int fromScheme = p.readInt();
    //         int toScheme = p.readInt();
    //         boolean selected = (p.readInt() == 1);

    //         info = new SmsBroadcastConfigInfo(fromId, toId, fromScheme,
    //                                           toScheme, selected);
    //         response.add(info);
    //     }
}

void RilResponse::responseCdmaBroadcastConfig(Parcel &p)
{
    //     int numServiceCategories;
    //     int response[];

    //     numServiceCategories = p.readInt();

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
    //             response[i] = p.readInt();
    //         }
    //     }
}

void RilResponse::responseSignalStrength(Parcel &p)
{
    int numInts = 12;
    mRespType = RESP_INT_ARR;

    /* TODO: Add SignalStrength class to match RIL_SignalStrength */
    for (int i = 0; i < numInts; i++)
    {
        mRespVecInt.emplace_back(p.readInt());
        LOGI << mRespVecInt[i] << ENDL;
    }
}

void RilResponse::responseCdmaInformationRecord(Parcel &p)
{
    //     int numberOfInfoRecs;
    //     ArrayList<CdmaInformationRecords> response;

    //     /**
    //          * Loop through all of the information records unmarshalling them
    //          * and converting them to Java Objects.
    //          */
    //     numberOfInfoRecs = p.readInt();
    //     response = new ArrayList<CdmaInformationRecords>(numberOfInfoRecs);

    //     for (int i = 0; i < numberOfInfoRecs; i++)
    //     {
    //         CdmaInformationRecords InfoRec = new CdmaInformationRecords(p);
    //         response.add(InfoRec);
    //     }
}

void RilResponse::responseCdmaCallWaiting(Parcel &p)
{
    //     CdmaCallWaitingNotification notification = new CdmaCallWaitingNotification();

    //     notification.number = p.readString();
    //     notification.numberPresentation = notification.presentationFromCLIP(p.readInt());
    //     notification.name = p.readString();
    //     notification.namePresentation = notification.numberPresentation;
    //     notification.isPresent = p.readInt();
    //     notification.signalType = p.readInt();
    //     notification.alertPitch = p.readInt();
    //     notification.signal = p.readInt();
    //     notification.numberType = p.readInt();
    //     notification.numberPlan = p.readInt();
}

void RilResponse::responseCallRing(Parcel &p)
{
    //     char response[] = new char[4];

    //     response[0] = (char)p.readInt(); // isPresent
    //     response[1] = (char)p.readInt(); // signalType
    //     response[2] = (char)p.readInt(); // alertPitch
    //     response[3] = (char)p.readInt(); // signal
}

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

std::string RilResponse::responseToString(int respid)
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
    case RIL_UNSOl_CDMA_PRL_CHANGED:
        return "UNSOL_CDMA_PRL_CHANGED";
    case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
        return "UNSOL_EXIT_EMERGENCY_CALLBACK_MODE";
    case RIL_UNSOL_RIL_CONNECTED:
        return "UNSOL_RIL_CONNECTED";
    default:
        return "<unknown reponse>";
    }
}
