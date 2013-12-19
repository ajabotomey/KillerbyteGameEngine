// I need to shorten this main loop and throw a lot of this code into the Win32 Platform class
#include "Platform/Platform.h" // Will be a header file that contains all the headers files required

#ifndef _WINDOWS_
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

using namespace KillerbyteGameEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Game* game = Game::GetInstance();
	Platform platform(game);

	platform.Initialize(game);
	platform.Run();
	platform.Shutdown();

	return 0;
}