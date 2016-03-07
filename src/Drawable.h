#pragma once
class Drawable
{
public:
	void render(SDL_Renderer* ren);
protected:
	SDL_Texture* texture = NULL;
	SDL_Rect rect;
	std::string path;

	Drawable();
	~Drawable();
};

