LOCAL_PATH := $(call my-dir)/../../src

include $(CLEAR_VARS)
LOCAL_MODULE := libKillerbyte
LOCAL_SRC_FILES := \
    Camera.cpp \
    Game.cpp \
    Matrix44.cpp \
    Model.cpp \
    Platform.cpp \
    PlatformAndroid.cpp \
    Shader.cpp 

LOCAL_CFLAGS := -D__ANDROID__
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

$(call import-module, android/native_app_glue)