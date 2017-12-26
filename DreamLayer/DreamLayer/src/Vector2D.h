#pragma once
#include <iostream>

class Vector2D {
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& add(const Vector2D& v);
	Vector2D& sub(const Vector2D& v);
	Vector2D& mult(const Vector2D& v);
	Vector2D& div(const Vector2D& v);

	//Operator overloading!

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator/=(const Vector2D& v);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& v);
};

