/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __RIL
#define __RIL

#define SETUP_DATA_PROTOCOL_IP "IP"
#define SETUP_DATA_PROTOCOL_IPV6 "IPV6"
#define SETUP_DATA_PROTOCOL_IPV4V6 "IPV4V6"
enum RILConstants
{
    // From the top of ril.cpp
    RIL_ERRNO_INVALID_RESPONSE = -1,

    MAX_INT = 0x7FFFFFFF,

    // from RIL_Errno
    SUCCESS = 0,
    RADIO_NOT_AVAILABLE = 1, /* If radio did not start or is resetting */
    GENERIC_FAILURE = 2,
    PASSWORD_INCORRECT = 3, /* for PIN/PIN2 methods only! */
    SIM_PIN2 = 4,           /* Operation requires SIM PIN2 to be entered */
    SIM_PUK2 = 5,           /* Operation requires SIM PIN2 to be entered */
    REQUEST_NOT_SUPPORTED = 6,
    REQUEST_CANCELLED = 7,
    OP_NOT_ALLOWED_DURING_VOICE_CALL = 8, /* data operation is not allowed during voice call in
                                                 class C */
    OP_NOT_ALLOWED_BEFORE_REG_NW = 9,     /* request is not allowed before device registers to
                                                 network */
    SMS_SEND_FAIL_RETRY = 10,             /* send sms fail and need retry */
    SIM_ABSENT = 11,                      /* ICC card is absent */
    SUBSCRIPTION_NOT_AVAILABLE = 12,      /* fail to find CDMA subscription from specified
                                                 location */
    MODE_NOT_SUPPORTED = 13,              /* HW does not support preferred network type */
    FDN_CHECK_FAILURE = 14,               /* send operation barred error when FDN is enabled */
    ILLEGAL_SIM_OR_ME = 15,               /* network selection failure due
                                                 to wrong SIM/ME and no
                                                 retries needed */

    /* NETWORK_MODE_* See ril.h RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE */
    NETWORK_MODE_WCDMA_PREF = 0,               /* GSM/WCDMA (WCDMA preferred) */
    NETWORK_MODE_GSM_ONLY = 1,                 /* GSM only */
    NETWORK_MODE_WCDMA_ONLY = 2,               /* WCDMA only */
    NETWORK_MODE_GSM_UMTS = 3,                 /* GSM/WCDMA (auto mode, according to PRL)
                                            AVAILABLE Application Settings menu*/
    NETWORK_MODE_CDMA = 4,                     /* CDMA and EvDo (auto mode, according to PRL)
                                            AVAILABLE Application Settings menu*/
    NETWORK_MODE_CDMA_NO_EVDO = 5,             /* CDMA only */
    NETWORK_MODE_EVDO_NO_CDMA = 6,             /* EvDo only */
    NETWORK_MODE_GLOBAL = 7,                   /* GSM/WCDMA, CDMA, and EvDo (auto mode, according to PRL)
                                            AVAILABLE Application Settings menu*/
    NETWORK_MODE_LTE_CDMA_EVDO = 8,            /* LTE, CDMA and EvDo */
    NETWORK_MODE_LTE_GSM_WCDMA = 9,            /* LTE, GSM/WCDMA */
    NETWORK_MODE_LTE_CMDA_EVDO_GSM_WCDMA = 10, /* LTE, CDMA, EvDo, GSM/WCDMA */
    NETWORK_MODE_LTE_ONLY = 11,                /* LTE Only mode. */

    PREFERRED_NETWORK_MODE = NETWORK_MODE_WCDMA_PREF,

    /* CDMA subscription source. See ril.h RIL_REQUEST_CDMA_SET_SUBSCRIPTION */
    SUBSCRIPTION_FROM_RUIM = 0, /* CDMA subscription from RUIM when available */
    SUBSCRIPTION_FROM_NV = 1,   /* CDMA subscription from NV */
    PREFERRED_CDMA_SUBSCRIPTION = SUBSCRIPTION_FROM_NV,

    CDMA_CELL_BROADCAST_SMS_DISABLED = 1,
    CDMA_CELL_BROADCAST_SMS_ENABLED = 0,

    NO_PHONE = 0,
    GSM_PHONE = 1,
    CDMA_PHONE = 2,
    SIP_PHONE = 3,

