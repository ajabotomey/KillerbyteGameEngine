TEST_PATH := $(call my-dir)/../../
ENGINE_PATH := $(call my-dir)/../../../KillerbyteGameEngine/src

# Engine
LOCAL_PATH := $(call my-dir)/../../../KillerbyteGameEngine/android/obj/local/armeabi
include $(CLEAR_VARS)
LOCAL_MODULE    := libKillerbyte
LOCAL_SRC_FILES := libKillerbyte.a
include $(PREBUILT_STATIC_LIBRARY)

# TestTriangle
LOCAL_PATH := $(TEST_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE := TestTriangle
LOCAL_SRC_FILES := ../KillerbyteGameEngine/src/MainAndroid.cpp TestTriangle.cpp

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2
LOCAL_CFLAGS    := -D__ANDROID__ -Wno-psabi -I"../../KillerbyteGameEngine/src"
LOCAL_STATIC_LIBRARIES := android_native_app_glue libKillerbyte

include $(BUILD_SHARED_LIBRARY)
$(call import-module, android/native_app_glue)