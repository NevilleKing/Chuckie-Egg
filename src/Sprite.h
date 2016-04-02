#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Vector.h"
#include "Size.h"

#include "Drawable.h"

class Sprite : public Drawable
{
public:
	Sprite(SDL_Renderer* ren, const std::string imagePath, const Vector location = Vector(100,100), const Size size1 = Size(100,100), const bool blank = false);
	~Sprite();
	bool isColliding(Sprite & other);
	Sprite(const Sprite& sprite);
};

