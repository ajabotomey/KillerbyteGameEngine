#include "Texture.h"

namespace KillerbyteGameEngine
{
	Texture::Texture()
	{

	}

	Texture::~Texture()
	{

	}

	bool Texture::LoadTextureFromFile(const char* filename)
	{
		Image image;
		image.LoadPNGImage(filename);

		glGenTextures(1, &textureHandle);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)image.GetData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return true;
	}
}