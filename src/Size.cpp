#include "Size.h"

Size::Size()
{
	width = 0.0f;
	height = 0.0f;
}

Size::Size(float width1, float height1)
{
	width = width1;
	height = height1;
}

Size Size::operator/(float other) const
{
	Size v = Size(width, height);

	v.width /= other;
	v.height /= other;

	return v;
}


Size::~Size()
{
}
