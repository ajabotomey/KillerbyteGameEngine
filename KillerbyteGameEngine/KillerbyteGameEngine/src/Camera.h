#ifndef CAMERA_H_
#define CAMERA_H_

#include "Base.h"
#include "Object.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix44.h"

namespace KillerbyteGameEngine 
{
	class Camera : public Object
	{
	public:
		enum CameraType
		{
			PERSPECTIVE,
			ORTHOGRAPHIC
		};

		Camera();
		~Camera();

		// Main Methods
		void LookAt(Vector3 camera, Vector3 target, Vector3 up);
		void MoveCamera(float x, float y, float z);
		void Frustum(double left, double right, double bottom, double top, double nearPlane, double farPlane);
		void Perspective(float fovy, float aspectRatio, float nearPlane, float farPlane);

		// Assessors
		inline float GetSpeed() { return movementSpeed; }

		// Properties
		Vector3 position;
		Vector2 rotateAngle;
		Vector3 direction;
		Vector3 target;
		float movementSpeed;

	protected:
		

	private:
		Matrix44 perspectiveMatrix;
		Matrix44 viewMatrix;
	};
}

#endif