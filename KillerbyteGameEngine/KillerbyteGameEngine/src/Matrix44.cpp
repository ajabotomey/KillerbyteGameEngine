#include "Matrix44.h"

Matrix44::Matrix44(const Matrix44& other)
{
	mV[0] = other.mV[0];
	mV[1] = other.mV[1];
	mV[2] = other.mV[2];
	mV[3] = other.mV[3];
	mV[4] = other.mV[4];
	mV[5] = other.mV[5];
	mV[6] = other.mV[6];
	mV[7] = other.mV[7];
	mV[8] = other.mV[8];
	mV[9] = other.mV[9];
	mV[10] = other.mV[10];
	mV[11] = other.mV[11];
	mV[12] = other.mV[12];
	mV[13] = other.mV[13];
	mV[14] = other.mV[14];
	mV[15] = other.mV[15];
}

void Matrix44::identity()
{
	mV[0] = 1.0f;
	mV[1] = 0.0f;
	mV[2] = 0.0f;
	mV[3] = 0.0f;
	mV[4] = 0.0f;
	mV[5] = 1.0f;
	mV[6] = 0.0f;
	mV[7] = 0.0f;
	mV[8] = 0.0f;
	mV[9] = 0.0f;
	mV[10] = 1.0f;
	mV[11] = 0.0f;
	mV[12] = 0.0f;
	mV[13] = 0.0f;
	mV[14] = 0.0f;
	mV[15] = 1.0f;
}

Matrix44& Matrix44::transpose()
{
	float temp = mV[1];
	mV[1] = mV[4];
	mV[4] = temp;

	temp = mV[2];
	mV[2] = mV[8];
	mV[8] = temp;

	temp = mV[3];
	mV[3] = mV[12];
	mV[12] = temp;

	temp = mV[6];
	mV[6] = mV[9];
	mV[9] = temp;

	temp = mV[7];
	mV[7] = mV[13];
	mV[13] = temp;

	temp = mV[11];
	mV[11] = mV[14];
	mV[14] = temp;

	return *this;
}

Matrix44& Matrix44::translation(const Vector3& xlate)
{
	identity();
	mV[12] = xlate.x;
	mV[13] = xlate.y;
	mV[14] = xlate.z;

	return *this;
}

Matrix44& Matrix44::scaling(const Vector3& scale)
{
	mV[0] = scale.x;
	mV[1] = 0.0f;
	mV[2] = 0.0f;
	mV[3] = 0.0f;
	mV[4] = 0.0f;
	mV[5] = scale.y;
	mV[6] = 0.0f;
	mV[7] = 0.0f;
	mV[8] = 0.0f;
	mV[9] = 0.0f;
	mV[10] = scale.z;
	mV[11] = 0.0f;
	mV[12] = 0.0f;
	mV[13] = 0.0f;
	mV[14] = 0.0f;
	mV[15] = 1.0f;

	return *this;
}

Matrix44& Matrix44::rotationX(float angle)
{
	float sinTheta = sinf(angle);
	float cosTheta = cosf(angle);

	mV[5] = cosTheta;
	mV[6] = sinTheta;
	mV[9] = -sinTheta;
	mV[10] = cosTheta;

	return *this;
}

Matrix44& Matrix44::rotationY(float angle)
{
	float sinTheta = sinf(angle);
	float cosTheta = cosf(angle);

	mV[0] = cosTheta;
	mV[2] = -sinTheta;
	mV[8] = sinTheta;
	mV[10] = cosTheta;

	return *this;
}

Matrix44& Matrix44::rotationZ(float angle)
{
	float sinTheta = sinf(angle);
	float cosTheta = cosf(angle);

	mV[0] = cosTheta;
	mV[1] = sinTheta;
	mV[4] = -sinTheta;
	mV[5] = cosTheta;

	return *this;
}

Matrix44 Matrix44::LookAt(Vector3 camera, Vector3 target, Vector3 up)
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

	return modelView;
}

Matrix44 Matrix44::Perspective(float fovy, float aspectRatio, float near, float far)
{
	Matrix44 perspectiveMatrix;

	float top = near * (tan((fovy * PI) / 360));
	float right = top * aspectRatio;
	float bottom = -top;
	float left = bottom * aspectRatio;

	float A = (2 * near) / (right - left);
	float B = (2 * near) / (top - bottom);
	float C = - ((far + near) / (far - near));
	float D = -2 * ((far * near) / (far - near));

	perspectiveMatrix(0, 0) = A;
	perspectiveMatrix(1, 1) = B;
	perspectiveMatrix(2, 2) = C;
	perspectiveMatrix(2, 3) = D;
	perspectiveMatrix(3, 2) = -1;
	perspectiveMatrix(3, 3) = 0;

	return perspectiveMatrix;
}

