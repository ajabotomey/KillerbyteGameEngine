#include "TestTriangle.h"

TestTriangle game;

GLfloat vVertices[] =
{
	0.5f,  -1.0f, 0.0f,
	0.5f, 1.0f, 0.0f,
	-0.5f, 1.0f, 0.0f,
	-0.5f, -1.0f, 0.0f
};

GLubyte vIndices[] =
{
	0, 1, 2,
	2, 3, 0
};

TestTriangle::TestTriangle()
{

}

void TestTriangle::Initialize()
{
	InitRectangle();
}

void TestTriangle::Finalize()
{

}

void TestTriangle::Update(float elapsedTime)
{
	// Possibly change some of these values to allow for greater range for view matrix
	projMatrix = projMatrix.Ortho(-2.0f, 2.0f, -2.5f, 2.5f, -1.0f, 1.0f);

	// Create the view matrix
	mvMatrix = mvMatrix.LookAt(Vector3(0.0, 0.0, 1.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));

	mvpMatrix = mvMatrix * projMatrix;
}

void TestTriangle::Render(float elapsedTime)
{
	glViewport(0, 0, GetWidth(), GetHeight());

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader.GetProgram());

	rectangle.Render(elapsedTime, mvpMatrix, mvpMatrixHandle);
}

void TestTriangle::InitRectangle()
{
	const char vShaderStr[] =
		"uniform mat4 MVPMatrix;				  \n"
		"attribute vec4 vPosition;                \n"
		"void main()                              \n"
		"{                                        \n"
		"   gl_Position = MVPMatrix * vPosition;  \n"
		"}                                        \n";

	const char fShaderStr[] =
		"precision mediump float;\n"
		"void main()                                  \n"
		"{                                            \n"
		"  gl_FragColor = vec4 ( 0.0, 1.0, 0.0, 1.0 );\n"
		"}                                            \n";

	shader.LoadFromSource(vShaderStr, fShaderStr);

	glBindAttribLocation(shader.GetProgram(), 0, "vPosition");

	shader.Link();

	mvpMatrixHandle = glGetUniformLocation(shader.GetProgram(), "MVPMatrix");

	rectangle.LoadVertices(vVertices, arraysize(vVertices));
	rectangle.LoadIndices(vIndices, arraysize(vIndices));
	rectangle.Initialize();
}
