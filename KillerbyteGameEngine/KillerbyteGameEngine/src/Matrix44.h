#ifndef MATRIX44_H_
#define MATRIX44_H_

#include "Vector3.h"

#define PI 3.14159265359

class Matrix44
{
public:
	inline Matrix44() { identity(); };
	inline ~Matrix44() { };
	Matrix44(const Matrix44& other);

	// accessor
	inline float &operator () (unsigned int i, unsigned int j) { return mV[i + 4 * j]; }
	inline float operator () (unsigned int i, unsigned int j) const { return mV[i + 4 * j]; }
	inline float* getValues() { return mV; }

	// mutators
	void identity();
	Matrix44& transpose();

	// transformations
	Matrix44& translation(const Vector3& xlate);
	Matrix44& scaling(const Vector3& scale);
	Matrix44& rotate(float angle, float x, float y, float z);
	Matrix44& rotationX(float angle);
	Matrix44& rotationY(float angle);
	Matrix44& rotationZ(float angle);
	Matrix44 LookAt(Vector3 camera, Vector3 target, Vector3 up);
	Matrix44 Perspective(float fovy, float aspectRatio, float near, float far);
	Matrix44 Frustum(double left, double right, double bottom, double top, double near, double far);
	Matrix44 Ortho(float left, float right, float bottom, float top, float near, float far);

	// Copy operator
	Matrix44& operator = (const Matrix44& other);

	// equality operators
	bool operator == (const Matrix44& other) const;
	bool operator != (const Matrix44& other) const;
	bool isIdentity() const;

	// arithmetic operators
	Matrix44 operator + (const Matrix44& other) const;
	Matrix44 &operator += (const Matrix44& other);
	Matrix44 operator - (const Matrix44& other) const;
	Matrix44 &operator -= (const Matrix44& other);
	Matrix44 operator - () const;
	Matrix44 operator * (const Matrix44& matrix) const;
	Matrix44 operator * (const Vector3& vector) const;
	Matrix44 &operator *= (const Matrix44& matrix);
	Matrix44 operator * (float scalar) const;
	Matrix44 &operator *= (float scalar);

private:
	float mV[16];
};

#endif