Matrix44 Matrix44::Frustum(double left, double right, double bottom, double top, double near, double far)
{
	Matrix44 perspectiveMatrix;
	double A, B, C, D, E, F;

	A = ((2 * near) / (right - left));
	B = ((2 * near) / (top - bottom));
	C = (-1.0 * (far + near) / (far - near));
	D = (-(2.0 * far * near) / (far - near));
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

	return perspectiveMatrix;
}

Matrix44 Matrix44::Ortho(float left, float right, float bottom, float top, float near, float far)
{
	float deltaX = right - left;
	float deltaY = top - bottom;
	float deltaZ = far - near;
	Matrix44 ortho;

	if (deltaX == 0.0f || deltaY == 0.0f || deltaZ == 0.0f)
	{
		return ortho;
	}

	ortho(0, 0) = 2.0f / deltaX;
	ortho(3, 0) = -(right + left) / deltaX;
	ortho(1, 1) = 2.0f / deltaY;
	ortho(3, 1) = -(top + bottom) / deltaY;
	ortho(2, 2) = 2.0f / deltaZ;
	ortho(3, 2) = -(near + far) / deltaZ;

	return ortho;
}

Matrix44& Matrix44::operator = (const Matrix44& other)
{
	if (this == &other)
		return *this;

	mV[0] = other.mV[0];
	mV[1] = other.mV[1];
	mV[2] = other.mV[2];
	mV[3] = other.mV[3];
	mV[4] = other.mV[4];
	mV[5] = other.mV[5];
	mV[6] = other.mV[6];
	mV[7] = other.mV[7];
	mV[8] = other.mV[8];
	mV[9] = other.mV[9];
	mV[10] = other.mV[10];
	mV[11] = other.mV[11];
	mV[12] = other.mV[12];
	mV[13] = other.mV[13];
	mV[14] = other.mV[14];
	mV[15] = other.mV[15];

	return *this;
}

bool Matrix44::operator == (const Matrix44& other) const
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		if (mV[i] != other.mV[i])
			return false;
	}

	return true;
}

bool Matrix44::operator != (const Matrix44& other) const
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		if (mV[i] != other.mV[i])
			return true;
	}

	return false;
}

bool Matrix44::isIdentity() const
{
	Matrix44 test;

	if (this == &test)
		return true;

	return false;
}

Matrix44 Matrix44::operator + (const Matrix44& other) const
{
	Matrix44 result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.mV[i] = mV[i] + other.mV[i];
	}

	return result;
}

Matrix44& Matrix44::operator += (const Matrix44& other)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		mV[i] += other.mV[i];
	}

	return *this;
}

Matrix44 Matrix44::operator - (const Matrix44& other) const
{
	Matrix44 result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.mV[i] = mV[i] - other.mV[i];
	}

	return result;
}

Matrix44& Matrix44::operator -= (const Matrix44& other)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		mV[i] -= other.mV[i];
	}

	return *this;
}

Matrix44 Matrix44::operator - () const
{
	Matrix44 result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.mV[i] = -mV[i];
	}

	return result;
}

