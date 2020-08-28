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

void set_ril_version(int ver);
int get_ril_version();

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

void responseGmsBroadcastConfig(Parcel &p, RILResponse *resp);
void responseGmsBroadcastConfigShow(RILResponse *resp);
void responseGmsBroadcastConfigFree(RILResponse *resp);

void responseCellList(Parcel &, RILResponse *);
void responseCellListShow(RILResponse *);
void responseCellListFree(RILResponse *);

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

void responseCellInfoList(Parcel &, RILResponse *);
void responseCellInfoListShow(RILResponse *);
void responseCellInfoListFree(RILResponse *);

void responseSIM_IO(Parcel &, RILResponse *);
void responseSIM_IOShow(RILResponse *);
void responseSIM_IOFree(RILResponse *);

void responseHardwareConfig(Parcel &, RILResponse *);
void responseHardwareConfigShow(RILResponse *);
void responseHardwareConfigFree(RILResponse *);

void responseDcRtInfo(Parcel &, RILResponse *);
void responseDcRtInfoShow(RILResponse *);
void responseDcRtInfoFree(RILResponse *);

void responseRadioCapability(Parcel &, RILResponse *);
void responseRadioCapabilityShow(RILResponse *);
void responseRadioCapabilityFree(RILResponse *);

void responseLceStatus(Parcel &, RILResponse *);
void responseLceStatusShow(RILResponse *);
void responseLceStatusFree(RILResponse *);

void responseLceData(Parcel &, RILResponse *);
void responseLceDataShow(RILResponse *);
void responseLceDataFree(RILResponse *);

void responseActivityData(Parcel &, RILResponse *);
void responseActivityDataShow(RILResponse *);
void responseActivityDataFree(RILResponse *);

void responseSSData(Parcel &, RILResponse *);
void responseSSDataShow(RILResponse *);
void responseSSDataFree(RILResponse *);

void responseSsn(Parcel &, RILResponse *);
void responseSsnShow(RILResponse *);
void responseSsnFree(RILResponse *);

typedef struct
{
    int commandid;
    void (*responseParser)(Parcel &, RILResponse *);
    void (*responseShow)(RILResponse *);
    void (*responseFree)(RILResponse *);
    void (*callback)(RILResponse *);
} RILCProcesser;

RILCProcesser *rilcFindSocilitedProcesser(int cmdid);
RILCProcesser *rilcFindUnSocilitedProcesser(int cmdid);

#endif //__RIL_RESPONSE
