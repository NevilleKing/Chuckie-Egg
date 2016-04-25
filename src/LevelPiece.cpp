#include "LevelPiece.h"

LevelPiece::LevelPiece(SDL_Renderer* ren, const std::string imagePath, const Vector location, const Size size1, LevelPiece::TileType tType) : Sprite(ren, imagePath, location, size1)
{
	_type = tType;
}


LevelPiece::~LevelPiece()
{
	std::cout << "Level Piece deconstructed " << this << std::endl;
}

void LevelPiece::releaseScore()
{
	if (!_scoreReleased)
		if (addScore != nullptr)
		{
			addScore(_type);
			_scoreReleased = true;
		}
}

void LevelPiece::addScoreCallback(void(*scoreFunc)(int))
{
	addScore = scoreFunc;
}

void LevelPiece::removeCallback()
{
	addScore == nullptr;
}

LevelPiece::TileType LevelPiece::getType()
{
	return _type;
}
