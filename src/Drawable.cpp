#include "Drawable.h"

Drawable::Drawable()
{
	texture = NULL;
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
	SDL_Rect rect;
	rect.x = position.x - (size.width / 2);
	rect.y = position.y - (size.height / 2);
	rect.w = size.width;
	rect.h = size.height;
	// if the width and height are zero the texture must be full screen
	if (rect.h == 0 && rect.w == 0)
		SDL_RenderCopy(ren, texture, NULL, NULL);
	else // otherwise use the rectangle
		SDL_RenderCopy(ren, texture, NULL, &rect);
	

}