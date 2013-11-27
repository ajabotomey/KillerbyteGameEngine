#include "Platform.h"

using namespace KillerbyteGameEngine;

int main(int argc, char *argv[])
{
	Game* game = Game::GetInstance();
	Platform platform(game);
	
	platform.Initialize(game);
	platform.Run();
	platform.Shutdown();
	
	return 0;
}