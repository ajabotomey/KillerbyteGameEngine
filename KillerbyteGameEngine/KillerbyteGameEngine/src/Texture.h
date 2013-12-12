#ifndef TEXTURE_H
#define TEXTURE_H

#include "Base.h"
#include "Object.h"

namespace KillerbyteGameEngine
{
	class Texture : public Object
	{
	public:
		Texture();
		~Texture();

		bool LoadTextureFromFile(const char* filename);
	private:
		void createTexture();

		GLuint textureHandle;
	};
}

#endif