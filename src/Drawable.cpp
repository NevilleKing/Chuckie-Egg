#include <iostream>
#include <SDL.h>
#include "Drawable.h"

Drawable::Drawable()
{
	texture = NULL;
}


Drawable::~Drawable()
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Drawable::render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, texture, NULL, &rect);
}