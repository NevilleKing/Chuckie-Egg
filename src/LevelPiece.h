#pragma once
#include "Sprite.h"
class LevelPiece :
	public Sprite
{
public:
	enum TileType { LADDER, EGG = 100, FOOD = 50, BIG_BIRD, DEFAULT };

	LevelPiece(SDL_Renderer* ren, const std::string imagePath, const Vector location, const Size size1, LevelPiece::TileType tType);
	~LevelPiece();

	void releaseScore();

	void addScoreCallback(void(*scoreFunc)(LevelPiece::TileType));
	void removeCallback();

	TileType getType();

private:
	TileType _type;
	void(*addScore)(LevelPiece::TileType) = nullptr;
	bool _scoreReleased = false;
};

