#ifndef GAME_H_
#define GAME_H_

namespace KillerbyteGameEngine
{
	class Game
	{
		friend class Platform;

	public:
		// Game State
		enum State
		{
			UNINITIALIZED,
			RUNNING,
			PAUSED
		};

		~Game();
		int Run();
		void Frame();

		State GetState() const;
		static Game* GetInstance();
		static double GetGameTime();

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
	protected:
		Game();
		virtual void Initialize() = 0;
		virtual void Finalize() = 0;
		virtual void Update(float elapsedTime) = 0;
		virtual void Render(float elapsedTime) = 0;
	private: 
		bool Startup();
		void Shutdown();

		State state;
		unsigned int width;
		unsigned int height;
		bool initialized;
		unsigned int frameCount;
		unsigned int frameRate;
		double frameLastFPS;
	};
}

#endif