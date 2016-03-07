#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Drawable.h"
#include "Text.h"

Text::Text(SDL_Renderer* ren, const std::string fontPath, const std::string fontText, const SDL_Rect fontRect, const SDL_Color fontColour, const int fontPointSize)
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
	if (texture != NULL) 
		SDL_DestroyTexture(texture);
	auto font = TTF_OpenFont(path.c_str(), pointSize);
	if (font == nullptr)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("TTF Font not initialised: ") + TTF_GetError()));
		return;
	}

	auto surface = TTF_RenderText_Solid(font, text.c_str(), colour);
	texture = SDL_CreateTextureFromSurface(ren, surface);

	// cleanup
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
}

Text::~Text()
{
}

void Text::ChangeText(const std::string newFontText, SDL_Renderer* ren)
{
	text = newFontText;
	initFont(ren);
}

void Text::ChangeFont(const std::string newFontPath, SDL_Renderer* ren)
{
	path = newFontPath;
	initFont(ren);
}
