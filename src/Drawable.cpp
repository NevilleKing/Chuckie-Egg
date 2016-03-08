#include <iostream>
#include <SDL.h>
#include "Drawable.h"

Drawable::Drawable()
{
	texture = NULL;
	rect.w = 0;
	rect.h = 0;
	rect.x = 0;
	rect.y = 0;
}


Drawable::~Drawable()
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Drawable::render(SDL_Renderer* ren)
{
	if (rect.h == 0 && rect.w == 0)
		SDL_RenderCopy(ren, texture, NULL, NULL);
	else 
		SDL_RenderCopy(ren, texture, NULL, &rect);

}