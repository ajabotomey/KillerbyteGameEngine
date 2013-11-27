#ifndef PLATFORM_H_
#define PLATFORM_H_

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
	private:
		Game* gameInstance;
	};
	
}

#include "Game.h"

#endif