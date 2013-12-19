#ifdef __ANDROID__

#include "Base.h"
#include "Platform.h"
#include "File.h"
#include "Game.h"

#include <android/log.h>
#include <android_native_app_glue.h>

struct android_app* app;
AAssetManager* assetManager;

EGLDisplay display = EGL_NO_DISPLAY;
EGLSurface surface = EGL_NO_SURFACE;
EGLContext context = EGL_NO_CONTEXT;
EGLConfig config = 0;
int width, height;
struct timespec _timespec;
double startTime, absoluteTime;
bool initialized = false;

namespace KillerbyteGameEngine
{
	static double timespec2millis(struct timespec *a)
	{
		return (1000.0 * a->tv_sec) + (0.000001 * a->tv_nsec);
	}

	bool InitializeEGL()
	{
		EGLint eglAttribs[] =
		{
			EGL_DEPTH_SIZE, 24,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_STENCIL_SIZE, 8,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_NONE
		};

		EGLint configCount, format;

		display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (display == EGL_NO_DISPLAY)
		{
			// Log error here
			return false;
		}

		if (!eglInitialize(display, NULL, NULL))
		{
			// Log error here
			return false;
		}

		if (!eglChooseConfig(display, eglAttribs, &config, 1, &configCount) || (configCount <= 0))
		{
			// Log error here
			return false;
		}

		if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
		{
			// Log error here
			return false;
		}

		ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

		surface = eglCreateWindowSurface(display, config, app->window, NULL);
		if (surface == EGL_NO_SURFACE)
		{
			LOGI("Surface could not be created");
			return false;
		}

		EGLint AttribList[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		context = eglCreateContext(display, config, EGL_NO_CONTEXT, AttribList);
		if (context == EGL_NO_CONTEXT)
		{
			LOGI("Context could not be created");
			return false;
		}

		if (!eglMakeCurrent(display, surface, surface, context))
		{
			LOGI("Context cannot linked to the surface");
			return false;
		}

		eglQuerySurface(display, surface, EGL_WIDTH, &width);
		eglQuerySurface(display, surface, EGL_HEIGHT, &height);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glViewport(0, 0, width, height);
		
		initialized = true;

		return true;
	}
	
	void ShutdownEGLSurface()
	{
		if (display != EGL_NO_DISPLAY)
		{
			eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		}

		if (surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(display, surface);
			surface = EGL_NO_SURFACE;
		}
	}
	
	void ShutdownEGLMain()
	{	
		ShutdownEGLSurface();

		if (context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(display, context);
			context = EGL_NO_CONTEXT;
		}

		if (display != EGL_NO_DISPLAY)
		{
			eglTerminate(display);
			display = EGL_NO_DISPLAY;
		}
	}
	
	static Keyboard::Key GetKey(int keycode, int metastate)
	{
		bool shiftKeyDown = (metastate == AMETA_SHIFT_ON);
		
		switch(keycode)
		{
			case AKEYCODE_SHIFT_LEFT:
			case AKEYCODE_SHIFT_RIGHT:
				return KillerbyteGameEngine::Keyboard::KEY_SHIFT;
			case AKEYCODE_DPAD_LEFT:
				return KillerbyteGameEngine::Keyboard::KEY_LEFTARROW;
			case AKEYCODE_DPAD_RIGHT:
				return KillerbyteGameEngine::Keyboard::KEY_RIGHTARROW;
			case AKEYCODE_DPAD_UP:
				return KillerbyteGameEngine::Keyboard::KEY_UPARROW;
			case AKEYCODE_DPAD_DOWN:
				return KillerbyteGameEngine::Keyboard::KEY_DOWNARROW;
			case AKEYCODE_A:
				return shiftKeyDown ? Keyboard::KEY_CAP_A : Keyboard::KEY_A;
			case AKEYCODE_B:
				return shiftKeyDown ? Keyboard::KEY_CAP_B : Keyboard::KEY_B;
			case AKEYCODE_C:
				return shiftKeyDown ? Keyboard::KEY_CAP_C : Keyboard::KEY_C;
			case AKEYCODE_D:
				return shiftKeyDown ? Keyboard::KEY_CAP_D : Keyboard::KEY_D;
			case AKEYCODE_E:
				return shiftKeyDown ? Keyboard::KEY_CAP_E : Keyboard::KEY_E;
			case AKEYCODE_F:
				return shiftKeyDown ? Keyboard::KEY_CAP_F : Keyboard::KEY_F;
			case AKEYCODE_G:
				return shiftKeyDown ? Keyboard::KEY_CAP_G : Keyboard::KEY_G;
			case AKEYCODE_H:
				return shiftKeyDown ? Keyboard::KEY_CAP_H : Keyboard::KEY_H;
			case AKEYCODE_I:
				return shiftKeyDown ? Keyboard::KEY_CAP_I : Keyboard::KEY_I;
			case AKEYCODE_J:
				return shiftKeyDown ? Keyboard::KEY_CAP_J : Keyboard::KEY_J;
			case AKEYCODE_K:
				return shiftKeyDown ? Keyboard::KEY_CAP_K : Keyboard::KEY_K;
			case AKEYCODE_L:
				return shiftKeyDown ? Keyboard::KEY_CAP_L : Keyboard::KEY_L;
			case AKEYCODE_M:
				return shiftKeyDown ? Keyboard::KEY_CAP_M : Keyboard::KEY_M;
			case AKEYCODE_N:
				return shiftKeyDown ? Keyboard::KEY_CAP_N : Keyboard::KEY_N;
			case AKEYCODE_O:
				return shiftKeyDown ? Keyboard::KEY_CAP_O : Keyboard::KEY_O;
			case AKEYCODE_P:
				return shiftKeyDown ? Keyboard::KEY_CAP_P : Keyboard::KEY_P;
			case AKEYCODE_Q:
				return shiftKeyDown ? Keyboard::KEY_CAP_Q : Keyboard::KEY_Q;
			case AKEYCODE_R:
				return shiftKeyDown ? Keyboard::KEY_CAP_R : Keyboard::KEY_R;
			case AKEYCODE_S:
				return shiftKeyDown ? Keyboard::KEY_CAP_S : Keyboard::KEY_S;
			case AKEYCODE_T:
				return shiftKeyDown ? Keyboard::KEY_CAP_T : Keyboard::KEY_T;
			case AKEYCODE_U:
				return shiftKeyDown ? Keyboard::KEY_CAP_U : Keyboard::KEY_U;
			case AKEYCODE_V:
				return shiftKeyDown ? Keyboard::KEY_CAP_V : Keyboard::KEY_V;
			case AKEYCODE_W:
				return shiftKeyDown ? Keyboard::KEY_CAP_W : Keyboard::KEY_W;
			case AKEYCODE_X:
				return shiftKeyDown ? Keyboard::KEY_CAP_X : Keyboard::KEY_X;
			case AKEYCODE_Y:
				return shiftKeyDown ? Keyboard::KEY_CAP_Y : Keyboard::KEY_Y;
			case AKEYCODE_Z:
				return shiftKeyDown ? Keyboard::KEY_CAP_Z : Keyboard::KEY_Z;
			default:
				return Keyboard::KEY_NONE;
		}
	}

	static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
	{
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY)
		{
			int32_t action = AKeyEvent_getAction(event);
			int32_t keycode = AKeyEvent_getKeyCode(event);
			int32_t metastate = AKeyEvent_getMetaState(event);
			
			switch(action)
			{
				case AKEY_EVENT_ACTION_DOWN:
					Game::GetInstance()->KeyEvent(Keyboard::KEY_DOWN, GetKey(keycode, metastate));
					break;
				case AKEY_EVENT_ACTION_UP:
					Platform::KeyEvent(Keyboard::KEY_UP, GetKey(keycode, metastate));
					break;
			}
		}
		
		return 0;
	}
	
