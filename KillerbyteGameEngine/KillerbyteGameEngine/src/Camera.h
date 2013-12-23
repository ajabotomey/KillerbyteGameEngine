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
		Matrix44 Frustum(double left, double right, double bottom, double top, double nearPlane, double farPlane);
		Matrix44 Perspective(float fovy, float aspectRatio, float nearPlane, float farPlane);
		Matrix44 Ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);

		// Assessors
		inline Matrix44 GetViewMatrix() { return viewMatrix; }
		inline Matrix44 GetProjectionMatrix() { return projectionMatrix; }
		inline Vector3 GetPosition() { return position; }
		inline Vector3 GetTarget() { return target; }

		// Mutators
		inline void SetPosition(Vector3 newPosition) { position = newPosition; }
		inline void SetTarget(Vector3 newTarget) { target = newTarget; }
		
	protected:
		

	private:
		// Properties
		Vector3 position;
		Vector3 target;
		Matrix44 projectionMatrix;
		Matrix44 viewMatrix;
	};
}

#endif