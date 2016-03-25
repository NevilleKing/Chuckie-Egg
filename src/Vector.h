#pragma once
class Vector
{
public:
	Vector();
	Vector(float x1, float y1);
	~Vector();

	float x;
	float y;

	Vector& operator*(float other);
	Vector& Vector::operator+=(const Vector& other);
};

