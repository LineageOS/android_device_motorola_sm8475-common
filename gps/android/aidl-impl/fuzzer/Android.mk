LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := aidl_fuzzer_android_hardware_gnss
LOCAL_VENDOR_MODULE := true

LOCAL_C_INCLUDES:= \
    $(LOCAL_PATH)/../

LOCAL_SRC_FILES := \
    fuzzer.cpp

LOCAL_HEADER_LIBRARIES := \
    libgps.utils_headers \
    libloc_core_headers \
    libloc_pla_headers \
    liblocation_api_headers

LOCAL_SHARED_LIBRARIES := \
    liblog \
    libcutils \
    libdl \
    libbase \
    libutils \
    libgps.utils \
    liblocation_api \
    libbinder \
    libbinder_ndk

ifneq ($(TARGET_SUPPORTS_WEARABLES),true)
    LOCAL_SHARED_LIBRARIES += libqti_vndfwk_detect_vendor
else
    LOCAL_SHARED_LIBRARIES += libqti_vndfwk_detect
endif

LOCAL_SHARED_LIBRARIES += \
    libhidlbase \
    android.hardware.gnss-V3-ndk \
    android.hardware.gnss-aidl-impl-qti \
    libclang_rt.ubsan_standalone

LOCAL_CFLAGS += $(GNSS_CFLAGS)

LOCAL_STATIC_LIBRARIES += libbinder_random_parcel

include $(BUILD_FUZZ_TEST)