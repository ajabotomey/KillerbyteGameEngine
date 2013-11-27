#ifdef _WIN32

#include "Base.h"
#include "Platform.h"
#include "glew/include/wglew.h"

// All Win32 code goes here

// Some default values for now
#define WINDOW_TITLE "OpenGL Win32"
#define WINDOW_CLASS WINDOW_TITLE " Class"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Some Win32 Global variables
HINSTANCE hInstance;
HWND hwnd;
HDC hdc;
HGLRC hglrc;
static double ticksPerMilli;
static double startTime;
static double absoluteTime;

// Message Handler for Win32. Essentially, all input is handled here
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

namespace KillerbyteGameEngine
{
	// Setup the Pixel Format
	void SetupPixelFormat(HDC hDC)
	{
		//Create a description of the pixel format that you want
		PIXELFORMATDESCRIPTOR pfd;

		//Store the size of the structure
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);

		//This version value should always be set to 1
		pfd.nVersion = 1;

		//Drawing to a window, using double buffered opengl
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

		//Use RGBA colours rather than indexed
		pfd.iPixelType = PFD_TYPE_RGBA;

		//24 bits for the RGB of the pixels (don't include the size of the alpha channel)
		pfd.cColorBits = 24;

		//Number of bits for the depth buffer
		pfd.cDepthBits = 16;

		//Find the nearest approximation for your pixel format
		int pixelFormat(ChoosePixelFormat(hDC, &pfd));

		//Set the current pixel format as that nearest approximation
		SetPixelFormat(hDC, pixelFormat, &pfd);
	}

	Platform::~Platform()
	{
		if (hwnd)
		{
			DestroyWindow(hwnd);
			hwnd = 0;
		}
	}

	void Platform::Initialize(Game* game)
	{
		//Struct to describe the main window.
		WNDCLASSEX windowClass;

		//Empty the windowClass struct
		memset(&windowClass, 0, sizeof(WNDCLASSEX));

		windowClass.cbSize = sizeof(WNDCLASSEX);		//Store the size of the struct
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	//Redraw the window on horizontal or vertical size changes
		windowClass.lpfnWndProc = WndProc;			//The message handling function to be used by the window
		windowClass.hInstance = hInstance;			//Handle to the window's instance
		windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//Use the custom icon that we added to the project
		windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//Use the custom icon that we added to the project
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);//Use the standard "Windows arrow" cursor in this window
		windowClass.hbrBackground = (HBRUSH)COLOR_ACTIVEBORDER;//Use the "active border" colour for the window background
		windowClass.lpszClassName = WINDOW_CLASS;			//Assign a name to this window class

		//Attempt to register this window class with Windows
		if (!RegisterClassEx(&windowClass))
		{
			MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			//Exit the program
			// Log the error
		}

		//Create an, initially invisible, window
		hwnd = CreateWindowEx(NULL,
			WINDOW_CLASS,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW,
			50, 50,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			0,
			0,
			hInstance,
			NULL);

		//If now window was created
		if (!hwnd)
		{
			MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
			// Log the error
		}

		//Get the window's device context
		if (!(hdc = GetDC(hwnd)))
		{
			MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		//Create an appropriate pixel format from the device context
		SetupPixelFormat(hdc);

		//Create a windows opengl context from the device context
		hglrc = wglCreateContext(hdc);

		//Make the newly created GL context the current one to use
		wglMakeCurrent(hdc, hglrc);

		if (glewInit() != GLEW_OK)
		{
			wglDeleteContext(hglrc);
			DestroyWindow(hwnd);
			return;
		}

		// Show the window
		ShowWindow(hwnd, SW_SHOW);
		SetForegroundWindow(hwnd);
		SetFocus(hwnd);
		ResizeEvent(WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	void Platform::Run()
	{
		// Get the initial time
		LARGE_INTEGER timePerSecond;
		QueryPerformanceCounter(&timePerSecond);
		ticksPerMilli = (double)(timePerSecond.QuadPart / 1000L);
		LARGE_INTEGER queryTime;
		QueryPerformanceCounter(&queryTime);
		startTime = queryTime.QuadPart / ticksPerMilli;

		SwapBuffers(hdc);

		// Run the game
		if (gameInstance->GetState() != Game::RUNNING)
		{
			gameInstance->Run();
		}

		// Contains each message sent to the window
		MSG msg;
		bool finished = false;

		// Now to check for messages
		while (!finished)
		{
			//Take a message from the message queue
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				//If a quit message then break;
				if (msg.message == WM_QUIT)
				{
					finished = true;
				}
				else
				{
					//Take a virtual-key message and change it to a MSG struct
					TranslateMessage(&msg);

					//Send this translated message to the message handling function
					DispatchMessage(&msg);
				}
			}
			else
			{
				//Run the OpenGL draw commands
				gameInstance->Frame();
				SwapBuffers(hdc);
			}

			if (gameInstance->GetState() == Game::UNINITIALIZED)
			{
				break;
			}
		}
	}

	void Platform::Shutdown()
	{
		//Make sure there is now no windows GL context in use
		wglMakeCurrent(hdc, NULL);

		//Delete the windows GL context that you created
		wglDeleteContext(hglrc);

		//Now that you're done with the window, unregister it!
		UnregisterClass(WINDOW_CLASS, hInstance);
	}

	unsigned int Platform::getDisplayWidth()
	{
		static RECT rect;
		GetClientRect(hwnd, &rect);
		return rect.right - rect.left;
	}

	unsigned int Platform::getDisplayHeight()
	{
		static RECT rect;
		GetClientRect(hwnd, &rect);
		return rect.bottom - rect.top;
	}

	double Platform::GetAbsoluteTime()
	{
		LARGE_INTEGER queryTime;
		QueryPerformanceCounter(&queryTime);
		absoluteTime = queryTime.QuadPart / ticksPerMilli;

		return absoluteTime - startTime;
	}

	void Platform::SetAbsoluteTime(double time)
	{
		absoluteTime = time;
	}
}

#endif