Matrix44 Matrix44::operator * (const Matrix44& other) const
{
	Matrix44 result;

	result.mV[0] = mV[0] * other.mV[0] + mV[4] * other.mV[1] + mV[8] * other.mV[2] + mV[12] * other.mV[3];
	result.mV[1] = mV[1] * other.mV[0] + mV[5] * other.mV[1] + mV[9] * other.mV[2] + mV[13] * other.mV[3];
	result.mV[2] = mV[2] * other.mV[0] + mV[6] * other.mV[1] + mV[10] * other.mV[2] + mV[14] * other.mV[3];
	result.mV[3] = mV[3] * other.mV[0] + mV[7] * other.mV[1] + mV[11] * other.mV[2] + mV[15] * other.mV[3];

	result.mV[4] = mV[0] * other.mV[4] + mV[4] * other.mV[5] + mV[8] * other.mV[6] + mV[12] * other.mV[7];
	result.mV[5] = mV[1] * other.mV[4] + mV[5] * other.mV[5] + mV[9] * other.mV[6] + mV[13] * other.mV[7];
	result.mV[6] = mV[2] * other.mV[4] + mV[6] * other.mV[5] + mV[10] * other.mV[6] + mV[14] * other.mV[7];
	result.mV[7] = mV[3] * other.mV[4] + mV[7] * other.mV[5] + mV[11] * other.mV[6] + mV[15] * other.mV[7];

	result.mV[8] = mV[0] * other.mV[8] + mV[4] * other.mV[9] + mV[8] * other.mV[10] + mV[12] * other.mV[11];
	result.mV[9] = mV[1] * other.mV[8] + mV[5] * other.mV[9] + mV[9] * other.mV[10] + mV[13] * other.mV[11];
	result.mV[10] = mV[2] * other.mV[8] + mV[6] * other.mV[9] + mV[10] * other.mV[10] + mV[14] * other.mV[11];
	result.mV[11] = mV[3] * other.mV[8] + mV[7] * other.mV[9] + mV[11] * other.mV[10] + mV[15] * other.mV[11];

	result.mV[12] = mV[0] * other.mV[12] + mV[4] * other.mV[13] + mV[8] * other.mV[14] + mV[12] * other.mV[15];
	result.mV[13] = mV[1] * other.mV[12] + mV[5] * other.mV[13] + mV[9] * other.mV[14] + mV[13] * other.mV[15];
	result.mV[14] = mV[2] * other.mV[12] + mV[6] * other.mV[13] + mV[10] * other.mV[14] + mV[14] * other.mV[15];
	result.mV[15] = mV[3] * other.mV[12] + mV[7] * other.mV[13] + mV[11] * other.mV[14] + mV[15] * other.mV[15];

	return result;
}

Matrix44& Matrix44::operator *= (const Matrix44& other)
{
	Matrix44 result;

	result.mV[0] = mV[0] * other.mV[0] + mV[4] * other.mV[1] + mV[8] * other.mV[2] + mV[12] * other.mV[3];
	result.mV[1] = mV[1] * other.mV[0] + mV[5] * other.mV[1] + mV[9] * other.mV[2] + mV[13] * other.mV[3];
	result.mV[2] = mV[2] * other.mV[0] + mV[6] * other.mV[1] + mV[10] * other.mV[2] + mV[14] * other.mV[3];
	result.mV[3] = mV[3] * other.mV[0] + mV[7] * other.mV[1] + mV[11] * other.mV[2] + mV[15] * other.mV[3];

	result.mV[4] = mV[0] * other.mV[4] + mV[4] * other.mV[5] + mV[8] * other.mV[6] + mV[12] * other.mV[7];
	result.mV[5] = mV[1] * other.mV[4] + mV[5] * other.mV[5] + mV[9] * other.mV[6] + mV[13] * other.mV[7];
	result.mV[6] = mV[2] * other.mV[4] + mV[6] * other.mV[5] + mV[10] * other.mV[6] + mV[14] * other.mV[7];
	result.mV[7] = mV[3] * other.mV[4] + mV[7] * other.mV[5] + mV[11] * other.mV[6] + mV[15] * other.mV[7];

	result.mV[8] = mV[0] * other.mV[8] + mV[4] * other.mV[9] + mV[8] * other.mV[10] + mV[12] * other.mV[11];
	result.mV[9] = mV[1] * other.mV[8] + mV[5] * other.mV[9] + mV[9] * other.mV[10] + mV[13] * other.mV[11];
	result.mV[10] = mV[2] * other.mV[8] + mV[6] * other.mV[9] + mV[10] * other.mV[10] + mV[14] * other.mV[11];
	result.mV[11] = mV[3] * other.mV[8] + mV[7] * other.mV[9] + mV[11] * other.mV[10] + mV[15] * other.mV[11];

	result.mV[12] = mV[0] * other.mV[12] + mV[4] * other.mV[13] + mV[8] * other.mV[14] + mV[12] * other.mV[15];
	result.mV[13] = mV[1] * other.mV[12] + mV[5] * other.mV[13] + mV[9] * other.mV[14] + mV[13] * other.mV[15];
	result.mV[14] = mV[2] * other.mV[12] + mV[6] * other.mV[13] + mV[10] * other.mV[14] + mV[14] * other.mV[15];
	result.mV[15] = mV[3] * other.mV[12] + mV[7] * other.mV[13] + mV[11] * other.mV[14] + mV[15] * other.mV[15];

	for (unsigned int i = 0; i < 16; ++i)
	{
		mV[i] = result.mV[i];
	}

	return *this;
}

Matrix44 Matrix44::operator * (float scalar) const
{
	Matrix44 result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.mV[i] = mV[i] * scalar;
	}

	return result;
}

Matrix44& Matrix44::operator *= (float scalar)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		mV[i] *= scalar;
	}

	return *this;
}
