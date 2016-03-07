#pragma once
#include "Drawable.h"
class Sprite : public Drawable
{
public:
	Sprite(SDL_Renderer* ren, const std::string imagePath);
	~Sprite();
	Sprite(const Sprite& sprite);
};

