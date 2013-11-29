#ifdef __ANDROID__

#include "Base.h"
#include "Platform.h"
#include "Game.h"

#include <android/log.h>
#include <android_native_app_glue.h>

struct android_app* app;

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
		app->onAppCmd = engine_handle_cmd;
		
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
