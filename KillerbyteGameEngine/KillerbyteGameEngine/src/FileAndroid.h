#ifndef FILEANDROID_H
#define FILEANDROID_H

#ifdef __ANDROID__

namespace KillerbyteGameEngine
{
	class FileAndroid
	{
	public:
		~FileAndroid();
		FileAndroid* open(AAssetManager* assetManager, const char* filePath);
		void Close();
		size_t Length();
		inline void GetAsset() { return asset; }
	private:
		FileAndroid(AAsset* newAsset);
		
	private:
		AAsset* asset;
	};
}

#endif

#endif