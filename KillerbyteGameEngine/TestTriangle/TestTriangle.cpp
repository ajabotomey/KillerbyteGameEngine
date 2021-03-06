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
	scene = new Scene("assets/Scene/test.xml");
	//GetAudioController()->LoadClip("assets/chirp.wav", true);
	//GetAudioController()->LoadClip("assets/noise.wav", true);
	//clip.OpenClip("assets/chirp.wav");]
	texture.LoadTextureFromFile("assets/Image/dudette_01.png");
}

void TestTriangle::Finalize()
{
	rectangle.Shutdown();
}

void TestTriangle::Update(float elapsedTime)
{
	//// First update the ractangle
	//rectangle.Update(elapsedTime);
	camera = scene->GetActiveCamera();

	// We need the half extents of the screen
	float halfWidth = GetWidth() / 2;
	float halfHeight = GetHeight() / 2;

	// Possibly change some of these values to allow for greater range for view matrix
	projMatrix = camera->Ortho(-halfWidth, halfWidth, -halfHeight , halfHeight, -1.0f, 1.0f);

	// Create the view matrix
	viewMatrix = camera->LookAt(Vector3(0.0, 0.0, 1.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0));

	// Update the scene last because we need those matrices
	scene->Update(elapsedTime);
}

void TestTriangle::Render(float elapsedTime)
{
	glViewport(0, 0, GetWidth(), GetHeight());

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glUseProgram(shader.GetProgram());

	//rectangle.Render(elapsedTime);
	scene->Render(elapsedTime);
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
	Model* player = scene->FindNode("Player")->GetModel();

	if (evt == Keyboard::KEY_DOWN)
	{
		switch (key)
		{
		case Keyboard::KEY_A:
		case Keyboard::KEY_CAP_A:
		case Keyboard::KEY_LEFTARROW:
			x = player->GetPosition().getX() - 0.005;
			player->SetPositionX(x);
			break;

		case Keyboard::KEY_D:
		case Keyboard::KEY_CAP_D:
		case Keyboard::KEY_RIGHTARROW:
			x = player->GetPosition().getX() + 0.005;
			player->SetPositionX(x);
			break;

		case Keyboard::KEY_P:
			GetAudioController()->PlayClip("chirp");
			break;

		case Keyboard::KEY_O:
			GetAudioController()->PauseClip("chirp");
			break;

		case Keyboard::KEY_I:
			GetAudioController()->StopClip("chirp");
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
			x = player->GetPosition().getX() + 0;
			player->SetPositionX(x);
			break;

		case Keyboard::KEY_D:
		case Keyboard::KEY_CAP_D:
		case Keyboard::KEY_RIGHTARROW:
			x = player->GetPosition().getX() - 0;
			player->SetPositionX(x);
			break;
		}
	}
}