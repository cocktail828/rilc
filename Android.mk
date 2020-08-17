LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    DeviceManager.cpp \
    logger.cpp \
    main.cpp \
    rilc_api.cpp \
    ril_request.cpp \
    ril_response.cpp \
    parcel/parcel.cpp \
    parcel/strdup8to16.cpp \
    parcel/strdup16to8.cpp

LOCAL_CPPFLAGS += -pie -fPIE -Wall -g
LOCAL_LDFLAGS += -pie -fPIE
LOCAL_MODULE_TAGS:= optional

LOCAL_MODULE:= rilc
include $(BUILD_EXECUTABLE)
