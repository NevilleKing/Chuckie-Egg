#include "Drawable.h"

Drawable::Drawable()
{
	texture = NULL;
	rect.w = 0;
	rect.h = 0;
	rect.x = 0;
	rect.y = 0;
	position = Vector();
	size = Size();
}


Drawable::~Drawable()
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Drawable::render(SDL_Renderer* ren)
{
	// set the positions of the rectangle for rendering
	rect.x = position.x;
	rect.y = position.y;
	rect.w = size.width;
	rect.h = size.height;
	// if the width and height are zero the texture must be full screen
	if (rect.h == 0 && rect.w == 0)
		SDL_RenderCopy(ren, texture, NULL, NULL);
	else // otherwise use the rectangle
		SDL_RenderCopy(ren, texture, NULL, &rect);

}