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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&mvpMatrix(0, 0));
	glDrawElements(GL_TRIANGLES, sizeof(vIndices) / sizeof(vIndices[0]), GL_UNSIGNED_BYTE, 0);
}

GLuint TestTriangle::LoadShader(GLenum type, const char* source)
{
	GLuint shader;
	GLint compiled;

	shader = glCreateShader(type);

	if (shader == 0)
	{
		return 0;
	}

	glShaderSource(shader, 1, &source, NULL);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		// Log that there is an error
		glDeleteShader(shader);
		return 0;
	}

	return shader;
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

	// Create both VBOs
	glGenBuffers(2, &rectangleInfo[0]);

	// Set up the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, rectangleInfo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

	// Set up the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleInfo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vIndices), vIndices, GL_STATIC_DRAW);
}

void TestTriangle::DrawRectangle()
{

}
