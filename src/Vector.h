#pragma once
class Vector
{
public:
	Vector();
	Vector(float x1, float y1);
	~Vector();

	float x;
	float y;

	Vector operator*(float other) const;
	Vector operator*(const Vector & other) const;
	Vector operator-(const Vector& other) const;
	Vector& Vector::operator+=(const Vector& other);
	Vector & operator-=(const Vector & other);
	Vector Vector::operator/(const Vector& other) const;

	Vector operator+(const Vector & other) const;

	Vector operator/(float other) const;

	bool Vector::operator!=(const Vector& other) const;

	Vector pow1();
};

