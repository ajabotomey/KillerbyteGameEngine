#include "File.h"
#include "Base.h"
#include "FileSystem.h"

#ifdef __ANDROID__
#include <android/asset_manager.h>
extern AAssetManager* assetManager;
#endif

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <direct.h>
#define gp_stat _stat
#define gp_stat_struct struct stat
#else
#define __EXT_POSIX2
#include <libgen.h>
#include <dirent.h>
#define gp_stat stat
#define gp_stat_struct struct stat
#endif

namespace KillerbyteGameEngine
{
#ifdef __ANDROID__
	static void makepath(std::string path, int mode)
	{
		std::vector<std::string> dirs;
		while (path.length() > 0)
		{
			int index = path.find('/');
			std::string dir = (index == -1) ? path : path.substr(0, index);
			if (dir.length() > 0)
			{
				dirs.push_back(dir);
			}

			if (index + 1 >= path.length() || index == -1)
				break;

			path = path.substr(index + 1);
		}

		struct stat s;
		std::string dirPath;
		for (unsigned int i = 0; i < dirs.size(); i++)
		{
			dirPath += "/";
			dirPath += dirs[i];
			if (stat(dirPath.c_str(), &s) != 0)
			{
				if (mkdir(dirPath.c_str(), 0777) != 0)
				{
					LOGI("Error while creating directory");
					return;
				}
			}
		}

		return;
	}

#endif

	File::File()
	{
		file = NULL;
	}

	File::~File()
	{
		if (file)
			CloseFile();

		file = NULL;
	}

	FILE* File::Open(const char* filename, const char* fileMode)
	{
		// If android, run asset to file conversion and return file
#ifndef __ANDROID__
		file = fopen(filename, fileMode);
#else
		ConvertAssetToFile(filename);
#endif

		return file;
	}

	size_t File::Read(void* ptr, size_t size, size_t count)
	{
		if (!file)
			return 0;

		return fread(ptr, size, count, file);
	}

	char* File::ReadLine(char* str, int num)
	{
		if (!file)
			return 0;

		return fgets(str, num, file);
	}

	bool File::DoesExist()
	{
		if (file)
		{
			return true;
		}

		return false;
	}

	void File::CloseFile()
	{
		fclose(file);
	}

#ifdef __ANDROID__
	std::string File::ConvertAssetToFile(const char* fileName)
	{
		LOGI("File path: %s", fileName);
		LOGI("Resource path: %s", FileSystem::GetResourcePath());

		fullPath = FileSystem::GetResourcePath();
		fullPath += fileName;
		LOGI("Full file path: %s", fullPath.c_str());

		std::string directoryPath = fullPath.substr(0, fullPath.rfind("/"));
		struct stat s;
		if (stat(directoryPath.c_str(), &s) != 0)
			makepath(directoryPath, 0777);

		std::string filePath = fullPath.substr(fullPath.rfind("/") + 1, fullPath.length() - 1);
		LOGI("File name is: %s", filePath.c_str());

		//AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_BUFFER);
		AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_UNKNOWN);
		if (asset == NULL)
		{
			LOGI("Asset won't open");
		}

		LOGI("Asset open");

		file = fopen(fullPath.c_str(), "wb");
		if (file == NULL)
		{
			LOGI("File won't open");
		}

		LOGI("File open");

		//char* assetBuffer = (char*)AAsset_getBuffer(asset);
		//LOGI("Asset Buffer is %s", assetBuffer);
		size_t length = AAsset_getLength(asset);

		LOGI("Length of the file is %d", length);

		//char* buffer = (char*) malloc(length);
		//void* buffer = (void*) malloc(length);

		//int count = AAsset_read(asset, buffer, length); // Why isn't buffer being read properly

		//LOGI("Count is %d", count);
		//LOGI("Buffer: %s\n", buffer); // Why is it crashing when I print the buffer

		char* buffer = (char*) malloc(sizeof(char) * length);

		int count;
		while ((count = AAsset_read(asset, buffer, length)) > 0)
		{
			fwrite(buffer, count, length, file);
		}

		//fwrite(buffer, sizeof(char) * length, length, file);
		//while ((count = AAsset_read(asset, buffer, length)) > 0)
		//{
			//fwrite(buffer, count, length, file);
		//}
		
		//if (assetManager)
		//{
		//	LOGI("Yay! We have a asset manager!");
		//}

		//AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_STREAMING);
		//char buf[BUFFER_SIZE];
		//int nb_read = 0;
		
		//if (asset)
		//{
		//	LOGI("Asset is open");
		//	const void* data = AAsset_getBuffer(asset);
		//	int length = AAsset_getLength(asset);

		//	LOGI("buffer and length retrieved");

		//	file = fopen(fullPath.c_str(), "w");

			/*while ((nb_read = AAsset_read(asset, buf, BUFFER_SIZE)) > 0)
			{
			fwrite(buf, nb_read, BUFFER_SIZE, file);
			}*/

			//LOGI("The length of the file is %d", length);

			//if (file != NULL)
			//{
			//	LOGI("File is open");
			//	int result = fwrite(data, sizeof(unsigned char), length, file);

			//	if (fclose(file) != 0)
			//	{
			//		LOGI("Failed to close the replica file");
			//	}

			//	if (result != length)
			//	{
			//		LOGI("Failed to write all the data from the apk to the file");
			//	}
			//}
			//else
			//{
			//	LOGI("Failed to open file");
			//}

			//delete data;
			//data = NULL;
		//}

		free(buffer);
		buffer = NULL;

		AAsset_close(asset);

		return fullPath;
	}
#endif

#ifdef __ANDROID__
	void File::Descript(const char* filename, int32_t& descriptor, off_t& start, off_t& length)
	{
		AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_UNKNOWN);
		if (asset != NULL)
		{
			descriptor = AAsset_openFileDescriptor(asset, &start, &length);
		}
	}
#endif
}