// Class to hold image data

#ifndef IMAGE_H
#define IMAGE_H

#include "Base.h"
#include "File.h"

namespace KillerbyteGameEngine
{
	class Image : public File
	{
	public:
		enum ImageFormat
		{
			RGB,
			RGBA
		};

		Image();
		~Image();

		bool LoadPNGImage(const char* filename);
		inline void ReleaseData() { delete[] data; data = NULL; }
		inline unsigned char* GetData() { return data; }
		inline unsigned int GetWidth() const { return width; }
		inline unsigned int GetHeight() const { return height; }
	private:
		unsigned char* data;
		ImageFormat format;
		unsigned int width;
		unsigned int height;
	};
}

#endif