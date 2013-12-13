#include "AudioController.h"

namespace KillerbyteGameEngine
{
	AudioController::AudioController()
	{
		
	}

	AudioController::~AudioController()
	{

	}

	void AudioController::Initialize()
	{
#ifdef __ANDROID__
		InitializeSL();
#else
		InitializeAL();
#endif
	}

	void AudioController::Shutdown()
	{
#ifdef __ANDROID__
		ShutdownSL();
#else
		ShutdownAL();
#endif
	}

	void AudioController::LoadClip(const char* filename, bool looping)
	{
#ifdef __ANDROID__
		LoadSLClip(filename);
#else
		LoadALClip(filename);
#endif
	}

	void AudioController::PlayClip(std::string name)
	{
#ifdef __ANDROID__
		PlaySLClip(name);
#else
		PlayALClip(name);
#endif
	}

	void AudioController::PauseClip(std::string name)
	{
#ifdef __ANDROID__
		PauseSLClip(name);
#else
		PauseALClip(name);
#endif
	}

	void AudioController::StopClip(std::string name)
	{
#ifdef __ANDROID__
		StopSLClip(name);
#else
		StopALClip(name);
#endif
	}

#ifndef __ANDROID__
	void AudioController::InitializeAL()
	{
		device = alcOpenDevice(NULL);
		if (!device)
		{
			// log error
			return;
		}

		context = alcCreateContext(device, NULL);
		if (!context)
		{
			// log error
			return;
		}

		alcMakeContextCurrent(context);
	}

	void AudioController::ShutdownAL()
	{
		alcDestroyContext(context);
		context = NULL;

		alcCloseDevice(device);
		device = NULL;
	}

	void AudioController::LoadALClip(const char* filename, bool looping)
	{
		AudioClip clip;
		int channel, sampleRate, bps, size;
		char* data = clip.OpenClip(filename, channel, sampleRate, bps, size);
		ALuint buffer, source, format;
		alGenBuffers(1, &buffer);

		// Check what format our wav file is
		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		alBufferData(buffer, format, data, size, sampleRate);

		// Set up the source
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, buffer);
		alSource3f(source, AL_POSITION, 0, 0, 0);
		alSourcei(source, AL_LOOPING, AL_TRUE);

		// Setup the listener
		float f[] = { 1, 0, 0, 0, 1, 0 };
		float p[] = { 0, 0, 0 };
		alListenerfv(AL_ORIENTATION, f);
		alListenerfv(AL_POSITION, p);
		alListenerfv(AL_VELOCITY, p);

		ALSound sound;

		sound.buffer = buffer;
		sound.source = source;
		sound.name = filename;

		alSounds.push_back(sound);
	}

	void AudioController::PlayALClip(std::string name)
	{
		ALuint source, buffer;

		// Iterate through the sounds vector until the name matches
		for (std::vector<ALSound>::iterator i = alSounds.begin(); i != alSounds.end(); i++)
		{
			if ((*i).name == name)
			{
				source = (*i).source;
				buffer = (*i).buffer;
				break;
			}
		}

		alSourcePlay(source);
	}

	void AudioController::PauseALClip(std::string name)
	{
		ALuint source, buffer;

		// Iterate through the sounds vector until the name matches
		for (std::vector<ALSound>::iterator i = alSounds.begin(); i != alSounds.end(); i++)
		{
			if ((*i).name == name)
			{
				source = (*i).source;
				buffer = (*i).buffer;
				break;
			}
		}

		alSourcePause(source);
	}

	void AudioController::StopALClip(std::string name)
	{
		ALuint source, buffer;

		// Iterate through the sounds vector until the name matches
		for (std::vector<ALSound>::iterator i = alSounds.begin(); i != alSounds.end(); i++)
		{
			if ((*i).name == name)
			{
				source = (*i).source;
				buffer = (*i).buffer;
				break;
			}
		}

		alSourceStop(source);
	}
