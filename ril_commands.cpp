#include "ril.h"
#include "ril_request.h"
#include "ril_response.h"
#include "logger.h"

#define RIL_VERBOSE 0

void getIccCardStatus(RilResponse *result)
{
    //Note: This RIL request has not been renamed to ICC,
    //       but this request is also valid for SIM and RUIM
    RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_SIM_STATUS, result);

    if (RIL_VERBOSE)
        LOGV << rr->serialString() << "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
}

// supplyIccPin(String pin, RilResponse *result)
// {
//     supplyIccPinForApp(pin, null, result);
// }

// void supplyIccPinForApp(String pin, String aid, RilResponse *result)
// {
//     //Note: This RIL request has not been renamed to ICC,
//     //       but this request is also valid for SIM and RUIM
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ENTER_SIM_PIN, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(2);
//     rr.mp.writeString(pin);
//     rr.mp.writeString(aid);

//     RILREQUEST::send(rr);
// }

// void supplyIccPuk(String puk, String newPin, RilResponse *result)
// {
//     supplyIccPukForApp(puk, newPin, null, result);
// }

// void supplyIccPukForApp(String puk, String newPin, String aid, RilResponse *result)
// {
//     //Note: This RIL request has not been renamed to ICC,
//     //       but this request is also valid for SIM and RUIM
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ENTER_SIM_PUK, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(3);
//     rr.mp.writeString(puk);
//     rr.mp.writeString(newPin);
//     rr.mp.writeString(aid);

//     RILREQUEST::send(rr);
// }

// void supplyIccPin2(String pin, RilResponse *result)
// {
//     supplyIccPin2ForApp(pin, null, result);
// }

// void supplyIccPin2ForApp(String pin, String aid, RilResponse *result)
// {
//     //Note: This RIL request has not been renamed to ICC,
//     //       but this request is also valid for SIM and RUIM
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ENTER_SIM_PIN2, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(2);
//     rr.mp.writeString(pin);
//     rr.mp.writeString(aid);

//     RILREQUEST::send(rr);
// }

// void supplyIccPuk2(String puk2, String newPin2, RilResponse *result)
// {
//     supplyIccPuk2ForApp(puk2, newPin2, null, result);
// }

// void supplyIccPuk2ForApp(String puk, String newPin2, String aid, RilResponse *result)
// {
//     //Note: This RIL request has not been renamed to ICC,
//     //       but this request is also valid for SIM and RUIM
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ENTER_SIM_PUK2, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(3);
//     rr.mp.writeString(puk);
//     rr.mp.writeString(newPin2);
//     rr.mp.writeString(aid);

//     RILREQUEST::send(rr);
// }

// void changeIccPin(String oldPin, String newPin, RilResponse *result)
// {
//     changeIccPinForApp(oldPin, newPin, null, result);
// }

// void changeIccPinForApp(String oldPin, String newPin, String aid, RilResponse *result)
// {
//     //Note: This RIL request has not been renamed to ICC,
//     //       but this request is also valid for SIM and RUIM
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CHANGE_SIM_PIN, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(3);
//     rr.mp.writeString(oldPin);
//     rr.mp.writeString(newPin);
//     rr.mp.writeString(aid);

//     RILREQUEST::send(rr);
// }

// void changeIccPin2(String oldPin2, String newPin2, RilResponse *result)
// {
//     changeIccPin2ForApp(oldPin2, newPin2, null, result);
// }

// void changeIccPin2ForApp(String oldPin2, String newPin2, String aid, RilResponse *result)
// {
//     //Note: This RIL request has not been renamed to ICC,
//     //       but this request is also valid for SIM and RUIM
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CHANGE_SIM_PIN2, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(3);
//     rr.mp.writeString(oldPin2);
//     rr.mp.writeString(newPin2);
//     rr.mp.writeString(aid);

//     RILREQUEST::send(rr);
// }

// public
// void changeBarringPassword(String facility, String oldPwd, String newPwd, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CHANGE_BARRING_PASSWORD, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(3);
//     rr.mp.writeString(facility);
//     rr.mp.writeString(oldPwd);
//     rr.mp.writeString(newPwd);

//     RILREQUEST::send(rr);
// }

// public
// void supplyNetworkDepersonalization(String netpin, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeInt(1);
//     rr.mp.writeString(netpin);

//     RILREQUEST::send(rr);
// }

// public
// void getCurrentCalls(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_CURRENT_CALLS, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// @Deprecated public void
// getPDPContextList(RilResponse *result)
// {
//     getDataCallList(result);
// }

// public
// void getDataCallList(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DATA_CALL_LIST, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void dial(String address, int clirMode, RilResponse *result)
// {
//     dial(address, clirMode, null, result);
// }

// public
// void dial(String address, int clirMode, UUSInfo uusInfo, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DIAL, result);

//     rr.mp.writeString(address);
//     rr.mp.writeInt(clirMode);
//     rr.mp.writeInt(0); // UUS information is absent

