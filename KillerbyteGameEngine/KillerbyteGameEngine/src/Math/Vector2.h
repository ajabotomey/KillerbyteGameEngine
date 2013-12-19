#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <cmath>

class Vector2
{
public:
	// Constructors
	inline Vector2() { };
	inline Vector2(double x_, double y_) { x = x_; y = y_; }
	// Copy operators
	Vector2& operator = (const Vector2& other) { x = other.x; y = other.y; return *this; }

	// Mutators
	inline void set(double x_, double y_) { x = x_; y = y_; }
	inline void setX(double x_) { x = x_; }
	inline void setY(double y_) { y = y_; }

	//Equality Operators
	//Vector3 &operator = (const Vector3 &other) { return Vector3(-x, -y, -z); }
	bool operator == (const Vector2 &other) { if (x == other.x && y == other.y) return true; return false; }
	bool operator != (const Vector2 &other) { if (x == other.x && y == other.y) return false; return true; }

	// Arithmetic Operators
	Vector2 operator - () const { return Vector2(-x, -y); }
	Vector2 operator + (const Vector2 &other) const { return Vector2(x + other.x, y + other.y); }
	Vector2 &operator += (const Vector2 &other) { x += other.x; y += other.y; return *this; }
	Vector2 operator - (const Vector2 &other) const { return Vector2(x - other.x, y - other.y); }
	Vector2 &operator -= (const Vector2 &other) { x -= other.x; y -= other.y; return *this; }
	Vector2 operator * (double scalar) const { return Vector2(x * scalar, y * scalar); }
	Vector2 &operator *= (double scalar) { x *= scalar; y *= scalar; return *this; }
	Vector2 operator / (double dividend) const { return Vector2(x * (1.0f / dividend), y * (1.0f / dividend)); }
	Vector2 &operator /= (double dividend) { double scalar = 1.0f / dividend; x *= scalar; y *= scalar; return *this; }

	// Utility functions
	void zero() { x = y = 0.0f; }
	void normalize()
	{
		double length = magnitude();

		x /= length;
		y /= length;
	}
	double dotProduct(const Vector2 &other) const { return x * other.x + y * other.y; }
	double magnitude() { return sqrt(x * x + y * y); }
	double* returnDoubleArray()
	{
		double* pointer = new double[2];

		pointer[0] = x;
		pointer[1] = y;

		return pointer;
	}

public:
	double x, y;
};

inline Vector2 operator * (double scalar, const Vector2 &in)
{
	return Vector2(scalar * in.x, scalar * in.y);
}

inline double distance(const Vector2 &a, const Vector2 &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;

	return sqrt(dx * dx + dy * dy);
}

#endif