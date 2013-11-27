#include "Camera.h"

namespace KillerbyteGameEngine
{
	Camera::Camera()
	{
		//direction.set(0.0f, -2.0f, -5.0f);
		direction.set(0.0f, 0.0f, -1.0f);
		//position.set(0.0f, 2.0f, 5.0f);
		position.set(0.0f, 0.0f, 5.0f);
		movementSpeed = 0.1f;
	}

	Camera::~Camera()
	{

	}

	void Camera::LookAt(Vector3 camera, Vector3 target, Vector3 up)
	{
		Matrix44 modelView, rotation, translation;

		Vector3 forward = target - camera;
		forward.normalize();
		up.normalize();
		Vector3 left = forward.crossProduct(up);
		left.normalize();
		up = left.crossProduct(forward);
		up.normalize();

		rotation(0, 0) = left.x;
		rotation(0, 1) = left.y;
		rotation(0, 2) = left.z;
		rotation(1, 0) = up.x;
		rotation(1, 1) = up.y;
		rotation(1, 2) = up.z;
		rotation(2, 0) = -(forward.x);
		rotation(2, 1) = -(forward.y);
		rotation(2, 2) = -(forward.z);

		translation(0, 3) = -(camera.x);
		translation(1, 3) = -(camera.y);
		translation(2, 3) = -(camera.z);

		modelView = rotation * translation;

		viewMatrix = modelView;
	}

	void Camera::Frustum(double left, double right, double bottom, double top, double nearPlane, double farPlane)
	{
		double A, B, C, D, E, F;

		A = ((2 * nearPlane) / (right - left));
		B = ((2 * nearPlane) / (top - bottom));
		C = (-1.0 * (farPlane + nearPlane) / (farPlane - nearPlane));
		D = (-(2.0 * farPlane * nearPlane) / (farPlane - nearPlane));
		E = (right + left) / (right - left);
		F = (top + bottom) / (top - bottom);

		perspectiveMatrix(0, 0) = A;
		perspectiveMatrix(1, 1) = B;
		perspectiveMatrix(2, 2) = C;
		perspectiveMatrix(2, 3) = D;
		perspectiveMatrix(0, 2) = E;
		perspectiveMatrix(1, 2) = F;
		perspectiveMatrix(3, 2) = -1;
		perspectiveMatrix(3, 3) = 0;
	}

	void Camera::Perspective(float fovy, float aspectRatio, float nearPlane, float farPlane)
	{
		float top = nearPlane * (tan((fovy * PI) / 360));
		float right = top * aspectRatio;
		float bottom = -top;
		float left = bottom * aspectRatio;

		float A = (2 * nearPlane) / (right - left);
		float B = (2 * nearPlane) / (top - bottom);
		float C = -((farPlane + nearPlane) / (farPlane - nearPlane));
		float D = -2 * ((farPlane * nearPlane) / (farPlane - nearPlane));

		perspectiveMatrix(0, 0) = A;
		perspectiveMatrix(1, 1) = B;
		perspectiveMatrix(2, 2) = C;
		perspectiveMatrix(2, 3) = D;
		perspectiveMatrix(3, 2) = -1;
		perspectiveMatrix(3, 3) = 0;
	}

	void Camera::MoveCamera(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}
}