//     if (uusInfo == null)
//     {
//         rr.mp.writeInt(0); // UUS information is absent
//     }
//     else
//     {
//         rr.mp.writeInt(1); // UUS information is present
//         rr.mp.writeInt(uusInfo.getType());
//         rr.mp.writeInt(uusInfo.getDcs());
//         rr.mp.writeByteArray(uusInfo.getUserData());
//     }

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getIMSI(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_IMSI, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getIMEI(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_IMEI, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getIMEISV(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_IMEISV, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void hangupConnection(int gsmIndex, RilResponse *result)
// {
//     if (RIL_VERBOSE)
//         riljLog("hangupConnection: gsmIndex=" + gsmIndex);

//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_HANGUP, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " +
//                 gsmIndex);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(gsmIndex);

//     RILREQUEST::send(rr);
// }

// public
// void hangupWaitingOrBackground(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND,
//                                         result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void hangupForegroundResumeBackground(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND,
//         result);
//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void switchWaitingOrHoldingAndActive(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE,
//         result);
//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void conference(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CONFERENCE, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void setPreferredVoicePrivacy(boolean enable, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE,
//                                         result);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(enable ? 1 : 0);

//     RILREQUEST::send(rr);
// }

// public
// void getPreferredVoicePrivacy(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE,
//                                         result);
//     RILREQUEST::send(rr);
// }

// public
// void separateConnection(int gsmIndex, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SEPARATE_CONNECTION, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + gsmIndex);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(gsmIndex);

//     RILREQUEST::send(rr);
// }

// public
// void acceptCall(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ANSWER, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void rejectCall(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_UDUB, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void explicitCallTransfer(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_EXPLICIT_CALL_TRANSFER, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getLastCallFailCause(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_LAST_CALL_FAIL_CAUSE, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * @deprecated
//      */
// public
// void getLastPdpFailCause(RilResponse *result)
// {
//     getLastDataCallFailCause(result);
// }

// /**
//      * The preferred new alternative to getLastPdpFailCause
//      */
// public
// void getLastDataCallFailCause(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void setMute(boolean enableMute, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_MUTE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + enableMute);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(enableMute ? 1 : 0);

//     RILREQUEST::send(rr);
// }

// public
// void getMute(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_MUTE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

void getSignalStrength(RilResponse *result)
{
    RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SIGNAL_STRENGTH, result);

    if (RIL_VERBOSE)
        LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

    RILREQUEST::send(rr);
}

// public
// void getVoiceRegistrationState(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_VOICE_REGISTRATION_STATE, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getDataRegistrationState(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DATA_REGISTRATION_STATE, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getOperator(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_OPERATOR, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void sendDtmf(char c, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DTMF, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeString(Character.toString(c));

//     RILREQUEST::send(rr);
// }

// public
// void startDtmf(char c, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DTMF_START, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeString(Character.toString(c));

//     RILREQUEST::send(rr);
// }

// public
// void stopDtmf(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DTMF_STOP, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void sendBurstDtmf(String dtmfString, int on, int off, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_BURST_DTMF, result);

//     rr.mp.writeInt(3);
//     rr.mp.writeString(dtmfString);
//     rr.mp.writeString(Integer.toString(on));
//     rr.mp.writeString(Integer.toString(off));

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + dtmfString);

//     RILREQUEST::send(rr);
// }

// public
// void sendSMS(String smscPDU, String pdu, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SEND_SMS, result);

//     rr.mp.writeInt(2);
//     rr.mp.writeString(smscPDU);
//     rr.mp.writeString(pdu);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void sendCdmaSms(byte[] pdu, RilResponse *result)
// {
//     int address_nbr_of_digits;
//     int subaddr_nbr_of_digits;
//     int bearerDataLength;
//     ByteArrayInputStream bais = new ByteArrayInputStream(pdu);
//     DataInputStream dis = new DataInputStream(bais);

//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_SEND_SMS, result);

//     try
//     {
//         rr.mp.writeInt(dis.readInt());        //teleServiceId
//         rr.mp.writeByte((byte)dis.readInt()); //servicePresent
//         rr.mp.writeInt(dis.readInt());        //serviceCategory
//         rr.mp.writeInt(dis.read());           //address_digit_mode
//         rr.mp.writeInt(dis.read());           //address_nbr_mode
//         rr.mp.writeInt(dis.read());           //address_ton
//         rr.mp.writeInt(dis.read());           //address_nbr_plan
//         address_nbr_of_digits = (byte)dis.read();
//         rr.mp.writeByte((byte)address_nbr_of_digits);
//         for (int i = 0; i < address_nbr_of_digits; i++)
//         {
//             rr.mp.writeByte(dis.readByte()); // address_orig_bytes[i]
//         }
//         rr.mp.writeInt(dis.read());        //subaddressType
//         rr.mp.writeByte((byte)dis.read()); //subaddr_odd
//         subaddr_nbr_of_digits = (byte)dis.read();
//         rr.mp.writeByte((byte)subaddr_nbr_of_digits);
//         for (int i = 0; i < subaddr_nbr_of_digits; i++)
//         {
//             rr.mp.writeByte(dis.readByte()); //subaddr_orig_bytes[i]
//         }

//         bearerDataLength = dis.read();
//         rr.mp.writeInt(bearerDataLength);
//         for (int i = 0; i < bearerDataLength; i++)
//         {
//             rr.mp.writeByte(dis.readByte()); //bearerData[i]
//         }
//     }
//     catch (IOException ex)
//     {
//         if (RIL_VERBOSE)
//             riljLog("sendSmsCdma: conversion from input stream to object failed: " + ex);
//     }

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void deleteSmsOnSim(int index, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DELETE_SMS_ON_SIM,
//                                         response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(index);

//     if (false)
//     {
//         if (RIL_VERBOSE)
//             LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + index);
//     }

//     RILREQUEST::send(rr);
// }

// public
// void deleteSmsOnRuim(int index, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM,
//                                         response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(index);

//     if (false)
//     {
//         if (RIL_VERBOSE)
//             LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + index);
//     }

//     RILREQUEST::send(rr);
// }

// public
// void writeSmsToSim(int status, String smsc, String pdu, RilResponse *response)
// {
//     status = translateStatus(status);

//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_WRITE_SMS_TO_SIM,
//                                         response);

//     rr.mp.writeInt(status);
//     rr.mp.writeString(pdu);
//     rr.mp.writeString(smsc);

//     if (false)
//     {
//         if (RIL_VERBOSE)
//             LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + status);
//     }

//     RILREQUEST::send(rr);
// }

// public
// void writeSmsToRuim(int status, String pdu, RilResponse *response)
// {
//     status = translateStatus(status);

//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM,
//                                         response);

//     rr.mp.writeInt(status);
//     rr.mp.writeString(pdu);

//     if (false)
//     {
//         if (RIL_VERBOSE)
//             LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + status);
//     }

//     RILREQUEST::send(rr);
// }

// /**
//      *  Translates EF_SMS status bits to a status value compatible with
//      *  SMS AT commands.  See TS 27.005 3.1.
//      */
// private
// int translateStatus(int status)
// {
//     switch (status & 0x7)
//     {
//     case SmsManager.STATUS_ON_ICC_READ:
//         return 1;
//     case SmsManager.STATUS_ON_ICC_UNREAD:
//         return 0;
//     case SmsManager.STATUS_ON_ICC_SENT:
//         return 3;
//     case SmsManager.STATUS_ON_ICC_UNSENT:
//         return 2;
//     }

//     // Default to READ.
//     return 1;
// }

// public
// void setupDataCall(String radioTechnology, String profile, String apn,
//                    String user, String password, String authType, String protocol,
//                    RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SETUP_DATA_CALL, result);

//     rr.mp.writeInt(7);

//     rr.mp.writeString(radioTechnology);
//     rr.mp.writeString(profile);
//     rr.mp.writeString(apn);
//     rr.mp.writeString(user);
//     rr.mp.writeString(password);
//     rr.mp.writeString(authType);
//     rr.mp.writeString(protocol);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + radioTechnology + " " + profile + " " + apn + " " + user + " " + password + " " + authType + " " + protocol);

//     RILREQUEST::send(rr);
// }

// public
// void deactivateDataCall(int cid, int reason, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DEACTIVATE_DATA_CALL, result);

//     rr.mp.writeInt(2);
//     rr.mp.writeString(Integer.toString(cid));
//     rr.mp.writeString(Integer.toString(reason));

//     if (RIL_VERBOSE)
//         riljLog(rr->serialString() + "> " +
//                 requestToString(rr.mRequest) + " " + cid + " " + reason);

//     RILREQUEST::send(rr);
// }

// public
// void setRadioPower(boolean on, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_RADIO_POWER, result);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(on ? 1 : 0);

//     if (RIL_VERBOSE)
//     {
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ (on ? " on" : " off"));
//     }

//     RILREQUEST::send(rr);
// }

// public
// void setSuppServiceNotifications(boolean enable, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION, result);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(enable ? 1 : 0);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void acknowledgeLastIncomingGsmSms(boolean success, int cause, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SMS_ACKNOWLEDGE, result);

//     rr.mp.writeInt(2);
//     rr.mp.writeInt(success ? 1 : 0);
//     rr.mp.writeInt(cause);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + success + " " + cause);

//     RILREQUEST::send(rr);
// }

// public
// void acknowledgeLastIncomingCdmaSms(boolean success, int cause, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE, result);

//     rr.mp.writeInt(success ? 0 : 1); //RIL_CDMA_SMS_ErrorClass
//     // cause code according to X.S004-550E
//     rr.mp.writeInt(cause);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + success + " " + cause);

//     RILREQUEST::send(rr);
// }

// public
// void acknowledgeIncomingGsmSmsWithPdu(boolean success, String ackPdu, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU, result);

//     rr.mp.writeInt(2);
//     rr.mp.writeString(success ? "1" : "0");
//     rr.mp.writeString(ackPdu);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ ' ' + success + " [" + ackPdu + ']');

//     RILREQUEST::send(rr);
// }

// public
// void iccIO(int command, int fileid, String path, int p1, int p2, int p3,
//            String data, String pin2, RilResponse *result)
// {
//     //Note: This RIL request has not been renamed to ICC,
//     //       but this request is also valid for SIM and RUIM
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SIM_IO, result);

//     rr.mp.writeInt(command);
//     rr.mp.writeInt(fileid);
//     rr.mp.writeString(path);
//     rr.mp.writeInt(p1);
//     rr.mp.writeInt(p2);
//     rr.mp.writeInt(p3);
//     rr.mp.writeString(data);
//     rr.mp.writeString(pin2);

//     if (RIL_VERBOSE)
//         riljLogLOGV << ialString() + "> iccIO: " << rr->requestToString() << ENDL+ " 0x" + Integer.toHexString(command) + " 0x" + Integer.toHexString(fileid) + " " + " path: " + path + "," + p1 + "," + p2 + "," + p3);

//     RILREQUEST::send(rr);
// }

// public
// void getCLIR(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_CLIR, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void setCLIR(int clirMode, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_CLIR, result);

//     // count ints
//     rr.mp.writeInt(1);

//     rr.mp.writeInt(clirMode);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + clirMode);

//     RILREQUEST::send(rr);
// }

// public
// void queryCallWaiting(int serviceClass, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_QUERY_CALL_WAITING, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(serviceClass);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + serviceClass);

//     RILREQUEST::send(rr);
// }

// public
// void setCallWaiting(boolean enable, int serviceClass, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_CALL_WAITING, response);

//     rr.mp.writeInt(2);
//     rr.mp.writeInt(enable ? 1 : 0);
//     rr.mp.writeInt(serviceClass);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + enable + ", " + serviceClass);

//     RILREQUEST::send(rr);
// }

// public
// void setNetworkSelectionModeAutomatic(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC,
//                                         response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void setNetworkSelectionModeManual(String operatorNumeric, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL,
//                                         response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + operatorNumeric);

//     rr.mp.writeString(operatorNumeric);

//     RILREQUEST::send(rr);
// }

// public
// void getNetworkSelectionMode(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE,
//                                         response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getAvailableNetworks(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_QUERY_AVAILABLE_NETWORKS,
//                                         response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void setCallForward(int action, int cfReason, int serviceClass,
//                     String number, int timeSeconds, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_CALL_FORWARD, response);

//     rr.mp.writeInt(action);
//     rr.mp.writeInt(cfReason);
//     rr.mp.writeInt(serviceClass);
//     rr.mp.writeInt(PhoneNumberUtils.toaFromString(number));
//     rr.mp.writeString(number);
//     rr.mp.writeInt(timeSeconds);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + action + " " + cfReason + " " + serviceClass + timeSeconds);

//     RILREQUEST::send(rr);
// }

// public
// void queryCallForwardStatus(int cfReason, int serviceClass,
//                             String number, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_QUERY_CALL_FORWARD_STATUS, response);

