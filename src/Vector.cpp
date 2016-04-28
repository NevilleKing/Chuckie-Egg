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

Vector Vector::operator*(float other) const
{
	Vector v = Vector(x, y);

	v.x *= other;
	v.y *= other;

	return v;
}

Vector Vector::operator*(const Vector& other) const
{
	Vector v = Vector(x, y);

	v.x *= other.x;
	v.y *= other.y;

	return v;
}

Vector Vector::operator-(const Vector& other) const
{
	Vector v = Vector(x, y);

	v.x -= other.x;
	v.y -= other.y;

	return v;
}

bool Vector::operator!=(const Vector& other) const
{
	if (x == other.x && y == other.y)
		return false;
	else
		return true;
}

Vector Vector::operator/(const Vector& other) const
{
	Vector v = Vector(x, y);

	v.x /= other.x;
	v.y /= other.y;

	return v;
}

Vector Vector::operator+(const Vector& other) const
{
	Vector v = Vector(x, y);

	v.x += other.x;
	v.y += other.y;

	return v;
}

Vector Vector::operator/(float other) const
{
	Vector v = Vector(x, y);

	v.x /= other;
	v.y /= other;

	return v;
}

Vector& Vector::operator+=(const Vector& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

Vector Vector::pow1()
{
	x *= x;
	y *= y;
	return *this;
}

Vector::~Vector()
{
}
