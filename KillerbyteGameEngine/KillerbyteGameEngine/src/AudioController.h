// This class will essentially control the audio for the entire engine.
// We will have access to two sound API's - OpenSL for Android and OpenAL for the remaining platforms
// This class will also hold the ability to play, pause and stop sounds rather than the AudioClip

#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include "Base.h"
#include "AudioClip.h"

namespace KillerbyteGameEngine
{
#ifndef __ANDROID__
	struct ALSound
	{
		ALuint buffer;
		ALuint source;
		std::string name;
	};
#else
	struct SLSound
	{
		char* bufferData;
		off_t length;
		std::string name;
	};
#endif

	class AudioController
	{
	public:
		AudioController();
		~AudioController();

		void Initialize();
		void Shutdown();

		void LoadClip(const char* filename, bool looping = false);
		void PlayClip(std::string name);
		void PauseClip(std::string name);
		void StopClip(std::string name);

		void PlayChunk();
		void PauseChunk();
		void StopChunk();
	private:
#ifndef __ANDROID__
		void InitializeAL();
		void ShutdownAL();
		
		void LoadALClip(const char* filename, bool looping = false);
		
		void PlayALClip(std::string name);
		void PauseALClip(std::string name);
		void StopALClip(std::string name);
		
		void PlayALChunk();
		void PauseALChunk();
		void StopALChunk();
#else
		void InitializeSL();
		bool StartBGMPlayer();
		bool StartSoundPlayer();
		void ShutdownSL();
				
		void LoadSLClip(const char* filename, bool looping = false);
		
		void PlaySLClip(std::string name);
		void PauseSLClip(std::string name);
		void StopSLClip(std::string name);
		void PlaySLChunk();
		void PauseSLChunk();
		void StopSLChunk();
#endif

	private:

#ifdef __ANDROID__
		// OpenSL Engine
		SLObjectItf engineObj;
		SLEngineItf engine;

		// Audio Output
		SLObjectItf outputMix;

		// Error checking
		SLresult result;

		// Background music player
		SLObjectItf bgmPlayerObj;
		SLPlayItf bgmPlayer;
		SLSeekItf bgmPlayerSeek;

		// Sound Player
		SLObjectItf playerObj;
		SLPlayItf player;
		SLBufferQueueItf playerQueue;

		std::vector<SLSound> sounds;
#else
		ALCdevice* device;
		ALCcontext* context;

		std::vector<ALSound> sounds;
#endif
	};
}

#endif