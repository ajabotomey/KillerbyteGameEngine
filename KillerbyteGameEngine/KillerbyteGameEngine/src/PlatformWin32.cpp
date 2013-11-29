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

// Special Key accessor. Take in a WPARAM and map that to a key in the keyboard class
static KillerbyteGameEngine::Keyboard::Key getKey(WPARAM keyCode, bool shiftKeyDown)
{
	switch (keyCode)
	{
	case VK_ESCAPE:
		return KillerbyteGameEngine::Keyboard::KEY_ESCAPE;
	case VK_SHIFT:
	case VK_LSHIFT:
	case VK_RSHIFT:
		return KillerbyteGameEngine::Keyboard::KEY_SHIFT;
	case VK_LEFT:
		return KillerbyteGameEngine::Keyboard::KEY_LEFTARROW;
	case VK_RIGHT:
		return KillerbyteGameEngine::Keyboard::KEY_RIGHTARROW;
	case VK_UP:
		return KillerbyteGameEngine::Keyboard::KEY_UPARROW;
	case VK_DOWN:
		return KillerbyteGameEngine::Keyboard::KEY_DOWNARROW;
	case 0x41:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_A : KillerbyteGameEngine::Keyboard::KEY_A;
	case 0x42:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_B : KillerbyteGameEngine::Keyboard::KEY_B;
	case 0x43:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_C : KillerbyteGameEngine::Keyboard::KEY_C;
	case 0x44:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_D : KillerbyteGameEngine::Keyboard::KEY_D;
	case 0x45:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_E : KillerbyteGameEngine::Keyboard::KEY_E;
	case 0x46:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_F : KillerbyteGameEngine::Keyboard::KEY_F;
	case 0x47:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_G : KillerbyteGameEngine::Keyboard::KEY_G;
	case 0x48:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_H : KillerbyteGameEngine::Keyboard::KEY_H;
	case 0x49:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_I : KillerbyteGameEngine::Keyboard::KEY_I;
	case 0x50:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_J : KillerbyteGameEngine::Keyboard::KEY_J;
	case 0x51:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_K : KillerbyteGameEngine::Keyboard::KEY_K;
	case 0x52:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_L : KillerbyteGameEngine::Keyboard::KEY_L;
	case 0x53:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_M : KillerbyteGameEngine::Keyboard::KEY_M;
	case 0x54:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_N : KillerbyteGameEngine::Keyboard::KEY_N;
	case 0x55:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_O : KillerbyteGameEngine::Keyboard::KEY_O;
	case 0x56:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_P : KillerbyteGameEngine::Keyboard::KEY_O;
	case 0x57:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_Q : KillerbyteGameEngine::Keyboard::KEY_Q;
	case 0x58:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_R : KillerbyteGameEngine::Keyboard::KEY_R;
	case 0x59:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_S : KillerbyteGameEngine::Keyboard::KEY_S;
	case 0x60:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_T : KillerbyteGameEngine::Keyboard::KEY_T;
	case 0x61:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_U : KillerbyteGameEngine::Keyboard::KEY_U;
	case 0x62:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_V : KillerbyteGameEngine::Keyboard::KEY_V;
	case 0x63:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_W : KillerbyteGameEngine::Keyboard::KEY_W;
	case 0x64:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_X : KillerbyteGameEngine::Keyboard::KEY_X;
	case 0x65:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_Y : KillerbyteGameEngine::Keyboard::KEY_Y;
	case 0x66:
		return shiftKeyDown ? KillerbyteGameEngine::Keyboard::KEY_CAP_Z : KillerbyteGameEngine::Keyboard::KEY_Z;
	default:
		return KillerbyteGameEngine::Keyboard::KEY_NONE;
	}
}

// Message Handler for Win32. Essentially, all input is handled here
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static KillerbyteGameEngine::Game* game = KillerbyteGameEngine::Game::GetInstance();

	// If the game is not running then we won't handle those messages
	if (!game->GetState() != KillerbyteGameEngine::Game::UNINITIALIZED)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	static bool shiftDown = false;
	static bool capsOn = false;

	switch (msg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			if (wParam == VK_SHIFT || wParam == VK_LSHIFT || wParam == VK_RSHIFT)
			{
				shiftDown = true;
			}

			if (wParam == VK_CAPITAL)
			{
				capsOn = !capsOn;
			}

			// There are no key repeats
			//if ((lParam & 0x40000000) == 0)
			//{
			//	KillerbyteGameEngine::Platform::KeyEvent(KillerbyteGameEngine::Keyboard::KEY_DOWN, getKey(wParam, shiftDown ^ capsOn));
			//}

			KillerbyteGameEngine::Platform::KeyEvent(KillerbyteGameEngine::Keyboard::KEY_DOWN, getKey(wParam, shiftDown ^ capsOn));

			break;

		case WM_KEYUP:
			if (wParam == VK_SHIFT || wParam == VK_LSHIFT || wParam == VK_RSHIFT)
			{
				shiftDown = true;
			}

			KillerbyteGameEngine::Platform::KeyEvent(KillerbyteGameEngine::Keyboard::KEY_UP, getKey(wParam, shiftDown & capsOn));

			break;

		case WM_CHAR:
			// There are no key repeats
			if ((lParam & 0x40000000) == 0)
			{
				KillerbyteGameEngine::Platform::KeyEvent(KillerbyteGameEngine::Keyboard::KEY_DOWN, wParam);
			}

			break;

		case WM_UNICHAR:
			// There are no key repeats
			if ((lParam & 0x40000000) == 0)
			{
				KillerbyteGameEngine::Platform::KeyEvent(KillerbyteGameEngine::Keyboard::KEY_DOWN, wParam);
			}

			break;

		case WM_SIZE:
			KillerbyteGameEngine::Platform::ResizeEvent((unsigned int)(short)LOWORD(lParam), (unsigned int)(short)HIWORD(lParam));
			break;

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