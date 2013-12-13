#include "TestTriangle.h"

TestTriangle game;

GLfloat vVertices[] =
{
	50.0f,  -100.0f, 0.0f,
	50.0f, 100.0f, 0.0f,
	-50.0f, 100.0f, 0.0f,
	-50.0f, -100.0f, 0.0f
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
	GetAudioController()->LoadClip("assets/chirp.wav", true);
}

void TestTriangle::Finalize()
{
	rectangle.Shutdown();
}

void TestTriangle::Update(float elapsedTime)
{
	// First update the ractangle
	rectangle.Update(elapsedTime);

	// We need the half extents of the screen
	float halfWidth = GetWidth() / 2;
	float halfHeight = GetHeight() / 2;

	// Possibly change some of these values to allow for greater range for view matrix
	projMatrix = camera->Ortho(-halfWidth, halfWidth, -halfHeight , halfHeight, -1.0f, 1.0f);

	// Create the view matrix
	viewMatrix = camera->LookAt(Vector3(0.0, 0.0, 1.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));

	mvMatrix = rectangle.GetModelMatrix() * viewMatrix;

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

void TestTriangle::KeyEvent(Keyboard::KeyEvent evt, int key)
{
	float x;

	if (evt == Keyboard::KEY_DOWN)
	{
		switch (key)
		{
		case Keyboard::KEY_A:
		case Keyboard::KEY_CAP_A:
		case Keyboard::KEY_LEFTARROW:
			x = rectangle.GetPosition().getX() - 0.005;
			rectangle.SetPositionX(x);
			break;

		case Keyboard::KEY_D:
		case Keyboard::KEY_CAP_D:
		case Keyboard::KEY_RIGHTARROW:
			x = rectangle.GetPosition().getX() + 0.005;
			rectangle.SetPositionX(x);
			break;

		case Keyboard::KEY_P:
			GetAudioController()->PlayClip("assets/chirp.wav");
			break;

		case Keyboard::KEY_O:
			GetAudioController()->PauseClip("assets/chirp.wav");
			break;

		case Keyboard::KEY_I:
			GetAudioController()->StopClip("assets/chirp.wav");
			break;
		}
	}
	else if (evt == Keyboard::KEY_UP)
	{
		switch (key)
		{
		case Keyboard::KEY_A:
		case Keyboard::KEY_CAP_A:
		case Keyboard::KEY_LEFTARROW:
			x = rectangle.GetPosition().getX() + 0;
			rectangle.SetPositionX(x);
			break;

		case Keyboard::KEY_D:
		case Keyboard::KEY_CAP_D:
		case Keyboard::KEY_RIGHTARROW:
			x = rectangle.GetPosition().getX() - 0;
			rectangle.SetPositionX(x);
			break;
		}
	}
}