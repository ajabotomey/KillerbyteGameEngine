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

		//glBindBuffer(GL_ARRAY_BUFFER, info[1]);
		//glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vector2), &texCoords[0], GL_STATIC_DRAW);

		// Set up the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices[0], GL_STATIC_DRAW);
	}

	void Model::Update(float elapsedTime)
	{
		modelMatrix.translation(position);
	}

	void Model::Render(float elapsedTime, Matrix44 mvpMatrix, GLint handle)
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

		glUniformMatrix4fv(handle, 1, GL_FALSE, (GLfloat*)&mvpMatrix(0, 0));
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
}