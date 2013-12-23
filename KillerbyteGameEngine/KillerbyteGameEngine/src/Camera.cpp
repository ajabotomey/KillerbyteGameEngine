#include "Camera.h"

namespace KillerbyteGameEngine
{
	Camera::Camera()
	{
		
	}

	Camera::~Camera()
	{

	}

	Matrix44 Camera::LookAt(Vector3 camera, Vector3 target, Vector3 up)
	{
		Matrix44 modelView, rotation, translation;
		
		position = camera; // Where the camera is positioned

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

		return viewMatrix;
	}

	Matrix44 Camera::Frustum(double left, double right, double bottom, double top, double nearPlane, double farPlane)
	{
		double A, B, C, D, E, F;

		A = ((2 * nearPlane) / (right - left));
		B = ((2 * nearPlane) / (top - bottom));
		C = (-1.0 * (farPlane + nearPlane) / (farPlane - nearPlane));
		D = (-(2.0 * farPlane * nearPlane) / (farPlane - nearPlane));
		E = (right + left) / (right - left);
		F = (top + bottom) / (top - bottom);

		projectionMatrix(0, 0) = A;
		projectionMatrix(1, 1) = B;
		projectionMatrix(2, 2) = C;
		projectionMatrix(2, 3) = D;
		projectionMatrix(0, 2) = E;
		projectionMatrix(1, 2) = F;
		projectionMatrix(3, 2) = -1;
		projectionMatrix(3, 3) = 0;

		return projectionMatrix;
	}

	Matrix44 Camera::Perspective(float fovy, float aspectRatio, float nearPlane, float farPlane)
	{
		float top = nearPlane * (tan((fovy * PI) / 360));
		float right = top * aspectRatio;
		float bottom = -top;
		float left = bottom * aspectRatio;

		float A = (2 * nearPlane) / (right - left);
		float B = (2 * nearPlane) / (top - bottom);
		float C = -((farPlane + nearPlane) / (farPlane - nearPlane));
		float D = -2 * ((farPlane * nearPlane) / (farPlane - nearPlane));

		projectionMatrix(0, 0) = A;
		projectionMatrix(1, 1) = B;
		projectionMatrix(2, 2) = C;
		projectionMatrix(2, 3) = D;
		projectionMatrix(3, 2) = -1;
		projectionMatrix(3, 3) = 0;

		return projectionMatrix;
	}

	Matrix44 Camera::Ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		float deltaX = right - left;
		float deltaY = top - bottom;
		float deltaZ = farPlane - nearPlane;
		Matrix44 ortho;

		if (deltaX == 0.0f || deltaY == 0.0f || deltaZ == 0.0f)
		{
			//return ortho;
		}

		ortho(0, 0) = 2.0f / deltaX;
		ortho(3, 0) = -(right + left) / deltaX;
		ortho(1, 1) = 2.0f / deltaY;
		ortho(3, 1) = -(top + bottom) / deltaY;
		ortho(2, 2) = 2.0f / deltaZ;
		ortho(3, 2) = -(nearPlane + farPlane) / deltaZ;

		//return ortho;
		projectionMatrix = ortho;

		return projectionMatrix;
	}
}