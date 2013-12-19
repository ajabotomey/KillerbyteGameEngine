// Base class for all resources

#ifndef FILE_H
#define FILE_H

#include <cstdio>
#include <string>

namespace KillerbyteGameEngine
{
#ifdef __ANDROID__
	struct FileDescriptor
	{
		int32_t descriptor;
		off_t start;
		off_t length;
	};
#endif

	class File
	{
	public:
		File();
		~File();

		FILE* Open(const char* filename, const char* mode);
		size_t Read(void* ptr, size_t size, size_t count);
		char* ReadLine(char* str, int num);
		
		bool DoesExist();
		void CloseFile();

		inline FILE* GetCFile() { return file; }

	protected:
		FILE* file;

	private:		
#ifdef __ANDROID__
		std::string ConvertAssetToFile(const char* filename);
		void Descript(const char* filename, int32_t& descriptor, off_t& start, off_t& length);
#endif
	
	private:
		std::string fullPath;
		bool readable;
		bool writable;
	};
}

#endif