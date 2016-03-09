#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Drawable.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* ren, const std::string imagePath)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Constructed(%p)", this);
	auto surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("Sprite surface not initialised: ") + SDL_GetError()));
		return;
	}

	texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr) {
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("Sprite texture not initialised: ") + SDL_GetError()));
		return;
	}
}

Sprite::Sprite(SDL_Renderer * ren, const std::string imagePath, SDL_Rect spriteRect) : Sprite(ren, imagePath)
{
	rect = spriteRect;
}

Sprite::Sprite(const Sprite& sprite) {
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Constructed(%p) - Copied from(%p)", this, sprite);
}

Sprite::~Sprite()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Destructed(%p)", this);
}