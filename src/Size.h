#pragma once
class Size
{
public:
	Size();
	Size(float width1, float height1);
	Size operator/(float other) const;
	Size operator-(const Size & other) const;
	~Size();

	float width;
	float height;
};

