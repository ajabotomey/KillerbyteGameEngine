#include "Base.h"
#include "Platform.h"

// All Platform Independent code goes here

namespace KillerbyteGameEngine
{
	Platform::Platform(Game* game)
	{
		gameInstance = game;
	}

	void Platform::ResizeEvent(unsigned int width, unsigned int height)
	{
		Game* game = Game::GetInstance();

		if (game->width != width || game->height != height)
		{
			game->width = width;
			game->height = height;
		}

		glViewport(0, 0, width, height);
	}

	void Platform::KeyEvent(Keyboard::KeyEvent evt, int key)
	{
		Game::GetInstance()->KeyEvent(evt, key);
	}
}