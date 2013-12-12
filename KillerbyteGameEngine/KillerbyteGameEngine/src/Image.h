#ifndef IMAGE_H
#define IMAGE_H

#include "Object.h"

namespace KillerbyteGameEngine
{
	class Image
	{
	public:
		enum ImageFormat
		{
			RGB,
			RGBA
		};

		Image();
		~Image();

		void LoadImage(const char* filename);

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