//     rr.mp.writeInt(2); // 2 is for query action, not in used anyway
//     rr.mp.writeInt(cfReason);
//     rr.mp.writeInt(serviceClass);
//     rr.mp.writeInt(PhoneNumberUtils.toaFromString(number));
//     rr.mp.writeString(number);
//     rr.mp.writeInt(0);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + cfReason + " " + serviceClass);

//     RILREQUEST::send(rr);
// }

// public
// void queryCLIP(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_QUERY_CLIP, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getBasebandVersion(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_BASEBAND_VERSION, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// void queryFacilityLock(String facility, String password, int serviceClass,
//                        RilResponse *response)
// {
//     queryFacilityLockForApp(facility, password, serviceClass, null, response);
// }

// void queryFacilityLockForApp(String facility, String password, int serviceClass, String appId,
//                              RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_QUERY_FACILITY_LOCK, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     // count strings
//     rr.mp.writeInt(4);

//     rr.mp.writeString(facility);
//     rr.mp.writeString(password);

//     rr.mp.writeString(Integer.toString(serviceClass));
//     rr.mp.writeString(appId);

//     RILREQUEST::send(rr);
// }

// void setFacilityLock(String facility, boolean lockState, String password,
//                      int serviceClass, RilResponse *response)
// {
//     setFacilityLockForApp(facility, lockState, password, serviceClass, null, response);
// }

// void setFacilityLockForApp(String facility, boolean lockState, String password,
//                            int serviceClass, String appId, RilResponse *response)
// {
//     String lockString;
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_FACILITY_LOCK, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     // count strings
//     rr.mp.writeInt(5);

//     rr.mp.writeString(facility);
//     lockString = (lockState) ? "1" : "0";
//     rr.mp.writeString(lockString);
//     rr.mp.writeString(password);
//     rr.mp.writeString(Integer.toString(serviceClass));
//     rr.mp.writeString(appId);

//     RILREQUEST::send(rr);
// }

// public
// void sendUSSD(String ussdString, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SEND_USSD, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + ussdString);

//     rr.mp.writeString(ussdString);

//     RILREQUEST::send(rr);
// }

// // inherited javadoc suffices
// public
// void cancelPendingUssd(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CANCEL_USSD, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void resetRadio(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_RESET_RADIO, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void invokeOemRilRequestRaw(byte[] data, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_OEM_HOOK_RAW, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ "[" + IccUtils.bytesToHexString(data) + "]");

//     rr.mp.writeByteArray(data);

//     RILREQUEST::send(rr);
// }

// public
// void invokeOemRilRequestStrings(String[] strings, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_OEM_HOOK_STRINGS, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeStringArray(strings);

//     RILREQUEST::send(rr);
// }

// /**
//      * Assign a specified band for RF configuration.
//      *
//      * @param bandMode one of BM_*_BAND
//      * @param response is callback message
//      */
// public
// void setBandMode(int bandMode, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_BAND_MODE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(bandMode);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " " + bandMode);

//     RILREQUEST::send(rr);
// }

// /**
//      * Query the list of band mode supported by RF.
//      *
//      * @param response is callback message
//      *        ((AsyncResult)response.obj).result  is an int[] with every
//      *        element representing one avialable BM_*_BAND
//      */
// public
// void queryAvailableBandMode(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE,
//                                         response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void sendTerminalResponse(String contents, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeString(contents);
//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void sendEnvelope(String contents, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     rr.mp.writeString(contents);
//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void sendEnvelopeWithStatus(String contents, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ '[' + contents + ']');

//     rr.mp.writeString(contents);
//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void handleCallSetupRequestFromSim(
//     boolean accept, RilResponse *response)
// {

//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM,
//         response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     int[] param = new int[1];
//     param[0] = accept ? 1 : 0;
//     rr.mp.writeIntArray(param);
//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// void setCurrentPreferredNetworkType()
// {
//     if (RIL_VERBOSE)
//         riljLog("setCurrentPreferredNetworkType: " + mSetPreferredNetworkType);
//     setPreferredNetworkType(mSetPreferredNetworkType, null);
// }
// private
// int mSetPreferredNetworkType;

// /**
//      * {@inheritDoc}
//      */
// public
// void setPreferredNetworkType(int networkType, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(networkType);

