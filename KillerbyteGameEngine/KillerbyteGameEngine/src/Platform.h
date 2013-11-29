#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "Keyboard.h"

namespace KillerbyteGameEngine
{
	class Game;
  
	class Platform
	{
		// Platform Dependent
	public:
		friend class Game;

		~Platform();

		static void Initialize(Game* game);
		
		void Run();
		void Shutdown();
	private:
		static unsigned int getDisplayWidth();
		static unsigned int getDisplayHeight();
		static double GetAbsoluteTime();
		static void SetAbsoluteTime(double time);

		// Platform Independent
	public:
		Platform(Game* game);
		
		static void ResizeEvent(unsigned int width, unsigned int height);
		static void KeyEvent(Keyboard::KeyEvent evt, int key);
	private:
		Game* gameInstance;
	};
	
}

#include "Game.h"

#endif