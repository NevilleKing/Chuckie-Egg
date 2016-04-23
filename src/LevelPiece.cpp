#include "LevelPiece.h"

LevelPiece::LevelPiece(SDL_Renderer* ren, const std::string imagePath, const Vector location, const Size size1, LevelPiece::TileType tType) : Sprite(ren, imagePath, location, size1)
{
	_type = tType;
}


LevelPiece::~LevelPiece()
{
}

LevelPiece::TileType LevelPiece::getType()
{
	return _type;
}
