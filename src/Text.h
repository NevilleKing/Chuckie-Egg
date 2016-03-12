#pragma once
#include "Drawable.h"
class Text : public Drawable
{
public:
	// main constructor
	Text(SDL_Renderer* ren, const std::string fontPath, const std::string fontText, const SDL_Rect fontRect, const SDL_Color fontColour, const int fontPointSize);

	// constructor overloads
	Text(SDL_Renderer* ren, const std::string fontPath, const std::string fontText, const SDL_Rect fontRect, const SDL_Color fontColour) : Text(ren, fontPath, fontText, fontRect, fontColour, 96) {};
	Text(SDL_Renderer* ren, const std::string fontPath, const std::string fontText, const SDL_Rect fontRect) : Text(ren, fontPath, fontText, fontRect, { 255, 255, 255 }) {};
	Text(SDL_Renderer* ren, const std::string fontPath, const std::string fontText) : Text(ren, fontPath, fontText, { 0, 0, 100, 100 }) {};

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

