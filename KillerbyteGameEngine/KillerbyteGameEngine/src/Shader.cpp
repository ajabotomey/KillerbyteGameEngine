#include "Shader.h"

namespace KillerbyteGameEngine
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}

	bool Shader::LoadFromFile(const char* vertexPath, const char* fragmentPath)
	{
		// Open the vertex shader and check if file exists
		std::ifstream vertexIn(vertexPath);
		if (!vertexIn.good())
		{
			// Log the error
			return false;
		}
		
		// Open the fragment shader and check if file exists
		std::ifstream fragmentIn(fragmentPath);
		if (!fragmentIn.good())
		{
			// Log the error
			return false;
		}

		// Create the shader program
		if (program <= 0)
		{
			program = glCreateProgram();
			if (program == 0)
			{
				// Log the error
				return false;
			}
		}

		// Read in the vertex shader code and then close the vertex file stream
		std::ostringstream vertexCode;
		while (vertexIn.good())
		{
			int c = vertexIn.get();
			if (!vertexIn.eof())
			{
				vertexCode << (char)c;
			}
		}

		vertexIn.close();

		// Read in the fragment shader code and then close the fragment file stream
		std::ostringstream fragmentCode;
		while (fragmentIn.good())
		{
			int c = fragmentIn.get();
			if (!fragmentIn.eof())
			{
				fragmentCode << (char)c;
			}
		}

		fragmentIn.close();

		return LoadFromSource(vertexCode.str().c_str(), fragmentCode.str().c_str());
	}

	bool Shader::LoadFromSource(const char* vertexSource, const char* fragmentSource)
	{
		GLuint vertexHandle = 0, fragmentHandle = 0;

		// Compile the vertex shader
		vertexHandle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexHandle, 1, &vertexSource, NULL);
		glCompileShader(vertexHandle);

		// Now check for errors
		int compileResult;
		glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &compileResult);
		if (compileResult == GL_FALSE)
		{
			// We log the error here
			int length = 0;
			std::string logString = "";
			glGetShaderiv(vertexHandle, GL_INFO_LOG_LENGTH, &length);
			if (length > 0)
			{
				char* c_log = new char[length];
				int written = 0;
				glGetShaderInfoLog(vertexHandle, length, &written, c_log);
				logString = c_log;
				// Log logString here
				delete[] c_log;
				c_log = NULL;
			}

			return false;
		}

		// Now repeat for the fragment shader
		fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentHandle, 1, &fragmentSource, NULL);
		glCompileShader(fragmentHandle);

		// Now check for errors
		glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &compileResult);
		if (compileResult == GL_FALSE)
		{
			// We log the error here
			int length = 0;
			std::string logString = "";
			glGetShaderiv(fragmentHandle, GL_INFO_LOG_LENGTH, &length);
			if (length > 0)
			{
				char* c_log = new char[length];
				int written = 0;
				glGetShaderInfoLog(fragmentHandle, length, &written, c_log);
				logString = c_log;
				// Log logString here
				delete[] c_log;
				c_log = NULL;
			}

			return false;
		}

		// Create the shader program if program doesn't already exist
		if (program <= 0)
		{
			program = glCreateProgram();
			if (program == 0)
			{
				// Log the error
				return false;
			}
		}

		// Attach the both shaders to the program
		glAttachShader(program, vertexHandle);
		glAttachShader(program, fragmentHandle);

		return true;
	}

	bool Shader::Link()
	{
		if (linked)
		{
			// No need to continue, the program has already been linked
			return true;
		}

		if (program <= 0)
		{
			// Log error here
			return false;
		}

		glLinkProgram(program);

		int status = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			// Error statement here
			return false;
		}

		linked = true;
		return true;
	}

	void Shader::Use()
	{
		if (program <= 0 || (!linked))
		{
			return;
		}

		glUseProgram(program);
	}

	void Shader::Stop()
	{
		glUseProgram(0);
	}
}