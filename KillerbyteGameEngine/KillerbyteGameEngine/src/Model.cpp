#include "Model.h"

namespace KillerbyteGameEngine
{
	Model::Model()
	{

	}

	Model::~Model()
	{

	}

	void Model::Initialize()
	{
		// Initialize the VBO data
		// Create both VBOs
		glGenBuffers(2, &info[0]);

		// Set up the vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, info[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);

		//glBindBuffer(GL_ARRAY_BUFFER, info[1]);
		//glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vector2), &texCoords[0], GL_STATIC_DRAW);

		// Set up the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices[0], GL_STATIC_DRAW);
	}

	void Model::Update(float elapsedTime, Matrix44 viewMatrix, Matrix44 projMatrix)
	{
		// At the moment we are only dealing with translation at the moment
		modelMatrix.translation(position);

		mvpMatrix = modelMatrix * viewMatrix * projMatrix;
	}

	//void Model::Render(float elapsedTime, Matrix44 mvpMatrix, GLint handle)
	//{
	//	glEnableVertexAttribArray(0);
	//	glEnableVertexAttribArray(1);
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	//	glUniformMatrix4fv(handle, 1, GL_FALSE, (GLfloat*)&mvpMatrix(0, 0));
	//	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, 0);
	//}

	void Model::Render(float elapsedTime)
	{
		glUseProgram(shader.GetProgram());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

		glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&mvpMatrix(0, 0));
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, 0);
	}

	void Model::Shutdown()
	{
		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Model::SetPosition(Vector3 newPosition)
	{
		position = newPosition;
	}

	void Model::LoadVertices(Vector3* positions, Vector2* texCoords, int length)
	{
		for (int i = 0; i < length; i++)
		{
			Vertex vertex;
			vertex.position = positions[i];
			vertex.texCoords = texCoords[i];
			vertices.push_back(vertex);
		}
	}

	//void Model::LoadVertices(Vector3* data, int length)
	//{
	//	for (int i = 0; i < length; i++)
	//	{
	//		vertices.push_back(data[i]);
	//	}
	//}

	//void Model::LoadTexCoords(Vector2* data, int length)
	//{
	//	for (int i = 0; i < length; i++)
	//	{
	//		texCoords.push_back(data[i]);
	//	}
	//}

	void Model::LoadIndices(GLubyte* data, int length)
	{
		for (int i = 0; i < length; i++)
		{
			indices.push_back(data[i]);
		}
	}

	void Model::CreateRectangle(Vector2 dimensions, const char* vertexPath, const char* fragmentPath)
	{
		width = dimensions.x;
		height = dimensions.y;

		int halfWidth = width / 2;
		int halfHeight = height / 2;

		Vector3 positions[] =
		{
			Vector3(halfWidth, -halfHeight, 0.0f),
			Vector3(halfWidth, halfHeight, 0.0f),
			Vector3(-halfWidth, halfHeight, 0.0f),
			Vector3(-halfWidth, -halfHeight, 0.0f)
		};

		Vector2 vTexCoords[] =
		{
			Vector2(1.0, 0.0),
			Vector2(1.0, 1.0),
			Vector2(0.0, 1.0),
			Vector2(0.0, 0.0)
		};

		GLubyte vIndices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		if (!LoadShader(vertexPath, fragmentPath))
		{
			// Log error here
			return;
		}

		glBindAttribLocation(shader.GetProgram(), 0, "vPosition");

		shader.Link();

		// Figure out how to deal with modelviewprojection matrices
		mvpMatrixHandle = glGetUniformLocation(shader.GetProgram(), "MVPMatrix");

		LoadVertices(positions, vTexCoords, arraysize(positions));
		LoadIndices(vIndices, arraysize(vIndices));
		Initialize();
	}

	bool Model::LoadShader(const char* vertexPath, const char* fragmentPath)
	{
		return shader.LoadFromFile(vertexPath, fragmentPath);
	}
}