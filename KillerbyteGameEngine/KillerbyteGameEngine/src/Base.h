#ifndef BASE_H_
#define BASE_H_

// This file essentially defines all the external includes as well as the data types used in this engine
// Will Also Contain Handles for major components such as the logger
// TODO: Add Support for iOS, Mac OSX and Android

// C++ Includes
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

// Image Loading
//#include <png.h>

// Audio Loading
#ifdef __ANDROID__
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

// Graphics Includes
#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif __linux__ 
#define GLEW_STATIC
#include "glew/include/glew.h"
#elif _WIN32
#define WIN32_LEAN_AND_MEAN
#define GLEW_STATIC
#include <Windows.h>
#include <glew.h>
#endif

#ifndef NULL
#define NULL     0
#endif

// Math defines
#define PI 3.14159265359
#define DEG2RAD (PI / 180.0)
#define RAD2DEG (180.0 / PI)

// A nice function for checking array size
template <typename T, unsigned S>
inline unsigned arraysize(const T(&v)[S]) { return S; }

// Android Logging
#ifdef __ANDROID__
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Killerbyte", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Killerbyte", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "Killerbyte", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "Killerbyte", __VA_ARGS__))
#endif

#endif