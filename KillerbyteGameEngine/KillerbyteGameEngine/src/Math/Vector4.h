#ifndef VECTOR4_H_
#define VECTOR4_H_

#include <cmath>

class Vector4
{
public:
	// Constructors
	inline Vector4() { };
	inline Vector4(double x_, double y_, double z_, double w_) { x = x_; y = y_; z = z_; w = w_; }
	// Copy operators
	Vector4& operator = (const Vector4& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }

	// Mutators
	inline void set(double x_, double y_, double z_, double w_) { x = x_; y = y_; z = z_; w = w_; }
	inline void setX(double x_) { x = x_; }
	inline void setY(double y_) { y = y_; }
	inline void setZ(double z_) { z = z_; }
	inline void setW(double w_) { w = w_; }

	//Equality Operators
	//Vector3 &operator = (const Vector3 &other) { return Vector3(-x, -y, -z); }
	bool operator == (const Vector4 &other) { if (x == other.x && y == other.y && z == other.z && w == other.w) return true; return false; }
	bool operator != (const Vector4 &other) { if (x == other.x && y == other.y && z == other.z && w == other.w) return false; return true; }

	// Arithmetic Operators
	Vector4 operator - () const { return Vector4(-x, -y, -z, -w); }
	Vector4 operator + (const Vector4 &other) const { return Vector4(x + other.x, y + other.y, z + other.z, w + other.w); }
	Vector4 &operator += (const Vector4 &other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	Vector4 operator - (const Vector4 &other) const { return Vector4(x - other.x, y - other.y, z - other.z, w - other.w); }
	Vector4 &operator -= (const Vector4 &other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	Vector4 operator * (double scalar) const { return Vector4(x * scalar, y * scalar, z * scalar, w * scalar); }
	Vector4 &operator *= (double scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
	Vector4 operator / (double dividend) const { return Vector4(x * (1.0f / dividend), y * (1.0f / dividend), z * (1.0f / dividend), w * (1.0f / dividend)); }
	Vector4 &operator /= (double dividend) { double scalar = 1.0f / dividend; x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }

	// Utility functions
	void zero() { x = y = z = w = 0.0f; }
	void normalize() 
	{ 
		double length = magnitude();

		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}
	double dotProduct(const Vector4 &other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
	double magnitude() { return sqrt(x * x + y * y + z * z + w * w); }
	double* returnDoubleArray()
	{
		double* pointer = new double[4];

		pointer[0] = x;
		pointer[1] = y;
		pointer[2] = z;
		pointer[3] = w;

		return pointer;
	}

public:
	double x, y, z, w;
};

inline Vector4 operator * (double scalar, const Vector4 &in)
{
	return Vector4(scalar * in.x, scalar * in.y, scalar * in.z, scalar * in.w);
}

inline double distance(const Vector4 &a, const Vector4 &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	double dz = a.z - b.z;
	double dw = a.w - b.w;

	return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

inline double distanceSquared(const Vector4 &a, const Vector4 &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	double dz = a.z - b.z;
	double dw = a.w - b.w;

	return dx * dx + dy * dy + dz * dz + dw * dw;
}

#endif