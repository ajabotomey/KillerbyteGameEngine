#ifndef TEXTURE_H
#define TEXTURE_H

#include "Base.h"
#include "Object.h"
#include "Image.h"

namespace KillerbyteGameEngine
{
	class Texture : public Object
	{
	public:
		Texture();
		~Texture();

		bool LoadTextureFromFile(const char* filename);
		inline GLuint GetTextureHandle() { return textureHandle; }
	private:

		GLuint textureHandle;
	};
}

#endif