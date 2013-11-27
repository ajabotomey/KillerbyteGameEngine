// Base Model class
// Texture goes to model. Model is rendered

// At the moment, we are simply drawing the model onto the screen.
// Then we can focus on loading a PNG image as a texture
// Then implement sprite animation

#ifndef MODEL_H
#define MODEL_H

#include "Base.h"
#include "Object.h"
#include <vector>

namespace KillerbyteGameEngine
{
	class Model : public Object
	{
	public:
		Model();
		~Model();
	
		//void LoadData(std::vector<T> data, std::vector<T> newData);

		void Initialize();
		void Update(float elapsedTime);
		void Render(float elapsedTime);
	private:
		std::vector<GLfloat> vertices;
		std::vector<GLubyte> indices;

		GLint info[2]; // Buffer data
	};
}

#endif