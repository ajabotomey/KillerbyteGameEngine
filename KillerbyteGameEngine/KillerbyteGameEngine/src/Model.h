// Base Model class
// Texture goes to model. Model is rendered

// At the moment, we are simply drawing the model onto the screen.
// Then we can focus on loading a PNG image as a texture
// Then implement sprite animation

#ifndef MODEL_H
#define MODEL_H

#include "Base.h"
#include "Object.h"
#include "Math/Matrix44.h"
#include "Math/Vector2.h"
#include <vector>

namespace KillerbyteGameEngine
{
	class Model : public Object
	{
	public:
		struct Vertex
		{
			Vector3 position;
			Vector2 texCoords;
		};

		Model();
		~Model();
	
		//void LoadData(std::vector<T> data, std::vector<T> newData);
		void LoadVertices(Vector3* positions, Vector2* texCoords, int length);
		//void LoadTexCoords(Vector2* data, int length);
		void LoadIndices(GLubyte* data, int length);

		void Initialize();
		void Update(float elapsedTime);
		// This will eventually go back to only one parameter
		// Shader will eventually become a member of Model
		void Render(float elapsedTime, Matrix44 mvpMatrix, GLint handle);
		void Shutdown();

		// Accessors
		inline Matrix44 GetModelMatrix() { return modelMatrix; }
		inline Vector3 GetPosition() { return position;  }

		// Mutators
		void SetPosition(Vector3 newPosition);
		inline void SetPositionX(float x) { position.setX(x); }
	private:
		//std::vector<Vector3> vertices;
		//std::vector<Vector2> texCoords;
		std::vector<Vertex> vertices;
		std::vector<GLubyte> indices;

		// Influences the model matrix
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		// Matrices - No need for the view matrix because we can get that from the camera
		Matrix44 mvpMatrix;
		Matrix44 modelMatrix;
		Matrix44 projMatrix;

		GLuint info[2]; // Buffer data
	};
}

#endif