#else
	void AudioController::InitializeSL()
	{
		const SLuint32 engineMixIIDCount = 1;
		const SLInterfaceID engineMixIIDs[] = { SL_IID_ENGINE };
		const SLboolean engineMixReqs[] = { SL_BOOLEAN_TRUE };
		const SLuint32 outputMixIIDCount = 0;
		const SLInterfaceID outputMixIIDs[] = {};
		const SLboolean outputMixReqs[] = {};

		// Create the OpenSL ES Engine
		result = slCreateEngine(&engineObj, 0, NULL, engineMixIIDCount, engineMixIIDs, engineMixReqs);
		if (result != SL_RESULT_SUCCESS)
		{

		}
		result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS)
		{

		}
		result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);
		if (result != SL_RESULT_SUCCESS)
		{

		}

		// Create the output
		result = (*engine)->CreateOutputMix(engine, &outputMix, outputMixIIDCount, outputMixIIDs, outputMixReqs);
		result = (*outputMix)->Realize(outputMix, SL_BOOLEAN_FALSE);

		// Setup the sound player
		if (StartSoundPlayer() == true)
		{

		}

	}

	bool AudioController::StartBGMPlayer()
	{
		
	}

	bool AudioController::StartSoundPlayer()
	{

		SLDataLocator_AndroidSimpleBufferQueue dataIn;
		dataIn.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
		dataIn.numBuffers = 1; // We have only one buffer for now

		SLDataFormat_PCM dataFormat;
		dataFormat.formatType = SL_DATAFORMAT_PCM;
		dataFormat.numChannels = 2; // Allow for possible stereo sound
		dataFormat.samplesPerSec = SL_SAMPLINGRATE_44_1;
		dataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
		dataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
		dataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
		dataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;

		SLDataSource dataSource;
		dataSource.pLocator = &dataIn;
		dataSource.pFormat = &dataFormat;

		SLDataLocator_OutputMix dataOut;
		dataOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
		dataOut.outputMix = outputMix;

		SLDataSink dataSink;
		dataSink.pLocator = &dataOut;
		dataSink.pFormat = NULL;
		
		// Now to create the sound player
		const SLuint32 soundPlayerIIDCount = 2;
		const SLInterfaceID soundPlayerIIDs[] = { SL_IID_PLAY, SL_IID_BUFFERQUEUE };
		const SLboolean soundPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
		
		result = (*engine)->CreateAudioPlayer(engine, &playerObj, &dataSource, &dataSink, soundPlayerIIDCount, soundPlayerIIDs, soundPlayerReqs);
		if (result != SL_RESULT_SUCCESS)
		{
			return false;
		}

		result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS)
		{
			return false;
		}

		// Now get the sound player's interfaces
		result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
		if (result != SL_RESULT_SUCCESS)
		{
			return false;
		}

		result = (*playerObj)->GetInterface(playerObj, SL_IID_BUFFERQUEUE, &playerQueue);
		if (result != SL_RESULT_SUCCESS)
		{
			return false;
		}

		return true;
	}

	void AudioController::ShutdownSL()
	{

	}

	void AudioController::LoadSLClip(const char* filename, bool looping)
	{
		AudioClip clip;
		int channel, sampleRate, bps, size;
		char* bufferData = clip.OpenClip(filename, channel, sampleRate, bps, size);

		SLSound sound;
		sound.bufferData = bufferData;
		sound.length = size;
		sound.name = filename;

		slSounds.push_back(sound); // Here is where it crashes
	}

	void AudioController::PlaySLClip(std::string name)
	{
		SLuint32 playerState;
		(*playerObj)->GetState(playerObj, &playerState);
		char* buffer;
		off_t length;
		if (playerState == SL_OBJECT_STATE_REALIZED)
		{
			for (std::vector<SLSound>::iterator i = slSounds.begin(); i != slSounds.end(); i++)
			{
				if ((*i).name == name)
				{
					buffer = (*i).bufferData;
					length = (*i).length;
					break;
				}
			}

			// Clear the queue of any sounds
			result = (*playerQueue)->Clear(playerQueue);
			if (result != SL_RESULT_SUCCESS)
			{
				return;
			}

			result = (*playerQueue)->Enqueue(playerQueue, buffer, length);
			if (result != SL_RESULT_SUCCESS)
			{
				LOGI("Problem adding the sound to the queue");
				return;
			}

			result = (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
			if (result != SL_RESULT_SUCCESS)
			{
				LOGI("Problem playing the sound");
				return;
			}
		}
	}

	void AudioController::PauseSLClip(std::string name)
	{

	}

	void AudioController::StopSLClip(std::string name)
	{

	}
#endif
}