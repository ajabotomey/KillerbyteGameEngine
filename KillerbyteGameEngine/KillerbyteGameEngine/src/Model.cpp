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
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

		// Set up the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), &indices[0], GL_STATIC_DRAW);
	}

	void Model::Update(float elapsedTime)
	{

	}

	void Model::Render(float elapsedTime, Matrix44 mvpMatrix, GLint handle)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glUniformMatrix4fv(handle, 1, GL_FALSE, (GLfloat*)&mvpMatrix(0, 0));
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, 0);
	}

	void Model::LoadVertices(GLfloat* data, int length)
	{
		for (int i = 0; i < length; i++)
		{
			vertices.push_back(data[i]);
		}
	}

	void Model::LoadIndices(GLubyte* data, int length)
	{
		for (int i = 0; i < length; i++)
		{
			indices.push_back(data[i]);
		}
	}
}