// Only deal with opening and closing of files at the moment
// Need to figure out how to do file handling for Android and the other platforms

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <cstdio>

namespace KillerbyteGameEngine
{
	class FileSystem
	{
	public:
		enum FileMode
		{
			READ,
			WRITE
		};

		~FileSystem();

		static FileSystem* GetInstance();

		static void SetResourcePath(const char* path);
		static const char* GetResourcePath();
		
		bool FileExists(const char* filename);
		FILE* OpenFile(const char* filename, const char* mode);
	protected:
		FileSystem();

	private:
		//static std::string resourcePath;
	};
}

#endif