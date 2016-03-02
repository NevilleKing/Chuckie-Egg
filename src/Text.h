#pragma once
class Text
{
public:
	Text(SDL_Renderer* ren, char* fontPath, char* fontText, SDL_Rect fontRect, SDL_Color fontColour, int fontPointSize = 96);
	~Text();

	void render(SDL_Renderer* ren);
private:
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
};

