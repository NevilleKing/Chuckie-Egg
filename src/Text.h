#pragma once
class Text
{
public:
	// main constructor
	Text(SDL_Renderer* ren, const char* fontPath, const char* fontText, const SDL_Rect fontRect, const SDL_Color fontColour, const int fontPointSize);

	// constructor overloads
	Text(SDL_Renderer* ren, const char* fontPath, const char* fontText, const SDL_Rect fontRect, const SDL_Color fontColour) : Text(ren, fontPath, fontText, fontRect, fontColour, 96) {};
	Text(SDL_Renderer* ren, const char* fontPath, const char* fontText, const SDL_Rect fontRect) : Text(ren, fontPath, fontText, fontRect, { 255, 255, 255 }) {};
	Text(SDL_Renderer* ren, const char* fontPath, const char* fontText) : Text(ren, fontPath, fontText, { 0, 0, 100, 100 }) {};


	~Text();

	void render(SDL_Renderer* ren);
private:
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;

};

