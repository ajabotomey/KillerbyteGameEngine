LOCAL_PATH := $(call my-dir)/../../src

include $(CLEAR_VARS)
LOCAL_MODULE := libKillerbyte
LOCAL_SRC_FILES := \
    Audio/AudioController.cpp \
    Audio/AudioClip.cpp \
    Camera.cpp \
    File.cpp \
    FileSystem.cpp \
    Image.cpp \
    Game.cpp \
    LogManager.cpp \
    Node.cpp \
    Math/Matrix44.cpp \
    Model.cpp \
    Platform/Platform.cpp \
    Platform/PlatformAndroid.cpp \
    Scene.cpp \
    Shader.cpp \
    Texture.cpp

LOCAL_CFLAGS := -D__ANDROID__ -I"../../external-deps/OpenAL/include" -I"../../external-deps/TinyXML/include" -I"../../external-deps/libpng/include" -I"../../external-deps/zlib/include"
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

$(call import-module, android/native_app_glue)