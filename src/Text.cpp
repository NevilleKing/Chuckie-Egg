#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.h"

Text::Text(SDL_Renderer* ren, const char* fontPath, const char* fontText, const SDL_Rect fontRect, const SDL_Color fontColour, const int fontPointSize)
{
	path = fontPath;
	text = fontText;
	rect = fontRect;
	colour = fontColour;
	pointSize = fontPointSize;

	initFont(ren);
}

void Text::initFont(SDL_Renderer* ren)
{
	font = TTF_OpenFont(path.c_str(), pointSize);
	if (font == nullptr)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("TTF Font not initialised: ") + TTF_GetError()));
		return;
	}

	surface = TTF_RenderText_Solid(font, text.c_str(), colour);
	texture = SDL_CreateTextureFromSurface(ren, surface);
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

void Text::ChangeText(const char* newFontText, SDL_Renderer* ren)
{
	text = newFontText;
	initFont(ren);
}
