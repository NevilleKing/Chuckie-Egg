#pragma once
#include "Sprite.h"
class LevelPiece :
	public Sprite
{
public:
	enum TileType { LADDER, EGG, FOOD, DEFAULT };

	LevelPiece(SDL_Renderer* ren, const std::string imagePath, const Vector location, const Size size1, LevelPiece::TileType tType);
	~LevelPiece();

	TileType getType();

private:
	TileType _type;
};

