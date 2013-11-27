#ifndef BASE_H_
#define BASE_H_

// This file essentially defines all the external includes as well as the data types used in this engine
// Will Also Contain Handles for major components such as the logger
// TODO: Add Support for iOS, Mac OSX and Android

// C++ Includes
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
#include "glew/include/glew.h"
#endif

#ifndef NULL
#define NULL     0
#endif

// Math defines
#define PI 3.14159265359
#define DEG2RAD (PI / 180.0)
#define RAD2DEG (180.0 / PI)

#endif