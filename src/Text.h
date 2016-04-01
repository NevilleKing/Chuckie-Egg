#pragma once

#include "Drawable.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Vector.h"
#include "Size.h"

class Text : public Drawable
{
public:
	// main constructor
	Text(SDL_Renderer* ren, const std::string fontPath, const std::string fontText, const SDL_Color fontColour, const Size size1, const Vector location, const int fontPointSize);

	Text(const Text& t);
	~Text();

	void ChangeText(const std::string newFontText, SDL_Renderer* ren);
	void ChangeFont(const std::string newFontPath, SDL_Renderer* ren);

private:
	std::string text;
	SDL_Color colour;
	int pointSize;

	void initFont(SDL_Renderer* ren);
};

