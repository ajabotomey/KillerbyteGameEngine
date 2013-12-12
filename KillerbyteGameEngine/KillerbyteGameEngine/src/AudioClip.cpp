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
		char* data = new char[size];
		result = Read(data, sizeof(char), size);

		fclose(file);

		return data;
	}
}