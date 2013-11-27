#ifndef SHADER_H
#define SHADER_H

// This simply represents a basic shader program for now. 
// Eventually, we will have the ability to add textures to this object allowing for textured objects

// TODO: Figure out a way of storing the vertex attributes as well as the uniform parameters

#include "Base.h"
#include "Object.h"

namespace KillerbyteGameEngine
{
	class Shader : public Object
	{
	public:
		Shader();
		~Shader();

		bool LoadFromFile(const char* vertexPath, const char* fragmentPath);
		bool LoadFromSource(const char* vertexSource, const char* fragmentSource);
		bool Link();
		void Use();
		void Stop();

		inline GLuint GetProgram() { return program; }
	private:
		GLuint program;
		bool linked;
	};
}

#endif