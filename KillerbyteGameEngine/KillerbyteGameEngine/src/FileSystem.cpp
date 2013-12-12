#include "FileSystem.h"

namespace KillerbyteGameEngine
{
	static FileSystem* instance = NULL;
	static std::string resourcePath = "";

	FileSystem::FileSystem()
	{
		instance = this;
	}

	FileSystem* FileSystem::GetInstance()
	{
		return instance;
	}

	void FileSystem::SetResourcePath(const char* path)
	{
		resourcePath = path;
	}

	const char* FileSystem::GetResourcePath()
	{
		return resourcePath.c_str();
	}

//	FILE* FileSystem::OpenFile(const char* filename, const char* mode)
//	{
//		std::string fullPath;
//		fullPath = resourcePath.append(filename);
//		FILE* file;
//
//#ifndef __ANDROID__
//		//file = fopen(fullPath.c_str(), mode);
//#else
//		FileAndroid* file = new FileAndroid(assetManager, fullPath);
//		// convert the asset into a FILE
//#endif
//
//	}
}