    LTE_ON_CDMA_UNKNOWN = -1,
    LTE_ON_CDMA_FALSE = 0,
    LTE_ON_CDMA_TRUE = 1,

    CDM_TTY_MODE_DISABLED = 0,
    CDM_TTY_MODE_ENABLED = 1,

    CDM_TTY_FULL_MODE = 1,
    CDM_TTY_HCO_MODE = 2,
    CDM_TTY_VCO_MODE = 3,

    /* Setup a packet data connection. See ril.h RIL_REQUEST_SETUP_DATA_CALL */
    SETUP_DATA_TECH_CDMA = 0,
    SETUP_DATA_TECH_GSM = 1,

    SETUP_DATA_AUTH_NONE = 0,
    SETUP_DATA_AUTH_PAP = 1,
    SETUP_DATA_AUTH_CHAP = 2,
    SETUP_DATA_AUTH_PAP_CHAP = 3,

    /* Deactivate data call reasons */
    DEACTIVATE_REASON_NONE = 0,
    DEACTIVATE_REASON_RADIO_OFF = 1,
    DEACTIVATE_REASON_PDP_RESET = 2,

    /**
     * No restriction at all including voice/SMS/USSD/SS/AV64
     * and packet data.
     */
    RIL_RESTRICTED_STATE_NONE = 0x00,
    /**
     * Block emergency call due to restriction.
     * But allow all normal voice/SMS/USSD/SS/AV64.
     */
    RIL_RESTRICTED_STATE_CS_EMERGENCY = 0x01,
    /**
     * Block all normal voice/SMS/USSD/SS/AV64 due to restriction.
     * Only Emergency call allowed.
     */
    RIL_RESTRICTED_STATE_CS_NORMAL = 0x02,
    /**
     * Block all voice/SMS/USSD/SS/AV64
     * including emergency call due to restriction.
     */
    RIL_RESTRICTED_STATE_CS_ALL = 0x04,
    /**
     * Block packet data access due to restriction.
     */
    RIL_RESTRICTED_STATE_PS_ALL = 0x10,

    /** Data profile for RIL_REQUEST_SETUP_DATA_CALL */
    DATA_PROFILE_DEFAULT = 0,
    DATA_PROFILE_TETHERED = 1,
    DATA_PROFILE_IMS = 2,
    DATA_PROFILE_FOTA = 3,
    DATA_PROFILE_CBS = 4,
    DATA_PROFILE_OEM_BASE = 1000,