	static void engine_handle_cmd(struct android_app* app, int32_t cmd)
	{
		switch (cmd)
		{
			case APP_CMD_INIT_WINDOW:
				if (app->window != NULL)
				{
					if (!InitializeEGL())
					{
						LOGI("Failed to initialize EGL");
					}
				}
				break;
			case APP_CMD_DESTROY:
				ShutdownEGLMain();
				break;
			case APP_CMD_TERM_WINDOW:
				ShutdownEGLSurface();
				break;
			case APP_CMD_GAINED_FOCUS:
				if (Game::GetInstance()->GetState() == Game::UNINITIALIZED)
				{
					Game::GetInstance()->Run();
				}
				break;
		}
	}
	
	Platform::~Platform()
	{
		
	}
	
	void Platform::Run()
	{
		LOGI("We are running");
		ANativeActivity* activity = app->activity;
		JavaVM* javaVM = app->activity->vm;
		JNIEnv* env = NULL;
		javaVM->GetEnv((void **)&env, JNI_VERSION_1_6);
		jint res = javaVM->AttachCurrentThread(&env, NULL);
		if (res == JNI_ERR)
		{
			// Log error here
			return;
		}
		
		jboolean isCopy;
		
		jclass clazz = env->GetObjectClass(activity->clazz);
		jmethodID methodGetExternalStorage = env->GetMethodID(clazz, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");
		
		jclass clazzFile = env->FindClass("java/io/File");
		jmethodID methodGetPath = env->GetMethodID(clazzFile, "getPath", "()Ljava/lang/String;");
		
		// Use Java.io.File to point to our directory
		jobject objectFile = env->CallObjectMethod(activity->clazz, methodGetExternalStorage, NULL);
		
		// Now we need to get a string which contains the path to the directory
		jstring stringExternalPath = static_cast<jstring>(env->CallObjectMethod(objectFile, methodGetPath));
		const char* externalPath = env->GetStringUTFChars(stringExternalPath, &isCopy);
		
		// Now to set the file system to the directory
		std::string assetPath(externalPath);
		if (externalPath[strlen(externalPath)-1] != '/')
			assetPath += "/";
			
		// Need to figure out a way to set the resource path in the FileSystem
		FileSystem::SetResourcePath(assetPath.c_str());
		
		LOGI("Resource Path: %s", FileSystem::GetResourcePath());
		
		// Now to release all the string data
		env->ReleaseStringUTFChars(stringExternalPath, externalPath);
		javaVM->DetachCurrentThread();
		
		// Get the asset manager so we can load assets from the .apk file
		assetManager = activity->assetManager;
	
		// Set the callback functions for the app
		app->onAppCmd = engine_handle_cmd;
		app->onInputEvent = engine_handle_input;
		
		// Get the initial time
		clock_gettime(CLOCK_REALTIME, &_timespec);
		startTime = timespec2millis(&_timespec);
		absoluteTime = 0L;
		
		bool running = true;
		while(running)
		{
			int events;
			struct android_poll_source* source;
			int ident = ALooper_pollAll(0, 0, &events, (void**)&source);
			if (ident >= 0)
			{
				if (source)
				{
					source->process(app, source);
				}

				if (app->destroyRequested)
				{
					running = false;
				}
			}

			if (initialized)
			{
				gameInstance->Frame();
				eglSwapBuffers(display, surface);
			}
		}
	}
	
	void Platform::Shutdown()
	{
		ShutdownEGLMain();
	}
	
	unsigned int Platform::getDisplayWidth()
	{
		return width;
	}
	
	unsigned int Platform::getDisplayHeight()
	{
		return height;
	}
	
	double Platform::GetAbsoluteTime()
	{
		clock_gettime(CLOCK_REALTIME, &_timespec);
		double now = timespec2millis(&_timespec);
		absoluteTime = now - startTime;
		
		return absoluteTime;
	}
	
	void Platform::SetAbsoluteTime(double time)
	{
		absoluteTime = time;
	}
}
#endif
