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
		void OpenClip(const char* filename);

		
		inline char* GetData() { return data; }

#ifndef __ANDROID__
		void SetupALClip(int channel, int sampleRate, int bps, int size);
		inline ALuint GetSource() { return source; }
#else
		void SetupSLClip(int size);
		inline off_t GetLength() { return length; }
#endif
	private:
		char* data;
		std::string name;	

#ifndef __ANDROID__
		ALuint buffer;
		ALuint source;
#else
		off_t length;
#endif
	};
}

#endif