//     mSetPreferredNetworkType = networkType;
//     mPreferredNetworkType = networkType;

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + networkType);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void getPreferredNetworkType(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void getNeighboringCids(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_GET_NEIGHBORING_CELL_IDS, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setLocationUpdates(boolean enable, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_LOCATION_UPDATES, response);
//     rr.mp.writeInt(1);
//     rr.mp.writeInt(enable ? 1 : 0);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ ": " + enable);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void getSmscAddress(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GET_SMSC_ADDRESS, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setSmscAddress(String address, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SET_SMSC_ADDRESS, result);

//     rr.mp.writeString(address);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + address);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void reportSmsMemoryStatus(boolean available, RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_REPORT_SMS_MEMORY_STATUS, result);
//     rr.mp.writeInt(1);
//     rr.mp.writeInt(available ? 1 : 0);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ ": " + available);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void reportStkServiceIsRunning(RilResponse *result)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING, result);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void getGsmBroadcastConfig(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GSM_GET_BROADCAST_CONFIG, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setGsmBroadcastConfig(SmsBroadcastConfigInfo[] config, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GSM_SET_BROADCAST_CONFIG, response);

//     int numOfConfig = config.length;
//     rr.mp.writeInt(numOfConfig);

//     for (int i = 0; i < numOfConfig; i++)
//     {
//         rr.mp.writeInt(config[i].getFromServiceId());
//         rr.mp.writeInt(config[i].getToServiceId());
//         rr.mp.writeInt(config[i].getFromCodeScheme());
//         rr.mp.writeInt(config[i].getToCodeScheme());
//         rr.mp.writeInt(config[i].isSelected() ? 1 : 0);
//     }

//     if (RIL_VERBOSE)
//     {
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " with " + numOfConfig + " configs : ");
//         for (int i = 0; i < numOfConfig; i++)
//         {
//             riljLog(config[i].toString());
//         }
//     }

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setGsmBroadcastActivation(boolean activate, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_GSM_BROADCAST_ACTIVATION, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(activate ? 0 : 1);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// //***** Private Methods

// private
// void sendScreenState(boolean on)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_SCREEN_STATE, null);
//     rr.mp.writeInt(1);
//     rr.mp.writeInt(on ? 1 : 0);

//     if (RIL_VERBOSE)
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

// /**
//      * Holds a PARTIAL_WAKE_LOCK whenever
//      * a) There is outstanding RIL request sent to RIL deamon and no replied
//      * b) There is a request pending to be sent out.
//      *
//      * There is a WAKE_LOCK_TIMEOUT to release the lock, though it shouldn't
//      * happen often.
//      */

// private
// void acquireWakeLock()
// {
//     synchronized(mWakeLock)
//     {
//         mWakeLock.acquire();
//         mRequestMessagesPending++;

//         mSender.removeMessages(EVENT_WAKE_LOCK_TIMEOUT);
//         RilResponse *msg = mSender.obtainMessage(EVENT_WAKE_LOCK_TIMEOUT);
//         mSender.sendMessageDelayed(msg, mWakeLockTimeout);
//     }
// }

// private
// void releaseWakeLockIfDone()
// {
//     synchronized(mWakeLock)
//     {
//         if (mWakeLock.isHeld() &&
//             (mRequestMessagesPending == 0) &&
//             (mRequestMessagesWaiting == 0))
//         {
//             mSender.removeMessages(EVENT_WAKE_LOCK_TIMEOUT);
//             mWakeLock.release();
//         }
//     }
// }

// private
// void send(RilRequest *rr)
// {
//     RilResponse *msg;

//     if (mSocket == null)
//     {
//         rr.onError(RADIO_NOT_AVAILABLE, null);
//         rr.release();
//         return;
//     }

//     msg = mSender.obtainMessage(EVENT_SEND, rr);

//     acquireWakeLock();

//     msg.sendToTarget();
// }

// private
// void processResponse(Parcel &p)
// {
//     int type;

//     type = p.readInt();

//     if (type == RESPONSE_UNSOLICITED)
//     {
//         processUnsolicited(p);
//     }
//     else if (type == RESPONSE_SOLICITED)
//     {
//         processSolicited(p);
//     }

//     releaseWakeLockIfDone();
// }

// /**
//      * Release each request in mReqeustsList then clear the list
//      * @param error is the RIL_Errno sent back
//      * @param loggable true means to print all requests in mRequestslist
//      */
// private
// void clearRequestsList(int error, boolean loggable)
// {
//     RilRequest *rr;
//     synchronized(mRequestsList)
//     {
//         int count = mRequestsList.size();
//         if (RIL_VERBOSE && loggable)
//         {
//             Log.d(LOG_TAG, "WAKE_LOCK_TIMEOUT " +
//                                " mReqPending=" + mRequestMessagesPending +
//                                " mRequestList=" + count);
//         }

//         for (int i = 0; i < count; i++)
//         {
//             rr = mRequestsList.get(i);
//             if (RIL_VERBOSE && loggable)
//             {
//                 Log.d(LOG_TAG, i + ": [" + rr.mSerial + "] " +
//                                    requestToString(rr.mRequest));
//             }
//             rr.onError(error, null);
//             rr.release();
//         }
//         mRequestsList.clear();
//         mRequestMessagesWaiting = 0;
//     }
// }

// private
// RilRequest findAndRemoveRequestFromList(int serial)
// {
//     synchronized(mRequestsList)
//     {
//         for (int i = 0, s = mRequestsList.size(); i < s; i++)
//         {
//             RilRequest *rr = mRequestsList.get(i);

//             if (rr.mSerial == serial)
//             {
//                 mRequestsList.remove(i);
//                 if (mRequestMessagesWaiting > 0)
//                     mRequestMessagesWaiting--;
//                 return rr;
//             }
//         }
//     }

//     return null;
// }

// private
// void processSolicited(Parcel &p)
// {
//     int serial, error;
//     boolean found = false;

//     serial = p.readInt();
//     error = p.readInt();

//     RilRequest *rr;

//     rr = findAndRemoveRequestFromList(serial);

//     if (rr == null)
//     {
//         Log.w(LOG_TAG, "Unexpected solicited response! sn: " + serial + " error: " + error);
//         return;
//     }

//     Object ret = null;

//     if (error == 0 || p.dataAvail() > 0)
//     {
//         // either command succeeds or command fails but with data payload
//         try
//         {
//             switch (rr.mRequest)
//             {
//             /*
//  cat libs/telephony/ril_commands.h \
//  | egrep "^ *{RIL_" \
//  | sed -re 's/\{([^,]+),[^,]+,([^}]+).+/case \1: ret = \2(p); break;/'
//              */
//             case RIL_REQUEST_GET_SIM_STATUS:
//                 ret = responseIccCardStatus(p);
//                 break;
//             case RIL_REQUEST_ENTER_SIM_PIN:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_ENTER_SIM_PUK:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_ENTER_SIM_PIN2:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_ENTER_SIM_PUK2:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_CHANGE_SIM_PIN:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_CHANGE_SIM_PIN2:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_GET_CURRENT_CALLS:
//                 ret = responseCallList(p);
//                 break;
//             case RIL_REQUEST_DIAL:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_GET_IMSI:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_HANGUP:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CONFERENCE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_UDUB:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_LAST_CALL_FAIL_CAUSE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_SIGNAL_STRENGTH:
//                 ret = responseSignalStrength(p);
//                 break;
//             case RIL_REQUEST_VOICE_REGISTRATION_STATE:
//                 ret = responseStrings(p);
//                 break;
//             case RIL_REQUEST_DATA_REGISTRATION_STATE:
//                 ret = responseStrings(p);
//                 break;
//             case RIL_REQUEST_OPERATOR:
//                 ret = responseStrings(p);
//                 break;
//             case RIL_REQUEST_RADIO_POWER:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_DTMF:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SEND_SMS:
//                 ret = responseSMS(p);
//                 break;
//             case RIL_REQUEST_SEND_SMS_EXPECT_MORE:
//                 ret = responseSMS(p);
//                 break;
//             case RIL_REQUEST_SETUP_DATA_CALL:
//                 ret = responseSetupDataCall(p);
//                 break;
//             case RIL_REQUEST_SIM_IO:
//                 ret = responseICC_IO(p);
//                 break;
//             case RIL_REQUEST_SEND_USSD:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CANCEL_USSD:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_GET_CLIR:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_SET_CLIR:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS:
//                 ret = responseCallForward(p);
//                 break;
//             case RIL_REQUEST_SET_CALL_FORWARD:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_QUERY_CALL_WAITING:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_SET_CALL_WAITING:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SMS_ACKNOWLEDGE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_GET_IMEI:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_GET_IMEISV:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_ANSWER:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_DEACTIVATE_DATA_CALL:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_QUERY_FACILITY_LOCK:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_SET_FACILITY_LOCK:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_CHANGE_BARRING_PASSWORD:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_QUERY_AVAILABLE_NETWORKS:
//                 ret = responseOperatorInfos(p);
//                 break;
//             case RIL_REQUEST_DTMF_START:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_DTMF_STOP:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_BASEBAND_VERSION:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_SEPARATE_CONNECTION:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SET_MUTE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_GET_MUTE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_QUERY_CLIP:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_DATA_CALL_LIST:
//                 ret = responseDataCallList(p);
//                 break;
//             case RIL_REQUEST_RESET_RADIO:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_OEM_HOOK_RAW:
//                 ret = responseRaw(p);
//                 break;
//             case RIL_REQUEST_OEM_HOOK_STRINGS:
//                 ret = responseStrings(p);
//                 break;
//             case RIL_REQUEST_SCREEN_STATE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_WRITE_SMS_TO_SIM:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_DELETE_SMS_ON_SIM:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SET_BAND_MODE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_STK_GET_PROFILE:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_STK_SET_PROFILE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_EXPLICIT_CALL_TRANSFER:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE:
//                 ret = responseGetPreferredNetworkType(p);
//                 break;
//             case RIL_REQUEST_GET_NEIGHBORING_CELL_IDS:
//                 ret = responseCellList(p);
//                 break;
//             case RIL_REQUEST_SET_LOCATION_UPDATES:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_SET_TTY_MODE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_QUERY_TTY_MODE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_CDMA_FLASH:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_BURST_DTMF:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_SEND_SMS:
//                 ret = responseSMS(p);
//                 break;
//             case RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_GSM_GET_BROADCAST_CONFIG:
//                 ret = responseGmsBroadcastConfig(p);
//                 break;
//             case RIL_REQUEST_GSM_SET_BROADCAST_CONFIG:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_GSM_BROADCAST_ACTIVATION:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG:
//                 ret = responseCdmaBroadcastConfig(p);
//                 break;
//             case RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_BROADCAST_ACTIVATION:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_SUBSCRIPTION:
//                 ret = responseStrings(p);
//                 break;
//             case RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_DEVICE_IDENTITY:
//                 ret = responseStrings(p);
//                 break;
//             case RIL_REQUEST_GET_SMSC_ADDRESS:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_SET_SMSC_ADDRESS:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_REPORT_SMS_MEMORY_STATUS:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE:
//                 ret = responseInts(p);
//                 break;
//             case RIL_REQUEST_ISIM_AUTHENTICATION:
//                 ret = responseString(p);
//                 break;
//             case RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU:
//                 ret = responseVoid(p);
//                 break;
//             case RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS:
//                 ret = responseICC_IO(p);
//                 break;
//             default:
//                 throw new RuntimeException("Unrecognized solicited response: " + rr.mRequest);
//                 //break;
//             }
//         }
//         catch (Throwable tr)
//         {
//             // Exceptions here usually mean invalid RIL responses

//             Log.w(LLOGV << rr->serialString() + "< " << rr->requestToString() << ENDL+ " exception, possible invalid RIL response", tr);

//             if (rr.mResult != null)
//             {
//                 AsyncResult.forMessage(rr.mResult, null, tr);
//                 rr.mResult.sendToTarget();
//             }
//             rr.release();
//             return;
//         }
//     }

//     if (error != 0)
//     {
//         rr.onError(error, ret);
//         rr.release();
//         return;
//     }

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "< " << rr->requestToString() << ENDL+ " " + retToString(rr.mRequest, ret));

//     if (rr.mResult != null)
//     {
//         AsyncResult.forMessage(rr.mResult, ret, null);
//         rr.mResult.sendToTarget();
//     }

//     rr.release();
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

// private
// void processUnsolicited(Parcel &p)
// {
//     int response;
//     Object ret;

//     response = p.readInt();

//     try
//     {
//         switch (response)
//         {
//             /*
//  cat libs/telephony/ril_unsol_commands.h \
//  | egrep "^ *{RIL_" \
//  | sed -re 's/\{([^,]+),[^,]+,([^}]+).+/case \1: \2(rr, p); break;/'
// */

//         case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_RESPONSE_NEW_SMS:
//             ret = responseString(p);
//             break;
//         case RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT:
//             ret = responseString(p);
//             break;
//         case RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOL_ON_USSD:
//             ret = responseStrings(p);
//             break;
//         case RIL_UNSOL_NITZ_TIME_RECEIVED:
//             ret = responseString(p);
//             break;
//         case RIL_UNSOL_SIGNAL_STRENGTH:
//             ret = responseSignalStrength(p);
//             break;
//         case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
//             ret = responseDataCallList(p);
//             break;
//         case RIL_UNSOL_SUPP_SVC_NOTIFICATION:
//             ret = responseSuppServiceNotification(p);
//             break;
//         case RIL_UNSOL_STK_SESSION_END:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_STK_PROACTIVE_COMMAND:
//             ret = responseString(p);
//             break;
//         case RIL_UNSOL_STK_EVENT_NOTIFY:
//             ret = responseString(p);
//             break;
//         case RIL_UNSOL_STK_CALL_SETUP:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOL_SIM_SMS_STORAGE_FULL:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_SIM_REFRESH:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOL_CALL_RING:
//             ret = responseCallRing(p);
//             break;
//         case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
//             ret = responseCdmaSms(p);
//             break;
//         case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
//             ret = responseRaw(p);
//             break;
//         case RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_CDMA_CALL_WAITING:
//             ret = responseCdmaCallWaiting(p);
//             break;
//         case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOL_CDMA_INFO_REC:
//             ret = responseCdmaInformationRecord(p);
//             break;
//         case RIL_UNSOL_OEM_HOOK_RAW:
//             ret = responseRaw(p);
//             break;
//         case RIL_UNSOL_RINGBACK_TONE:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOL_RESEND_INCALL_MUTE:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOl_CDMA_PRL_CHANGED:
//             ret = responseInts(p);
//             break;
//         case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
//             ret = responseVoid(p);
//             break;
//         case RIL_UNSOL_RIL_CONNECTED:
//             ret = responseInts(p);
//             break;

//         default:
//             throw new RuntimeException("Unrecognized unsol response: " + response);
//             //break; (implied)
//         }
//     }
//     catch (Throwable tr)
//     {
//         Log.e(LOG_TAG, "Exception processing unsol response: " + response +
//                            "Exception:" + tr.toString());
//         return;
//     }

//     switch (response)
//     {
//     case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
//         /* has bonus radio state int */
//         RadioState newState = getRadioStateFromInt(p.readInt());
//         if (RIL_VERBOSE)
//             unsljLogMore(response, newState.toString());

//         switchToRadioState(newState);
//         break;
//     case RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         mCallStateRegistrants
//             .notifyRegistrants(new AsyncResult(null, null, null));
//         break;
//     case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         mVoiceNetworkStateRegistrants
//             .notifyRegistrants(new AsyncResult(null, null, null));
//         break;
//     case RIL_UNSOL_RESPONSE_NEW_SMS:
//     {
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         // FIXME this should move up a layer
//         String a[] = new String[2];

//         a[1] = (String)ret;

//         SmsMessage sms;

//         sms = SmsMessage.newFromCMT(a);
//         if (mGsmSmsRegistrant != null)
//         {
//             mGsmSmsRegistrant
//                 .notifyRegistrant(new AsyncResult(null, sms, null));
//         }
//         break;
//     }
//     case RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mSmsStatusRegistrant != null)
//         {
//             mSmsStatusRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;
//     case RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         int[] smsIndex = (int[])ret;

//         if (smsIndex.length == 1)
//         {
//             if (mSmsOnSimRegistrant != null)
//             {
//                 mSmsOnSimRegistrant.notifyRegistrant(new AsyncResult(null, smsIndex, null));
//             }
//         }
//         else
//         {
//             if (RIL_VERBOSE)
//                 riljLog(" NEW_SMS_ON_SIM ERROR with wrong length " + smsIndex.length);
//         }
//         break;
//     case RIL_UNSOL_ON_USSD:
//         String[] resp = (String[])ret;

//         if (resp.length < 2)
//         {
//             resp = new String[2];
//             resp[0] = ((String[])ret)[0];
//             resp[1] = null;
//         }
//         if (RIL_VERBOSE)
//             unsljLogMore(response, resp[0]);
//         if (mUSSDRegistrant != null)
//         {
//             mUSSDRegistrant.notifyRegistrant(
//                 new AsyncResult(null, resp, null));
//         }
//         break;
//     case RIL_UNSOL_NITZ_TIME_RECEIVED:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         // has bonus long containing milliseconds since boot that the NITZ
//         // time was received
//         long nitzReceiveTime = p.readLong();

//         Object[] result = new Object[2];

//         result[0] = ret;
//         result[1] = Long.valueOf(nitzReceiveTime);

//         if (mNITZTimeRegistrant != null)
//         {

//             mNITZTimeRegistrant
//                 .notifyRegistrant(new AsyncResult(null, result, null));
//         }
//         else
//         {
//             // in case NITZ time registrant isnt registered yet
//             mLastNITZTimeInfo = result;
//         }
//         break;

//     case RIL_UNSOL_SIGNAL_STRENGTH:
//         // Note this is set to "verbose" because it happens
//         // frequently
//         if (RILJ_LOGV)
//             unsljLogvRet(response, ret);

//         if (mSignalStrengthRegistrant != null)
//         {
//             mSignalStrengthRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;
//     case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         mDataNetworkStateRegistrants.notifyRegistrants(new AsyncResult(null, ret, null));
//         break;

//     case RIL_UNSOL_SUPP_SVC_NOTIFICATION:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mSsnRegistrant != null)
//         {
//             mSsnRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_STK_SESSION_END:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         if (mCatSessionEndRegistrant != null)
//         {
//             mCatSessionEndRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_STK_PROACTIVE_COMMAND:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mCatProCmdRegistrant != null)
//         {
//             mCatProCmdRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_STK_EVENT_NOTIFY:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mCatEventRegistrant != null)
//         {
//             mCatEventRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_STK_CALL_SETUP:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mCatCallSetUpRegistrant != null)
//         {
//             mCatCallSetUpRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_SIM_SMS_STORAGE_FULL:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         if (mIccSmsFullRegistrant != null)
//         {
//             mIccSmsFullRegistrant.notifyRegistrant();
//         }
//         break;

//     case RIL_UNSOL_SIM_REFRESH:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mIccRefreshRegistrants != null)
//         {
//             mIccRefreshRegistrants.notifyRegistrants(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_CALL_RING:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mRingRegistrant != null)
//         {
//             mRingRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
//         if (RIL_VERBOSE)
//             unsljLogvRet(response, ret);
//         if (mRestrictedStateRegistrant != null)
//         {
//             mRestrictedStateRegistrant.notifyRegistrant(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         if (mIccStatusChangedRegistrants != null)
//         {
//             mIccStatusChangedRegistrants.notifyRegistrants();
//         }
//         break;

//     case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         SmsMessage sms = (SmsMessage)ret;

//         if (mCdmaSmsRegistrant != null)
//         {
//             mCdmaSmsRegistrant
//                 .notifyRegistrant(new AsyncResult(null, sms, null));
//         }
//         break;

//     case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         if (mGsmBroadcastSmsRegistrant != null)
//         {
//             mGsmBroadcastSmsRegistrant
//                 .notifyRegistrant(new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         if (mIccSmsFullRegistrant != null)
//         {
//             mIccSmsFullRegistrant.notifyRegistrant();
//         }
//         break;

//     case RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE:
//         if (RIL_VERBOSE)
//             unsljLog(response);

//         if (mEmergencyCallbackModeRegistrant != null)
//         {
//             mEmergencyCallbackModeRegistrant.notifyRegistrant();
//         }
//         break;

//     case RIL_UNSOL_CDMA_CALL_WAITING:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mCallWaitingInfoRegistrants != null)
//         {
//             mCallWaitingInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mOtaProvisionRegistrants != null)
//         {
//             mOtaProvisionRegistrants.notifyRegistrants(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_CDMA_INFO_REC:
//         ArrayList<CdmaInformationRecords> listInfoRecs;

//         try
//         {
//             listInfoRecs = (ArrayList<CdmaInformationRecords>)ret;
//         }
//         catch (ClassCastException e)
//         {
//             Log.e(LOG_TAG, "Unexpected exception casting to listInfoRecs", e);
//             break;
//         }

//         for (CdmaInformationRecords rec : listInfoRecs)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, rec);
//             notifyRegistrantsCdmaInfoRec(rec);
//         }
//         break;

//     case RIL_UNSOL_OEM_HOOK_RAW:
//         if (RIL_VERBOSE)
//             unsljLogvRet(response, IccUtils.bytesToHexString((byte[])ret));
//         if (mUnsolOemHookRawRegistrant != null)
//         {
//             mUnsolOemHookRawRegistrant.notifyRegistrant(new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_RINGBACK_TONE:
//         if (RIL_VERBOSE)
//             unsljLogvRet(response, ret);
//         if (mRingbackToneRegistrants != null)
//         {
//             boolean playtone = (((int[])ret)[0] == 1);
//             mRingbackToneRegistrants.notifyRegistrants(
//                 new AsyncResult(null, playtone, null));
//         }
//         break;

//     case RIL_UNSOL_RESEND_INCALL_MUTE:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mResendIncallMuteRegistrants != null)
//         {
//             mResendIncallMuteRegistrants.notifyRegistrants(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mCdmaSubscriptionChangedRegistrants != null)
//         {
//             mCdmaSubscriptionChangedRegistrants.notifyRegistrants(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOl_CDMA_PRL_CHANGED:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mCdmaPrlChangedRegistrants != null)
//         {
//             mCdmaPrlChangedRegistrants.notifyRegistrants(
//                 new AsyncResult(null, ret, null));
//         }
//         break;

//     case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         if (mExitEmergencyCallbackModeRegistrants != null)
//         {
//             mExitEmergencyCallbackModeRegistrants.notifyRegistrants(
//                 new AsyncResult(null, null, null));
//         }
//         break;

//     case RIL_UNSOL_RIL_CONNECTED:
//     {
//         if (RIL_VERBOSE)
//             unsljLogRet(response, ret);

//         // Initial conditions
//         setRadioPower(false, null);
//         setPreferredNetworkType(mPreferredNetworkType, null);
//         setCdmaSubscriptionSource(mCdmaSubscription, null);
//         notifyRegistrantsRilConnectionChanged(((int[])ret)[0]);
//         break;
//     }
//     }
// }

// /**
//      * Notifiy all registrants that the ril has connected or disconnected.
//      *
//      * @param rilVer is the version of the ril or -1 if disconnected.
//      */
// private
// void notifyRegistrantsRilConnectionChanged(int rilVer)
// {
//     mRilVersion = rilVer;
//     if (mRilConnectedRegistrants != null)
//     {
//         mRilConnectedRegistrants.notifyRegistrants(
//             new AsyncResult(null, new Integer(rilVer), null));
//     }
// }

// private
// Object
// responseInts(Parcel &p)
// {
//     int numInts;
//     int response[];

//     numInts = p.readInt();

//     response = new int[numInts];

//     for (int i = 0; i < numInts; i++)
//     {
//         response[i] = p.readInt();
//     }

//     return response;
// }

// private
// Object
// responseVoid(Parcel &p)
// {
//     return null;
// }

// private
// Object
// responseCallForward(Parcel &p)
// {
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

//     return infos;
// }

// private
// Object
// responseSuppServiceNotification(Parcel &p)
// {
//     SuppServiceNotification notification = new SuppServiceNotification();

//     notification.notificationType = p.readInt();
//     notification.code = p.readInt();
//     notification.index = p.readInt();
//     notification.type = p.readInt();
//     notification.number = p.readString();

//     return notification;
// }

// private
// Object
// responseCdmaSms(Parcel &p)
// {
//     SmsMessage sms;
//     sms = SmsMessage.newFromParcel(p);

//     return sms;
// }

// private
// Object
// responseString(Parcel &p)
// {
//     String response;

//     response = p.readString();

//     return response;
// }

// private
// Object
// responseStrings(Parcel &p)
// {
//     int num;
//     String response[];

//     response = p.readStringArray();

//     if (false)
//     {
//         num = p.readInt();

//         response = new String[num];
//         for (int i = 0; i < num; i++)
//         {
//             response[i] = p.readString();
//         }
//     }

//     return response;
// }

// private
// Object
// responseRaw(Parcel &p)
// {
//     int num;
//     byte response[];

//     response = p.createByteArray();

//     return response;
// }

// private
// Object
// responseSMS(Parcel &p)
// {
//     int messageRef, errorCode;
//     String ackPDU;

//     messageRef = p.readInt();
//     ackPDU = p.readString();
//     errorCode = p.readInt();

//     SmsResponse response = new SmsResponse(messageRef, ackPDU, errorCode);

//     return response;
// }

// private
// Object
// responseICC_IO(Parcel &p)
// {
//     int sw1, sw2;
//     byte data[] = null;
//     RilResponse *ret;

//     sw1 = p.readInt();
//     sw2 = p.readInt();

//     String s = p.readString();

//     if (RILJ_LOGV)
//         riljLog("< iccIO: " + " 0x" + Integer.toHexString(sw1) + " 0x" + Integer.toHexString(sw2) + " " + s);

//     return new IccIoResult(sw1, sw2, s);
// }

// private
// Object
// responseIccCardStatus(Parcel &p)
// {
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
//     return status;
// }

// private
// Object
// responseCallList(Parcel &p)
// {
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

//     return response;
// }

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

// private
// Object
// responseDataCallList(Parcel &p)
// {
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
// }

// private
// Object
// responseSetupDataCall(Parcel &p)
// {
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
//             if (RIL_VERBOSE)
//                 riljLog("responseSetupDataCall got dnses=" + dnses);
//             if (!TextUtils.isEmpty(dnses))
//             {
//                 dataCall.dnses = dnses.split(" ");
//             }
//         }
//         if (num >= 5)
//         {
//             String gateways = p.readString();
//             if (RIL_VERBOSE)
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

//     return dataCall;
// }

// private
// Object
// responseOperatorInfos(Parcel &p)
// {
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

//     return ret;
// }

// private
// Object
// responseCellList(Parcel &p)
// {
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
//     return response;
// }

// private
// Object responseGetPreferredNetworkType(Parcel &p)
// {
//     int[] response = (int[])responseInts(p);

//     if (response.length >= 1)
//     {
//         // Since this is the response for getPreferredNetworkType
//         // we'll assume that it should be the value we want the
//         // vendor ril to take if we reestablish a connection to it.
//         mPreferredNetworkType = response[0];
//     }
//     return response;
// }

// private
// Object responseGmsBroadcastConfig(Parcel &p)
// {
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
//     return response;
// }

// private
// Object
// responseCdmaBroadcastConfig(Parcel &p)
// {
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

//     return response;
// }

void responseSignalStrength(Parcel &p)
{
    int numInts = 12;
    std::vector<int> vec;

    /* TODO: Add SignalStrength class to match RIL_SignalStrength */
    for (int i = 0; i < numInts; i++)
    {
        vec.emplace_back(p.readInt());
        LOGI << vec[i] << ENDL;
    }
}

// private
// ArrayList<CdmaInformationRecords>
// responseCdmaInformationRecord(Parcel &p)
// {
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

//     return response;
// }

// private
// Object
// responseCdmaCallWaiting(Parcel &p)
// {
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

//     return notification;
// }

// private
// Object
// responseCallRing(Parcel &p)
// {
//     char response[] = new char[4];

//     response[0] = (char)p.readInt(); // isPresent
//     response[1] = (char)p.readInt(); // signalType
//     response[2] = (char)p.readInt(); // alertPitch
//     response[3] = (char)p.readInt(); // signal

//     return response;
// }

// private
// void notifyRegistrantsCdmaInfoRec(CdmaInformationRecords infoRec)
// {
//     int response = RIL_UNSOL_CDMA_INFO_REC;
//     if (infoRec.record instanceof CdmaInformationRecords.CdmaDisplayInfoRec)
//     {
//         if (mDisplayInfoRegistrants != null)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, infoRec.record);
//             mDisplayInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaSignalInfoRec)
//     {
//         if (mSignalInfoRegistrants != null)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, infoRec.record);
//             mSignalInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaNumberInfoRec)
//     {
//         if (mNumberInfoRegistrants != null)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, infoRec.record);
//             mNumberInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaRedirectingNumberInfoRec)
//     {
//         if (mRedirNumInfoRegistrants != null)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, infoRec.record);
//             mRedirNumInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaLineControlInfoRec)
//     {
//         if (mLineControlInfoRegistrants != null)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, infoRec.record);
//             mLineControlInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaT53ClirInfoRec)
//     {
//         if (mT53ClirInfoRegistrants != null)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, infoRec.record);
//             mT53ClirInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
//     else if (infoRec.record instanceof CdmaInformationRecords.CdmaT53AudioControlInfoRec)
//     {
//         if (mT53AudCntrlInfoRegistrants != null)
//         {
//             if (RIL_VERBOSE)
//                 unsljLogRet(response, infoRec.record);
//             mT53AudCntrlInfoRegistrants.notifyRegistrants(
//                 new AsyncResult(null, infoRec.record, null));
//         }
//     }
// }

// static String
// requestToString(int request)
// {
//     /*
//  cat libs/telephony/ril_commands.h \
//  | egrep "^ *{RIL_" \
//  | sed -re 's/\{RIL_([^,]+),[^,]+,([^}]+).+/case RIL_\1: return "\1";/'
// */
//     switch (request)
//     {
//     case RIL_REQUEST_GET_SIM_STATUS:
//         return "GET_SIM_STATUS";
//     case RIL_REQUEST_ENTER_SIM_PIN:
//         return "ENTER_SIM_PIN";
//     case RIL_REQUEST_ENTER_SIM_PUK:
//         return "ENTER_SIM_PUK";
//     case RIL_REQUEST_ENTER_SIM_PIN2:
//         return "ENTER_SIM_PIN2";
//     case RIL_REQUEST_ENTER_SIM_PUK2:
//         return "ENTER_SIM_PUK2";
//     case RIL_REQUEST_CHANGE_SIM_PIN:
//         return "CHANGE_SIM_PIN";
//     case RIL_REQUEST_CHANGE_SIM_PIN2:
//         return "CHANGE_SIM_PIN2";
//     case RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION:
//         return "ENTER_NETWORK_DEPERSONALIZATION";
//     case RIL_REQUEST_GET_CURRENT_CALLS:
//         return "GET_CURRENT_CALLS";
//     case RIL_REQUEST_DIAL:
//         return "DIAL";
//     case RIL_REQUEST_GET_IMSI:
//         return "GET_IMSI";
//     case RIL_REQUEST_HANGUP:
//         return "HANGUP";
//     case RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND:
//         return "HANGUP_WAITING_OR_BACKGROUND";
//     case RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND:
//         return "HANGUP_FOREGROUND_RESUME_BACKGROUND";
//     case RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE:
//         return "REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE";
//     case RIL_REQUEST_CONFERENCE:
//         return "CONFERENCE";
//     case RIL_REQUEST_UDUB:
//         return "UDUB";
//     case RIL_REQUEST_LAST_CALL_FAIL_CAUSE:
//         return "LAST_CALL_FAIL_CAUSE";
//     case RIL_REQUEST_SIGNAL_STRENGTH:
//         return "SIGNAL_STRENGTH";
//     case RIL_REQUEST_VOICE_REGISTRATION_STATE:
//         return "VOICE_REGISTRATION_STATE";
//     case RIL_REQUEST_DATA_REGISTRATION_STATE:
//         return "DATA_REGISTRATION_STATE";
//     case RIL_REQUEST_OPERATOR:
//         return "OPERATOR";
//     case RIL_REQUEST_RADIO_POWER:
//         return "RADIO_POWER";
//     case RIL_REQUEST_DTMF:
//         return "DTMF";
//     case RIL_REQUEST_SEND_SMS:
//         return "SEND_SMS";
//     case RIL_REQUEST_SEND_SMS_EXPECT_MORE:
//         return "SEND_SMS_EXPECT_MORE";
//     case RIL_REQUEST_SETUP_DATA_CALL:
//         return "SETUP_DATA_CALL";
//     case RIL_REQUEST_SIM_IO:
//         return "SIM_IO";
//     case RIL_REQUEST_SEND_USSD:
//         return "SEND_USSD";
//     case RIL_REQUEST_CANCEL_USSD:
//         return "CANCEL_USSD";
//     case RIL_REQUEST_GET_CLIR:
//         return "GET_CLIR";
//     case RIL_REQUEST_SET_CLIR:
//         return "SET_CLIR";
//     case RIL_REQUEST_QUERY_CALL_FORWARD_STATUS:
//         return "QUERY_CALL_FORWARD_STATUS";
//     case RIL_REQUEST_SET_CALL_FORWARD:
//         return "SET_CALL_FORWARD";
//     case RIL_REQUEST_QUERY_CALL_WAITING:
//         return "QUERY_CALL_WAITING";
//     case RIL_REQUEST_SET_CALL_WAITING:
//         return "SET_CALL_WAITING";
//     case RIL_REQUEST_SMS_ACKNOWLEDGE:
//         return "SMS_ACKNOWLEDGE";
//     case RIL_REQUEST_GET_IMEI:
//         return "GET_IMEI";
//     case RIL_REQUEST_GET_IMEISV:
//         return "GET_IMEISV";
//     case RIL_REQUEST_ANSWER:
//         return "ANSWER";
//     case RIL_REQUEST_DEACTIVATE_DATA_CALL:
//         return "DEACTIVATE_DATA_CALL";
//     case RIL_REQUEST_QUERY_FACILITY_LOCK:
//         return "QUERY_FACILITY_LOCK";
//     case RIL_REQUEST_SET_FACILITY_LOCK:
//         return "SET_FACILITY_LOCK";
//     case RIL_REQUEST_CHANGE_BARRING_PASSWORD:
//         return "CHANGE_BARRING_PASSWORD";
//     case RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE:
//         return "QUERY_NETWORK_SELECTION_MODE";
//     case RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC:
//         return "SET_NETWORK_SELECTION_AUTOMATIC";
//     case RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL:
//         return "SET_NETWORK_SELECTION_MANUAL";
//     case RIL_REQUEST_QUERY_AVAILABLE_NETWORKS:
//         return "QUERY_AVAILABLE_NETWORKS ";
//     case RIL_REQUEST_DTMF_START:
//         return "DTMF_START";
//     case RIL_REQUEST_DTMF_STOP:
//         return "DTMF_STOP";
//     case RIL_REQUEST_BASEBAND_VERSION:
//         return "BASEBAND_VERSION";
//     case RIL_REQUEST_SEPARATE_CONNECTION:
//         return "SEPARATE_CONNECTION";
//     case RIL_REQUEST_SET_MUTE:
//         return "SET_MUTE";
//     case RIL_REQUEST_GET_MUTE:
//         return "GET_MUTE";
//     case RIL_REQUEST_QUERY_CLIP:
//         return "QUERY_CLIP";
//     case RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE:
//         return "LAST_DATA_CALL_FAIL_CAUSE";
//     case RIL_REQUEST_DATA_CALL_LIST:
//         return "DATA_CALL_LIST";
//     case RIL_REQUEST_RESET_RADIO:
//         return "RESET_RADIO";
//     case RIL_REQUEST_OEM_HOOK_RAW:
//         return "OEM_HOOK_RAW";
//     case RIL_REQUEST_OEM_HOOK_STRINGS:
//         return "OEM_HOOK_STRINGS";
//     case RIL_REQUEST_SCREEN_STATE:
//         return "SCREEN_STATE";
//     case RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION:
//         return "SET_SUPP_SVC_NOTIFICATION";
//     case RIL_REQUEST_WRITE_SMS_TO_SIM:
//         return "WRITE_SMS_TO_SIM";
//     case RIL_REQUEST_DELETE_SMS_ON_SIM:
//         return "DELETE_SMS_ON_SIM";
//     case RIL_REQUEST_SET_BAND_MODE:
//         return "SET_BAND_MODE";
//     case RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE:
//         return "QUERY_AVAILABLE_BAND_MODE";
//     case RIL_REQUEST_STK_GET_PROFILE:
//         return "REQUEST_STK_GET_PROFILE";
//     case RIL_REQUEST_STK_SET_PROFILE:
//         return "REQUEST_STK_SET_PROFILE";
//     case RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND:
//         return "REQUEST_STK_SEND_ENVELOPE_COMMAND";
//     case RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE:
//         return "REQUEST_STK_SEND_TERMINAL_RESPONSE";
//     case RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM:
//         return "REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM";
//     case RIL_REQUEST_EXPLICIT_CALL_TRANSFER:
//         return "REQUEST_EXPLICIT_CALL_TRANSFER";
//     case RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE:
//         return "REQUEST_SET_PREFERRED_NETWORK_TYPE";
//     case RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE:
//         return "REQUEST_GET_PREFERRED_NETWORK_TYPE";
//     case RIL_REQUEST_GET_NEIGHBORING_CELL_IDS:
//         return "REQUEST_GET_NEIGHBORING_CELL_IDS";
//     case RIL_REQUEST_SET_LOCATION_UPDATES:
//         return "REQUEST_SET_LOCATION_UPDATES";
//     case RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE:
//         return "RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE";
//     case RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE:
//         return "RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE";
//     case RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE:
//         return "RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE";
//     case RIL_REQUEST_SET_TTY_MODE:
//         return "RIL_REQUEST_SET_TTY_MODE";
//     case RIL_REQUEST_QUERY_TTY_MODE:
//         return "RIL_REQUEST_QUERY_TTY_MODE";
//     case RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE:
//         return "RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE";
//     case RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE:
//         return "RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE";
//     case RIL_REQUEST_CDMA_FLASH:
//         return "RIL_REQUEST_CDMA_FLASH";
//     case RIL_REQUEST_CDMA_BURST_DTMF:
//         return "RIL_REQUEST_CDMA_BURST_DTMF";
//     case RIL_REQUEST_CDMA_SEND_SMS:
//         return "RIL_REQUEST_CDMA_SEND_SMS";
//     case RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE:
//         return "RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE";
//     case RIL_REQUEST_GSM_GET_BROADCAST_CONFIG:
//         return "RIL_REQUEST_GSM_GET_BROADCAST_CONFIG";
//     case RIL_REQUEST_GSM_SET_BROADCAST_CONFIG:
//         return "RIL_REQUEST_GSM_SET_BROADCAST_CONFIG";
//     case RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG:
//         return "RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG";
//     case RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG:
//         return "RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG";
//     case RIL_REQUEST_GSM_BROADCAST_ACTIVATION:
//         return "RIL_REQUEST_GSM_BROADCAST_ACTIVATION";
//     case RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY:
//         return "RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY";
//     case RIL_REQUEST_CDMA_BROADCAST_ACTIVATION:
//         return "RIL_REQUEST_CDMA_BROADCAST_ACTIVATION";
//     case RIL_REQUEST_CDMA_SUBSCRIPTION:
//         return "RIL_REQUEST_CDMA_SUBSCRIPTION";
//     case RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM:
//         return "RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM";
//     case RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM:
//         return "RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM";
//     case RIL_REQUEST_DEVICE_IDENTITY:
//         return "RIL_REQUEST_DEVICE_IDENTITY";
//     case RIL_REQUEST_GET_SMSC_ADDRESS:
//         return "RIL_REQUEST_GET_SMSC_ADDRESS";
//     case RIL_REQUEST_SET_SMSC_ADDRESS:
//         return "RIL_REQUEST_SET_SMSC_ADDRESS";
//     case RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE:
//         return "REQUEST_EXIT_EMERGENCY_CALLBACK_MODE";
//     case RIL_REQUEST_REPORT_SMS_MEMORY_STATUS:
//         return "RIL_REQUEST_REPORT_SMS_MEMORY_STATUS";
//     case RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING:
//         return "RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING";
//     case RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE:
//         return "RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE";
//     case RIL_REQUEST_ISIM_AUTHENTICATION:
//         return "RIL_REQUEST_ISIM_AUTHENTICATION";
//     case RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU:
//         return "RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU";
//     case RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS:
//         return "RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS";
//     default:
//         return "<unknown request>";
//     }
// }

// static String
// responseToString(int request)
// {
//     /*
//  cat libs/telephony/ril_unsol_commands.h \
//  | egrep "^ *{RIL_" \
//  | sed -re 's/\{RIL_([^,]+),[^,]+,([^}]+).+/case RIL_\1: return "\1";/'
// */
//     switch (request)
//     {
//     case RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED:
//         return "UNSOL_RESPONSE_RADIO_STATE_CHANGED";
//     case RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED:
//         return "UNSOL_RESPONSE_CALL_STATE_CHANGED";
//     case RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED:
//         return "UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED";
//     case RIL_UNSOL_RESPONSE_NEW_SMS:
//         return "UNSOL_RESPONSE_NEW_SMS";
//     case RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT:
//         return "UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT";
//     case RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM:
//         return "UNSOL_RESPONSE_NEW_SMS_ON_SIM";
//     case RIL_UNSOL_ON_USSD:
//         return "UNSOL_ON_USSD";
//     case RIL_UNSOL_ON_USSD_REQUEST:
//         return "UNSOL_ON_USSD_REQUEST";
//     case RIL_UNSOL_NITZ_TIME_RECEIVED:
//         return "UNSOL_NITZ_TIME_RECEIVED";
//     case RIL_UNSOL_SIGNAL_STRENGTH:
//         return "UNSOL_SIGNAL_STRENGTH";
//     case RIL_UNSOL_DATA_CALL_LIST_CHANGED:
//         return "UNSOL_DATA_CALL_LIST_CHANGED";
//     case RIL_UNSOL_SUPP_SVC_NOTIFICATION:
//         return "UNSOL_SUPP_SVC_NOTIFICATION";
//     case RIL_UNSOL_STK_SESSION_END:
//         return "UNSOL_STK_SESSION_END";
//     case RIL_UNSOL_STK_PROACTIVE_COMMAND:
//         return "UNSOL_STK_PROACTIVE_COMMAND";
//     case RIL_UNSOL_STK_EVENT_NOTIFY:
//         return "UNSOL_STK_EVENT_NOTIFY";
//     case RIL_UNSOL_STK_CALL_SETUP:
//         return "UNSOL_STK_CALL_SETUP";
//     case RIL_UNSOL_SIM_SMS_STORAGE_FULL:
//         return "UNSOL_SIM_SMS_STORAGE_FULL";
//     case RIL_UNSOL_SIM_REFRESH:
//         return "UNSOL_SIM_REFRESH";
//     case RIL_UNSOL_CALL_RING:
//         return "UNSOL_CALL_RING";
//     case RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED:
//         return "UNSOL_RESPONSE_SIM_STATUS_CHANGED";
//     case RIL_UNSOL_RESPONSE_CDMA_NEW_SMS:
//         return "UNSOL_RESPONSE_CDMA_NEW_SMS";
//     case RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS:
//         return "UNSOL_RESPONSE_NEW_BROADCAST_SMS";
//     case RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL:
//         return "UNSOL_CDMA_RUIM_SMS_STORAGE_FULL";
//     case RIL_UNSOL_RESTRICTED_STATE_CHANGED:
//         return "UNSOL_RESTRICTED_STATE_CHANGED";
//     case RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE:
//         return "UNSOL_ENTER_EMERGENCY_CALLBACK_MODE";
//     case RIL_UNSOL_CDMA_CALL_WAITING:
//         return "UNSOL_CDMA_CALL_WAITING";
//     case RIL_UNSOL_CDMA_OTA_PROVISION_STATUS:
//         return "UNSOL_CDMA_OTA_PROVISION_STATUS";
//     case RIL_UNSOL_CDMA_INFO_REC:
//         return "UNSOL_CDMA_INFO_REC";
//     case RIL_UNSOL_OEM_HOOK_RAW:
//         return "UNSOL_OEM_HOOK_RAW";
//     case RIL_UNSOL_RINGBACK_TONE:
//         return "UNSOL_RINGBACK_TONG";
//     case RIL_UNSOL_RESEND_INCALL_MUTE:
//         return "UNSOL_RESEND_INCALL_MUTE";
//     case RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED:
//         return "CDMA_SUBSCRIPTION_SOURCE_CHANGED";
//     case RIL_UNSOl_CDMA_PRL_CHANGED:
//         return "UNSOL_CDMA_PRL_CHANGED";
//     case RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE:
//         return "UNSOL_EXIT_EMERGENCY_CALLBACK_MODE";
//     case RIL_UNSOL_RIL_CONNECTED:
//         return "UNSOL_RIL_CONNECTED";
//     default:
//         return "<unknown reponse>";
//     }
// }

// private
// void riljLog(String msg)
// {
//     Log.d(LOG_TAG, msg);
// }

// private
// void riljLogv(String msg)
// {
//     Log.v(LOG_TAG, msg);
// }

// private
// void unsljLog(int response)
// {
//     riljLog("[UNSL]< " + responseToString(response));
// }

// private
// void unsljLogMore(int response, String more)
// {
//     riljLog("[UNSL]< " + responseToString(response) + " " + more);
// }

// private
// void unsljLogRet(int response, Object ret)
// {
//     riljLog("[UNSL]< " + responseToString(response) + " " + retToString(response, ret));
// }

// private
// void unsljLogvRet(int response, Object ret)
// {
//     riljLogv("[UNSL]< " + responseToString(response) + " " + retToString(response, ret));
// }

// // ***** Methods for CDMA support
// public
// void getDeviceIdentity(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_DEVICE_IDENTITY, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void getCDMASubscription(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_SUBSCRIPTION, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// void setPhoneType(int phoneType)
// { // Called by CDMAPhone and GSMPhone constructor
//     if (RIL_VERBOSE)
//         riljLog("setPhoneType=" + phoneType + " old value=" + mPhoneType);
//     mPhoneType = phoneType;
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void queryCdmaRoamingPreference(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaRoamingPreference(int cdmaRoamingType, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(cdmaRoamingType);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + cdmaRoamingType);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setCdmaSubscriptionSource(int cdmaSubscription, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(cdmaSubscription);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + cdmaSubscription);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// void getCdmaSubscriptionSource(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void queryTTYMode(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_QUERY_TTY_MODE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void setTTYMode(int ttyMode, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(
//         RILConstants.RIL_REQUEST_SET_TTY_MODE, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(ttyMode);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + ttyMode);

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void sendCDMAFeatureCode(String FeatureCode, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_FLASH, response);

//     rr.mp.writeString(FeatureCode);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL+ " : " + FeatureCode);

//     RILREQUEST::send(rr);
// }

// public
// void getCdmaBroadcastConfig(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG, response);

//     RILREQUEST::send(rr);
// }

// // TODO: Change the configValuesArray to a RIL_BroadcastSMSConfig
// public
// void setCdmaBroadcastConfig(int[] configValuesArray, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG, response);

//     for (int i = 0; i < configValuesArray.length; i++)
//     {
//         rr.mp.writeInt(configValuesArray[i]);
//     }

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void setCdmaBroadcastActivation(boolean activate, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_CDMA_BROADCAST_ACTIVATION, response);

//     rr.mp.writeInt(1);
//     rr.mp.writeInt(activate ? 0 : 1);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// /**
//      * {@inheritDoc}
//      */
// public
// void exitEmergencyCallbackMode(RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE, response);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }

// public
// void requestIsimAuthentication(String nonce, RilResponse *response)
// {
//     RilRequest *rr = RILREQUEST::obtain(RIL_REQUEST_ISIM_AUTHENTICATION, response);

//     rr.mp.writeString(nonce);

//     if (RIL_VERBOSE)
//         LOGV << rr->serialString() + "> " << rr->requestToString() << ENDL;

//     RILREQUEST::send(rr);
// }
// }
