// This class is simply an extension of the File class for loading WAV files

#ifndef AUDIOCLIP_H
#define AUDIOCLIP_H

#include "Base.h"
#include "File.h"
#include "Object.h"

namespace KillerbyteGameEngine
{
	class AudioClip : public File
	{
	public:
		AudioClip();
		~AudioClip();

		char* OpenClip(const char* filename, int& channel, int& sampleRate, int& bps, int& size);
	};
}

#endif