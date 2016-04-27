#include "AI.h"

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 27

#define SPRITE_WIDTH 65
#define SPRITE_HEIGHT 22

AI::AI(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, TileMap* tm, Vector velocity1, Vector location, Size size1) : Character(ren, imagePath, JSONPath, velocity1, location, size1)
{
	_isAI = true;
	_destination = currentPos;

	srand(time(NULL));

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
		ChooseNextDestination();
	}

	Character::Update(time, level, windowSize);
}

bool AI::checkIfReachedDestination()
{
	if (_horizontal)
	{
		if (_moveDirection == RIGHT)
			return position.x > (_destination.x * SPRITE_WIDTH) + (SPRITE_WIDTH / 2);
		else if (_moveDirection == LEFT)
			return position.x < (_destination.x * SPRITE_WIDTH) + (SPRITE_WIDTH / 2);
	}
	else
	{
		if (_moveDirection == UP)
			return position.y < (_destination.y * SPRITE_HEIGHT) + (SPRITE_HEIGHT / 2);
		else if (_moveDirection == DOWN)
			return position.y > (_destination.y * SPRITE_HEIGHT) + (SPRITE_HEIGHT / 2);
	}
	return false;
}

void AI::ChooseNextDestination()
{
	if (_onLadder)
	{
		int ran = (rand() % 10);
		std::cout << ran << std::endl;
		if (ran > 4)
		{
			if (_horizontal)
			{
				_moveDirection = UP;
				MoveUp();
			}
			else
			{
				StopMovingUp();
				ran = (rand() % 10);
				_destination.y++;
				if (ran > 4)
				{
					_moveDirection = RIGHT;
					MoveRight();
				}
				else
				{
					_moveDirection = LEFT;
					MoveLeft();
				}
			}
			_horizontal = !_horizontal;
		}
	}
	else
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
	}

	if (_horizontal)
	{
		_onLadder = false;
		bool firstTime = true;
		while ((_tilemap->levelIntMap[(int)_destination.y][(int)_destination.x] != 1 && _tilemap->levelIntMap[(int)_destination.y + 1][(int)_destination.x] == 1) || firstTime)
		{
			firstTime = false;
			if (_moveDirection == RIGHT)
				_destination.x++;
			else
				_destination.x--;

			if (_destination.x == 19 || _destination.x == 0)
				break;

			if (_tilemap->levelIntMap[(int)_destination.y][(int)_destination.x] == 2)
			{
				_onLadder = true;
				break;
			}
		}

		if (_moveDirection == LEFT && !_onLadder) _destination.x++;

		if (_destination.x == 0)
			_destination.x = 1;
	}
	else
	{
		_onLadder = true;
		bool needsMinus = true;
		while (_tilemap->levelIntMap[(int)_destination.y][(int)_destination.x] == 2)
		{
			if (_moveDirection == UP)
				_destination.y--;

			if (_destination.y == 26 || _destination.y == 0)
				break;

			if (_tilemap->levelIntMap[(int)_destination.y][(int)_destination.x - 1] == 1 || _tilemap->levelIntMap[(int)_destination.y][(int)_destination.x + 1] == 1)
			{
				needsMinus = false;
				break;
			}
		}

		if (needsMinus)
			_destination.y++;
		else
			_destination.y -= 2;
	}

	std::cout << "CALLED" << std::endl;
}