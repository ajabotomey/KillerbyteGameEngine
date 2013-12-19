#ifndef CAMERA_H_
#define CAMERA_H_

#include "Base.h"
#include "Object.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Matrix44.h"

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
		Matrix44 LookAt(Vector3 camera, Vector3 target, Vector3 up);
		void MoveCamera(float x, float y, float z);
		Matrix44 Frustum(double left, double right, double bottom, double top, double nearPlane, double farPlane);
		Matrix44 Perspective(float fovy, float aspectRatio, float nearPlane, float farPlane);
		Matrix44 Ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);

		// Assessors
		inline float GetSpeed() { return movementSpeed; }
		inline Matrix44 GetViewMatrix() { return viewMatrix; }
		inline Matrix44 GetProjectionMatrix() { return projectionMatrix; }

		// Properties
		Vector3 position;
		Vector2 rotateAngle;
		Vector3 direction;
		Vector3 target;
		float movementSpeed;

	protected:
		

	private:
		Matrix44 projectionMatrix;
		Matrix44 viewMatrix;
	};
}

#endif