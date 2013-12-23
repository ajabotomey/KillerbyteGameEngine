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

	void AudioController::PlayALClip(std::string name)
	{
		// Find the node with our data
		Node* audioNode = Scene::GetScene()->FindNode(name);
		alSourcePlay((*audioNode->GetAudioClip()).GetSource());
	}

	void AudioController::PauseALClip(std::string name)
	{
		// Find the node with our data
		Node* audioNode = Scene::GetScene()->FindNode(name);
		alSourcePause((*audioNode->GetAudioClip()).GetSource());
	}

	void AudioController::StopALClip(std::string name)
	{
		// Find the node with our data
		Node* audioNode = Scene::GetScene()->FindNode(name);
		alSourceStop((*audioNode->GetAudioClip()).GetSource());
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
			LOGI("Engine could not be created!");
			return;
		}
		result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS)
		{
			LOGI("Engine object could not be realized!");
			return;
		}
		result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);
		if (result != SL_RESULT_SUCCESS)
		{
			LOGI("Engine Interface could not be retrieved!");
			return;
		}

		// Create the output
		result = (*engine)->CreateOutputMix(engine, &outputMix, outputMixIIDCount, outputMixIIDs, outputMixReqs);
		result = (*outputMix)->Realize(outputMix, SL_BOOLEAN_FALSE);

		// Setup the sound player
		if (StartSoundPlayer() != true)
		{
			LOGI("Sound Player could not be started!");
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
		dataFormat.numChannels = 1; // Allow for possible stereo sound
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
			LOGI("Audio Player could not be created!");
			return false;
		}

		result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);
		if (result != SL_RESULT_SUCCESS)
		{
			LOGI("Player Object could not be realized!");
			return false;
		}

		// Now get the sound player's interfaces
		result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
		if (result != SL_RESULT_SUCCESS)
		{
			LOGI("Play Interface could not be retrieved");
			return false;
		}

		result = (*playerObj)->GetInterface(playerObj, SL_IID_BUFFERQUEUE, &playerQueue);
		if (result != SL_RESULT_SUCCESS)
		{
			LOGI("Buffer Queue Interface could not be retrieved!");
			return false;
		}

		return true;
	}

	void AudioController::ShutdownSL()
	{

	}

	void AudioController::PlaySLClip(std::string name)
	{
		LOGI("Hello World!");
		char* buffer;
		off_t length;
		SLuint32 playerState;
		SLuint32 currentPlayState;

		// Search through the scene for our node
		Node* audioNode = Scene::GetScene()->FindNode(name);
		buffer = (*audioNode->GetAudioClip()).GetData();
		length = (*audioNode->GetAudioClip()).GetLength();
		
		result = (*player)->GetPlayState(player, &currentPlayState);
		if (currentPlayState == SL_PLAYSTATE_PAUSED)
		{
			result = (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
			if (result != SL_RESULT_SUCCESS)
			{
				LOGI("Problem playing the sound");
				return;
			}

			return;
		}

		(*playerObj)->GetState(playerObj, &playerState);
		if (playerState == SL_OBJECT_STATE_REALIZED)
		{
			LOGI("Buffer Data: %s", buffer);
			LOGI("File Length: %d", (int)length);

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
		result = (*player)->SetPlayState(player, SL_PLAYSTATE_PAUSED);
		if (result != SL_RESULT_SUCCESS)
		{
			LOGI("Problem playing the sound");
			return;
		}
	}

	void AudioController::StopSLClip(std::string name)
	{
		result = (*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);
		if (result != SL_RESULT_SUCCESS)
		{
			LOGI("Problem playing the sound");
			return;
		}
	}
#endif
}