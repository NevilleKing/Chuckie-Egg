#pragma once
class Sprite
{
public:
	Sprite(SDL_Renderer* ren, const std::string imagePath);
	~Sprite();
	Sprite(const Sprite& sprite);

	void render(SDL_Renderer* ren);

private:
	SDL_Texture* texture;
};

