#include "Vector.h"



Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(float x1, float y1)
{
	x = x1;
	y = y1;
}

Vector Vector::operator*(float other)
{
	Vector v = Vector(x, y);

	v.x *= other;
	v.y *= other;

	return v;
}

Vector& Vector::operator+=(const Vector& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vector::~Vector()
{
}
