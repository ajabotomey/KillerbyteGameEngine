#include "Base.h"
#include "Game.h"
#include "Platform/Platform.h"

namespace KillerbyteGameEngine
{
	static Game* instance = NULL; // This is the instance of our game that we will refer to

	Game::Game()
	{
		initialized = false;
		instance = this;
		camera = new Camera();
		audioController = NULL;
	}

	Game::~Game()
	{
		
	}

	Game* Game::GetInstance()
	{
		return instance;
	}

	int Game::Run()
	{
		if (state != UNINITIALIZED)
		{
			return -1;
		}

		// Load all the config settings for the game

		// Get the width and height from the platform class
		width = Platform::getDisplayWidth();
		height = Platform::getDisplayHeight();

		// start game
		if (!Startup())
		{
			Shutdown();
			return -1;
		}

		return 0;
	}

	bool Game::Startup()
	{
		if (state != UNINITIALIZED)
		{
			return false;
		}

		glEnable(GL_TEXTURE_2D);

		glViewport(0, 0, width, height);

		audioController = new AudioController();
		audioController->Initialize();

		state = RUNNING;

		return true;
	}

	void Game::Shutdown()
	{
		if (state != UNINITIALIZED)
		{
			Finalize();

			// Shutdown the Render State
			// Shutdown the Frame Buffer

			state = UNINITIALIZED;
		}
	}

	void Game::Frame()
	{
		if (!initialized)
		{
			Initialize();
			initialized = true;
		}

		static double lastFrameTime = Game::GetGameTime();
		double frameTime = GetGameTime();

		if (state == Game::RUNNING)
		{
			// Update Time.
			float elapsedTime = (frameTime - lastFrameTime);
			lastFrameTime = frameTime;

			// Application Update.
			Update(elapsedTime);

			// Graphics Rendering.
			Render(elapsedTime);

			// Update FPS.
			++frameCount;
			if ((Game::GetGameTime() - frameLastFPS) >= 1000)
			{
				frameRate = frameCount;
				frameCount = 0;
				frameLastFPS = GetGameTime();
			}
		}
	}

	double Game::GetGameTime()
	{
		// Get the time from platform and subtract the amount of pause time
		// At this stage, there is no pause time
		return Platform::GetAbsoluteTime();
	}

	Game::State Game::GetState() const
	{
		return state;
	}

	unsigned int Game::GetWidth() const
	{
		return width;
	}

	unsigned int Game::GetHeight() const
	{
		return height;
	}

	void Game::KeyEvent(Keyboard::KeyEvent evt, int key)
	{

	}
}