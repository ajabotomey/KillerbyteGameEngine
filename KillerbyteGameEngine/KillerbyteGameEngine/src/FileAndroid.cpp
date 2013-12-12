#ifdef __ANDROID__

#include "FileAndroid.h"

namespace KillerbyteGameEngine
{
	FileAndroid::FileAndroid(AAsset* newAsset)
	{
		asset = newAsset;
	}

	FileAndroid* FileAndroid::Open(AAssetManager* assetManager, const char* filename)
	{
		AAsset* newAsset = AAssetManager_open(assetManager, filePath, AASSET_MODE_RANDOM);
		if (newAsset == STATUS_OK)
		{
			FileAndroid* file = new FileAndroid(newAsset);
			return file;
		}
		
		return NULL;
	}
	
	void FileAndroid::Close()
	{
		if (asset != NULL)
		{
			AAsset_close(asset);
			asset = NULL;
		}
	}
	
	size_t FileAndroid::Length()
	{
		return (size_t)AAsset_getLength(asset);
	}
}

#endif