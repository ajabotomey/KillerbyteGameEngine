#include "AudioClip.h"

namespace KillerbyteGameEngine
{
	bool IsBigEndian()
	{
		int a = 1;
		return !((char*)&a)[0];
	}

	int ConvertToInt(char* buffer, int length)
	{
		int a = 0; 
		if (!IsBigEndian())
		{
			for (int i = 0; i < length; i++)
			{
				((char*)&a)[i] = buffer[i];
			}
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				((char*)&a)[3 - i] = buffer[i];
			}
		}

		return a;
	}

	AudioClip::AudioClip()
	{
		
	}

	AudioClip::~AudioClip()
	{

	}

	// Start by loading the header info
	char* AudioClip::OpenClip(const char* filename, int& channel, int& sampleRate, int& bps, int& size)
	{
		//wavFile = new WavFile;

		char fileBuffer[4];
		size_t result;

		file = Open(filename, "rb");

		result = Read(fileBuffer, 1, 4); // RIFF
		// Check that it reads RIFF
		result = Read(fileBuffer, 1, 4);
		result = Read(fileBuffer, 1, 4); // WAVE
		result = Read(fileBuffer, 1, 4); // fmt
		result = Read(fileBuffer, 1, 4); // 16 bit
		result = Read(fileBuffer, 1, 2); // Audio Format, should be 1
		result = Read(fileBuffer, 1, 2); // Channels
		channel = ConvertToInt(fileBuffer, 2);

		result = Read(fileBuffer, 1, 4); // Sample rate
		sampleRate = ConvertToInt(fileBuffer, 4);

		result = Read(fileBuffer, 1, 4);
		result = Read(fileBuffer, 1, 2);
		result = Read(fileBuffer, 1, 2); // Bits per sample
		bps = ConvertToInt(fileBuffer, 2);

		result = Read(fileBuffer, 1, 4); // data
		result = Read(fileBuffer, 1, 4); // size
		size = ConvertToInt(fileBuffer, 4);

		data = new char[size];
		result = Read(data, sizeof(char), size);

		fclose(file);

		return data;
	}

	void AudioClip::OpenClip(const char* filename)
	{
		int channel, sampleRate, bps, size;
		char fileBuffer[4];
		size_t result;

		file = Open(filename, "rb");

		result = Read(fileBuffer, 1, 4); // RIFF
		// Check that it reads RIFF
		result = Read(fileBuffer, 1, 4);
		result = Read(fileBuffer, 1, 4); // WAVE
		result = Read(fileBuffer, 1, 4); // fmt
		result = Read(fileBuffer, 1, 4); // 16 bit
		result = Read(fileBuffer, 1, 2); // Audio Format, should be 1
		result = Read(fileBuffer, 1, 2); // Channels
		channel = ConvertToInt(fileBuffer, 2);

		result = Read(fileBuffer, 1, 4); // Sample rate
		sampleRate = ConvertToInt(fileBuffer, 4);

		result = Read(fileBuffer, 1, 4);
		result = Read(fileBuffer, 1, 2);
		result = Read(fileBuffer, 1, 2); // Bits per sample
		bps = ConvertToInt(fileBuffer, 2);

		result = Read(fileBuffer, 1, 4); // data
		result = Read(fileBuffer, 1, 4); // size
		size = ConvertToInt(fileBuffer, 4);

		data = new char[size];
		result = Read(data, sizeof(char), size);

		fclose(file);

		// Get the name of the file
		std::string fullPath = filename;
		std::string filePath = fullPath.substr(fullPath.rfind("/") + 1, fullPath.length() - 1);
		name = filePath;

#ifdef __ANDROID__
		SetupSLClip(size);
#else
		SetupALClip(channel, sampleRate, bps, size);
#endif
	}

#ifdef __ANDROID__
	void AudioClip::SetupSLClip(int size)
	{
		length = (off_t)size;

		LOGI("Buffer data: %s", data);
		LOGI("File Length: %d", size);
	}
#else
	void AudioClip::SetupALClip(int channel, int sampleRate, int bps, int size)
	{
		// Now create the OpenAL data
		ALuint format;
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
	}
#endif
}