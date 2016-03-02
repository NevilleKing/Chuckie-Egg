#include "Text.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

Text::Text(SDL_Renderer* ren, char* fontPath, char* fontText, SDL_Rect fontRect, SDL_Color fontColour, int fontPointSize = 96)
{
	font = TTF_OpenFont(fontPath, fontPointSize);
	if (font == nullptr)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (std::string("TTF Font not initialised: ") + std::string(TTF_GetError())).c_str());
		return;
	}

	surface = TTF_RenderText_Solid(font, fontText, fontColour);
	texture = SDL_CreateTextureFromSurface(ren, surface);
	rect = fontRect;

}


Text::~Text()
{
	if (font != nullptr)
	{
		SDL_DestroyTexture(texture);
		delete font;
		delete surface;
	}
}

void Text::render(SDL_Renderer * ren)
{
	SDL_RenderCopy(ren, texture, NULL, &rect);
}
