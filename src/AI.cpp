#include "AI.h"

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 27

#define SPRITE_WIDTH 65
#define SPRITE_HEIGHT 22

AI::AI(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, TileMap* tm, Vector velocity1, Vector location, Size size1) : Character(ren, imagePath, JSONPath, velocity1, location, size1)
{
	MOVE_SPEED = 120;
	_tilemap = tm;
	MoveRight();
	ChooseNextDestination();
}


AI::~AI()
{
}

void AI::Update(float time, std::vector<std::unique_ptr<LevelPiece>> &level, Size windowSize)
{
	if (checkIfReachedDestination())
	{
		if (_moveDirection == RIGHT)
		{
			_moveDirection = LEFT;
			MoveLeft();
		}
		else
		{
			_moveDirection = RIGHT;
			MoveRight();
		}

		ChooseNextDestination();
	}

	Character::Update(time, level, windowSize);
}

bool AI::checkIfReachedDestination()
{
	if (_moveDirection == RIGHT)
		return position.x > _destination.x * SPRITE_WIDTH;
	else
		return position.x < _destination.x * SPRITE_WIDTH;
}

void AI::ChooseNextDestination()
{
	_destination = currentPos;

	while (_tilemap->levelIntMap[(int)_destination.y][(int)_destination.x] != 1 && _tilemap->levelIntMap[(int)_destination.y + 1][(int)_destination.x] == 1)
	{
		if (_moveDirection == RIGHT)
			_destination.x++;
		else
			_destination.x--;

		if (_destination.x == 19 || _destination.x == 0)
			break;
	}

	if (_moveDirection == LEFT) _destination.x++;
}