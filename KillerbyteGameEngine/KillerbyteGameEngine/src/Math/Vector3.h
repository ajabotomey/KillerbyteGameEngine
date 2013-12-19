#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3
{
public:
	// Constructors
	inline Vector3() {} // Default constructor
	inline Vector3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; } // Copy constructor

	// Copy operators
	Vector3& operator = (const Vector3& other) { x = other.x; y = other.y; z = other.z;  return *this; }

	// Mutators
	inline void set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
	inline void setX(float x_) { x = x_; }
	inline void setY(float y_) { y = y_; }
	inline void setZ(float z_) { z = z_; }

	// Accessors
	inline float getX() { return x; }
	inline float getY() { return y; }
	inline float getZ() { return z; }

	//Equality Operators
	//Vector3 &operator = (const Vector3 &other) { return Vector3(-x, -y, -z); }
	bool operator == (const Vector3 &other) { if (x == other.x && y == other.y && z == other.z) return true; return false; }
	bool operator != (const Vector3 &other) { if (x == other.x && y == other.y && z == other.z) return false; return true; }

	// Arithmetic Operators
	Vector3 operator - () const { return Vector3(-x, -y, -z); }
	Vector3 operator + (const Vector3 &other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
	Vector3 &operator += (const Vector3 &other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3 operator - (const Vector3 &other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
	Vector3 &operator -= (const Vector3 &other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vector3 operator * (float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
	Vector3 &operator *= (float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
	Vector3 operator / (float dividend) const { return Vector3(x * (1.0f / dividend), y * (1.0f / dividend), z * (1.0f / dividend)); }
	Vector3 &operator /= (float dividend) { double scalar = 1.0f / dividend; x *= scalar; y *= scalar; z *= scalar; return *this; }

	// Utility functions
	void zero() { x = y = z = 0.0f; }
	void normalize() 
	{ 
		float length = magnitude();

		x /= length;
		y /= length;
		z /= length;
	}
	float dotProduct(const Vector3 &other) const { return x * other.x + y * other.y + z * other.z; }
	float magnitude() { return sqrt(x * x + y * y + z * z);}
	Vector3 crossProduct(const Vector3 &other) 
	{ 
		return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

public:
	float x, y, z;
};

inline Vector3 operator * (float scalar, const Vector3 &in)
{
	return Vector3(scalar * in.x, scalar * in.y, scalar * in.z);
}

inline float distance(const Vector3 &a, const Vector3 &b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

#endif
