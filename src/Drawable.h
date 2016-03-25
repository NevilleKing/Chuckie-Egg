#pragma once

#include <iostream>
#include <SDL.h>

#include "Vector.h"
#include "Size.h"

class Drawable
{
public:
	void render(SDL_Renderer* ren);
protected:
	SDL_Texture* texture = NULL;
	std::string path;

	Vector position;
	Size size;

	Drawable();
	~Drawable();

private:
	SDL_Rect rect;
};

