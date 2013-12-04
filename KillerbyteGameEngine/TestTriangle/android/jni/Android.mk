TEST_PATH := $(call my-dir)/../../
ENGINE_PATH := $(call my-dir)/../../../KillerbyteGameEngine/src
OPENAL_INCLUDE_PATH := ../../external-deps/OpenAL/include
OPENAL_LIB_PATH := $(call my-dir)/../../../external-deps/OpenAL/android/obj/local/armeabi

# Engine
LOCAL_PATH := $(call my-dir)/../../../KillerbyteGameEngine/android/obj/local/armeabi
include $(CLEAR_VARS)
LOCAL_MODULE    := libKillerbyte
LOCAL_SRC_FILES := libKillerbyte.a
include $(PREBUILT_STATIC_LIBRARY)

#OpenAL
LOCAL_PATH := $(OPENAL_LIB_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libOpenAL
LOCAL_SRC_FILES := libOpenAL.a
include $(PREBUILT_STATIC_LIBRARY)

# TestTriangle
LOCAL_PATH := $(TEST_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE := TestTriangle
LOCAL_SRC_FILES := ../KillerbyteGameEngine/src/MainAndroid.cpp TestTriangle.cpp

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2
LOCAL_CFLAGS    := -D__ANDROID__ -Wno-psabi -I"../../KillerbyteGameEngine/src" -I$(OPENAL_INCLUDE_PATH)
LOCAL_STATIC_LIBRARIES := android_native_app_glue libKillerbyte libOpenAL

include $(BUILD_SHARED_LIBRARY)
$(call import-module, android/native_app_glue)