    RIL_REQUEST_GET_SIM_STATUS = 1,
    RIL_REQUEST_ENTER_SIM_PIN = 2,
    RIL_REQUEST_ENTER_SIM_PUK = 3,
    RIL_REQUEST_ENTER_SIM_PIN2 = 4,
    RIL_REQUEST_ENTER_SIM_PUK2 = 5,
    RIL_REQUEST_CHANGE_SIM_PIN = 6,
    RIL_REQUEST_CHANGE_SIM_PIN2 = 7,
    RIL_REQUEST_ENTER_NETWORK_DEPERSONALIZATION = 8,
    RIL_REQUEST_GET_CURRENT_CALLS = 9,
    RIL_REQUEST_DIAL = 10,
    RIL_REQUEST_GET_IMSI = 11,
    RIL_REQUEST_HANGUP = 12,
    RIL_REQUEST_HANGUP_WAITING_OR_BACKGROUND = 13,
    RIL_REQUEST_HANGUP_FOREGROUND_RESUME_BACKGROUND = 14,
    RIL_REQUEST_SWITCH_WAITING_OR_HOLDING_AND_ACTIVE = 15,
    RIL_REQUEST_CONFERENCE = 16,
    RIL_REQUEST_UDUB = 17,
    RIL_REQUEST_LAST_CALL_FAIL_CAUSE = 18,
    RIL_REQUEST_SIGNAL_STRENGTH = 19,
    RIL_REQUEST_VOICE_REGISTRATION_STATE = 20,
    RIL_REQUEST_DATA_REGISTRATION_STATE = 21,
    RIL_REQUEST_OPERATOR = 22,
    RIL_REQUEST_RADIO_POWER = 23,
    RIL_REQUEST_DTMF = 24,
    RIL_REQUEST_SEND_SMS = 25,
    RIL_REQUEST_SEND_SMS_EXPECT_MORE = 26,
    RIL_REQUEST_SETUP_DATA_CALL = 27,
    RIL_REQUEST_SIM_IO = 28,
    RIL_REQUEST_SEND_USSD = 29,
    RIL_REQUEST_CANCEL_USSD = 30,
    RIL_REQUEST_GET_CLIR = 31,
    RIL_REQUEST_SET_CLIR = 32,
    RIL_REQUEST_QUERY_CALL_FORWARD_STATUS = 33,
    RIL_REQUEST_SET_CALL_FORWARD = 34,
    RIL_REQUEST_QUERY_CALL_WAITING = 35,
    RIL_REQUEST_SET_CALL_WAITING = 36,
    RIL_REQUEST_SMS_ACKNOWLEDGE = 37,
    RIL_REQUEST_GET_IMEI = 38,
    RIL_REQUEST_GET_IMEISV = 39,
    RIL_REQUEST_ANSWER = 40,
    RIL_REQUEST_DEACTIVATE_DATA_CALL = 41,
    RIL_REQUEST_QUERY_FACILITY_LOCK = 42,
    RIL_REQUEST_SET_FACILITY_LOCK = 43,
    RIL_REQUEST_CHANGE_BARRING_PASSWORD = 44,
    RIL_REQUEST_QUERY_NETWORK_SELECTION_MODE = 45,
    RIL_REQUEST_SET_NETWORK_SELECTION_AUTOMATIC = 46,
    RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL = 47,
    RIL_REQUEST_QUERY_AVAILABLE_NETWORKS = 48,
    RIL_REQUEST_DTMF_START = 49,
    RIL_REQUEST_DTMF_STOP = 50,
    RIL_REQUEST_BASEBAND_VERSION = 51,
    RIL_REQUEST_SEPARATE_CONNECTION = 52,
    RIL_REQUEST_SET_MUTE = 53,
    RIL_REQUEST_GET_MUTE = 54,
    RIL_REQUEST_QUERY_CLIP = 55,
    RIL_REQUEST_LAST_DATA_CALL_FAIL_CAUSE = 56,
    RIL_REQUEST_DATA_CALL_LIST = 57,
    RIL_REQUEST_RESET_RADIO = 58,
    RIL_REQUEST_OEM_HOOK_RAW = 59,
    RIL_REQUEST_OEM_HOOK_STRINGS = 60,
    RIL_REQUEST_SCREEN_STATE = 61,
    RIL_REQUEST_SET_SUPP_SVC_NOTIFICATION = 62,
    RIL_REQUEST_WRITE_SMS_TO_SIM = 63,
    RIL_REQUEST_DELETE_SMS_ON_SIM = 64,
    RIL_REQUEST_SET_BAND_MODE = 65,
    RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE = 66,
    RIL_REQUEST_STK_GET_PROFILE = 67,
    RIL_REQUEST_STK_SET_PROFILE = 68,
    RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND = 69,
    RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE = 70,
    RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM = 71,
    RIL_REQUEST_EXPLICIT_CALL_TRANSFER = 72,
    RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE = 73,
    RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE = 74,
    RIL_REQUEST_GET_NEIGHBORING_CELL_IDS = 75,
    RIL_REQUEST_SET_LOCATION_UPDATES = 76,
    RIL_REQUEST_CDMA_SET_SUBSCRIPTION_SOURCE = 77,
    RIL_REQUEST_CDMA_SET_ROAMING_PREFERENCE = 78,
    RIL_REQUEST_CDMA_QUERY_ROAMING_PREFERENCE = 79,
    RIL_REQUEST_SET_TTY_MODE = 80,
    RIL_REQUEST_QUERY_TTY_MODE = 81,
    RIL_REQUEST_CDMA_SET_PREFERRED_VOICE_PRIVACY_MODE = 82,
    RIL_REQUEST_CDMA_QUERY_PREFERRED_VOICE_PRIVACY_MODE = 83,
    RIL_REQUEST_CDMA_FLASH = 84,
    RIL_REQUEST_CDMA_BURST_DTMF = 85,
    RIL_REQUEST_CDMA_VALIDATE_AND_WRITE_AKEY = 86,
    RIL_REQUEST_CDMA_SEND_SMS = 87,
    RIL_REQUEST_CDMA_SMS_ACKNOWLEDGE = 88,
    RIL_REQUEST_GSM_GET_BROADCAST_CONFIG = 89,
    RIL_REQUEST_GSM_SET_BROADCAST_CONFIG = 90,
    RIL_REQUEST_GSM_BROADCAST_ACTIVATION = 91,
    RIL_REQUEST_CDMA_GET_BROADCAST_CONFIG = 92,
    RIL_REQUEST_CDMA_SET_BROADCAST_CONFIG = 93,
    RIL_REQUEST_CDMA_BROADCAST_ACTIVATION = 94,
    RIL_REQUEST_CDMA_SUBSCRIPTION = 95,
    RIL_REQUEST_CDMA_WRITE_SMS_TO_RUIM = 96,
    RIL_REQUEST_CDMA_DELETE_SMS_ON_RUIM = 97,
    RIL_REQUEST_DEVICE_IDENTITY = 98,
    RIL_REQUEST_EXIT_EMERGENCY_CALLBACK_MODE = 99,
    RIL_REQUEST_GET_SMSC_ADDRESS = 100,
    RIL_REQUEST_SET_SMSC_ADDRESS = 101,
    RIL_REQUEST_REPORT_SMS_MEMORY_STATUS = 102,
    RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING = 103,
    RIL_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE = 104,
    RIL_REQUEST_ISIM_AUTHENTICATION = 105,
    RIL_REQUEST_ACKNOWLEDGE_INCOMING_GSM_SMS_WITH_PDU = 106,
    RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS = 107,
    RIL_UNSOL_RESPONSE_BASE = 1000,
    RIL_UNSOL_RESPONSE_RADIO_STATE_CHANGED = 1000,
    RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED = 1001,
    RIL_UNSOL_RESPONSE_VOICE_NETWORK_STATE_CHANGED = 1002,
    RIL_UNSOL_RESPONSE_NEW_SMS = 1003,
    RIL_UNSOL_RESPONSE_NEW_SMS_STATUS_REPORT = 1004,
    RIL_UNSOL_RESPONSE_NEW_SMS_ON_SIM = 1005,
    RIL_UNSOL_ON_USSD = 1006,
    RIL_UNSOL_ON_USSD_REQUEST = 1007,
    RIL_UNSOL_NITZ_TIME_RECEIVED = 1008,
    RIL_UNSOL_SIGNAL_STRENGTH = 1009,
    RIL_UNSOL_DATA_CALL_LIST_CHANGED = 1010,
    RIL_UNSOL_SUPP_SVC_NOTIFICATION = 1011,
    RIL_UNSOL_STK_SESSION_END = 1012,
    RIL_UNSOL_STK_PROACTIVE_COMMAND = 1013,
    RIL_UNSOL_STK_EVENT_NOTIFY = 1014,
    RIL_UNSOL_STK_CALL_SETUP = 1015,
    RIL_UNSOL_SIM_SMS_STORAGE_FULL = 1016,
    RIL_UNSOL_SIM_REFRESH = 1017,
    RIL_UNSOL_CALL_RING = 1018,
    RIL_UNSOL_RESPONSE_SIM_STATUS_CHANGED = 1019,
    RIL_UNSOL_RESPONSE_CDMA_NEW_SMS = 1020,
    RIL_UNSOL_RESPONSE_NEW_BROADCAST_SMS = 1021,
    RIL_UNSOL_CDMA_RUIM_SMS_STORAGE_FULL = 1022,
    RIL_UNSOL_RESTRICTED_STATE_CHANGED = 1023,
    RIL_UNSOL_ENTER_EMERGENCY_CALLBACK_MODE = 1024,
    RIL_UNSOL_CDMA_CALL_WAITING = 1025,
    RIL_UNSOL_CDMA_OTA_PROVISION_STATUS = 1026,
    RIL_UNSOL_CDMA_INFO_REC = 1027,
    RIL_UNSOL_OEM_HOOK_RAW = 1028,
    RIL_UNSOL_RINGBACK_TONE = 1029,
    RIL_UNSOL_RESEND_INCALL_MUTE = 1030,
    RIL_UNSOL_CDMA_SUBSCRIPTION_SOURCE_CHANGED = 1031,
    RIL_UNSOl_CDMA_PRL_CHANGED = 1032,
    RIL_UNSOL_EXIT_EMERGENCY_CALLBACK_MODE = 1033,
    RIL_UNSOL_RIL_CONNECTED = 1034
};

#endif //__RIL
