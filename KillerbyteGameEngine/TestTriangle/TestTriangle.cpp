#include "TestTriangle.h"

TestTriangle game;

//GLfloat vVertices[] =
//{
//	50.0f,  -100.0f, 0.0f,
//	50.0f, 100.0f, 0.0f,
//	-50.0f, 100.0f, 0.0f,
//	-50.0f, -100.0f, 0.0f
//};

Vector3 vVertices[] =
{
	Vector3(50.0f, -100.0f, 0.0f),
	Vector3(50.0f, 100.0f, 0.0f),
	Vector3(-50.0f, 100.0f, 0.0f),
	Vector3(-50.0f, -100.0f, 0.0f)
};

Vector2 vTexCoords[] =
{
	Vector2(1.0, 0.0),
	Vector2(1.0, 1.0),
	Vector2(0.0, 1.0),
	Vector2(0.0, 0.0)
};

//GLfloat vTexCoords[] = 
//{
//	1.0, 0.0,
//	1.0, 1.0,
//	0.0, 1.0,
//	0.0, 0.0
//};

GLubyte vIndices[] =
{
	0, 1, 2,
	2, 3, 0
};

TestTriangle::TestTriangle()
{
	scene = NULL;
}

void TestTriangle::Initialize()
{
	InitRectangle();
	scene = new Scene("assets/test.xml");
	//GetAudioController()->LoadClip("assets/chirp.wav", true);
	//GetAudioController()->LoadClip("assets/noise.wav", true);
	//clip.OpenClip("assets/chirp.wav");
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
	shader.LoadFromFile("assets/shader.vert", "assets/shader.frag");

	glBindAttribLocation(shader.GetProgram(), 0, "vPosition");

	shader.Link();

	mvpMatrixHandle = glGetUniformLocation(shader.GetProgram(), "MVPMatrix");

	rectangle.LoadVertices(vVertices, vTexCoords, arraysize(vVertices));
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
			GetAudioController()->PlayClip("chirp");
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