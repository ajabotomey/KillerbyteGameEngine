#ifndef TESTTRIANGLE_H
#define TESTTRIANGLE_H

#include "KillerbyteGameEngine.h"

using namespace KillerbyteGameEngine;

class TestTriangle : public Game
{
public:
	TestTriangle();

	// Have various input events here

protected:
	void Initialize();
	void Finalize();
	void Update(float elapsedTime);
	void Render(float elapsedTime);

private: // Methods
	GLuint LoadShader(GLenum type, const char* source);
	void InitRectangle(); // These will eventually be in its own object but for now, we use these to demo 
	void DrawRectangle(); // that we can display VBO objects

private: // Variables
	GLuint program;
	Matrix44 projMatrix;
	Matrix44 mvMatrix;
	Matrix44 mvpMatrix;
	GLint mvpMatrixHandle;

	GLuint rectangleInfo[2];
	Shader shader;
};

#endif