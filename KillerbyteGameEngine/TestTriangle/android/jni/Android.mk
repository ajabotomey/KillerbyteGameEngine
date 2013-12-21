TEST_PATH := $(call my-dir)/../../
ENGINE_PATH := $(call my-dir)/../../../KillerbyteGameEngine/src
OPENAL_INCLUDE_PATH := $(call my-dir)/../../../external-deps/OpenAL/include
OPENAL_LIB_PATH := $(call my-dir)/../../../external-deps/OpenAL/lib/android
TINYXML_INCLUDE_PATH := $(call my-dir)/../../../external-deps/TinyXML/include
TINYXML_LIB_PATH := $(call my-dir)/../../../external-deps/TinyXML/lib/android
LIBPNG_INCLUDE_PATH := $(call my-dir)/../../../external-deps/libpng/include
LIBPNG_LIB_PATH := $(call my-dir)/../../../external-deps/libpng/lib/android
ZLIB_INCLUDE_PATH := $(call my-dir)/../../../external-deps/zlib/include
ZLIB_LIB_PATH := $(call my-dir)/../../../external-deps/zlib/lib/android
BULLET_INCLUDE_PATH := $(call my-dir)/../../../external-deps/Bullet/include
BULLET_LIB_PATH := $(call my-dir)/../../../external-deps/Bullet/lib/android

# Engine
LOCAL_PATH := $(call my-dir)/../../../KillerbyteGameEngine/android/obj/local/armeabi
include $(CLEAR_VARS)
LOCAL_MODULE    := libKillerbyte
LOCAL_SRC_FILES := libKillerbyte.a
include $(PREBUILT_STATIC_LIBRARY)

# libpng
LOCAL_PATH := $(LIBPNG_LIB_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libpng
LOCAL_SRC_FILES := libpng.a
include $(PREBUILT_STATIC_LIBRARY)

# zlib
LOCAL_PATH := $(ZLIB_LIB_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libzlib
LOCAL_SRC_FILES := libzlib.a
include $(PREBUILT_STATIC_LIBRARY)

# TinyXML
LOCAL_PATH := $(TINYXML_LIB_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libTinyXML
LOCAL_SRC_FILES := libTinyXML.a
include $(PREBUILT_STATIC_LIBRARY)

# Bullet
LOCAL_PATH := $(BULLET_LIB_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE := libBullet
LOCAL_SRC_FILES := libBullet.a
include $(PREBUILT_STATIC_LIBRARY)

# TestTriangle
LOCAL_PATH := $(TEST_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE := TestTriangle
LOCAL_SRC_FILES := ../KillerbyteGameEngine/src/MainAndroid.cpp TestTriangle.cpp

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lOpenSLES
LOCAL_CFLAGS    := -D__ANDROID__ -Wno-psabi -I"../../KillerbyteGameEngine/src" -I$(OPENAL_INCLUDE_PATH) -I$(LIBPNG_INCLUDE_PATH) -I$(ZLIB_INCLUDE_PATH) -I$(TINYXML_INCLUDE_PATH) -I$(BULLET_INCLUDE_PATH)
LOCAL_STATIC_LIBRARIES := android_native_app_glue libKillerbyte libpng libzlib libTinyXML libBullet

include $(BUILD_SHARED_LIBRARY)
$(call import-module, android/native_app_glue)