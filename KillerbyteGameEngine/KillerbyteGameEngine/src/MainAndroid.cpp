#include <android_native_app_glue.h>
#include "KillerbyteGameEngine.h"

using namespace KillerbyteGameEngine;

extern struct android_app* app;

void android_main(struct android_app* state)
{
	app_dummy();
	
	app = state;
	Game* game = Game::GetInstance();
	Platform platform(game);

	platform.Run();
	platform.Shutdown();
}
