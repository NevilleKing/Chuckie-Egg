#include "AI.h"

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 27

#define SPRITE_WIDTH 65
#define SPRITE_HEIGHT 22

AI::AI(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, TileMap* tm, Vector velocity1, Vector location, Size size1, Vector tilePosition) : Character(ren, imagePath, JSONPath, velocity1, location, size1)
{
	_isAI = true;
	originalPos = tilePosition;

	_destination = originalPos;

	srand(time(NULL));

	MOVE_SPEED = 120;
	_tilemap = tm;
	MoveRight();
	ChooseNextDestination();
}


AI::~AI()
{
}

void AI::UpdateEnemyCollisions(std::vector<std::unique_ptr<Character>>& players, void(*enemyCollisionCallback)(void))
{
	for (auto const& player : players)
	{
		if (player->isColliding(*this))
		{
			enemyCollisionCallback();
			return;
		}
	}
}

void AI::Update(float time, std::vector<std::unique_ptr<LevelPiece>> &level, std::vector<std::unique_ptr<Character>>& players, Size windowSize, void(*enemyCollisionCallback)(void))
{
	if (checkIfReachedDestination())
	{
		ChooseNextDestination();
	}

	UpdateEnemyCollisions(players, enemyCollisionCallback);
	Character::Update(time, level, windowSize);
}

void AI::ResetPosition()
{
	Character::ResetPosition();
	
	_destination = originalPos;
	MoveRight();
	_moveDirection = RIGHT;
	_horizontal = true;
	_onLadder = false;
	ChooseNextDestination();
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
		if (ran > 4)
		{
			if (_horizontal)
			{
				StopAllMovement();
				ran = (rand() % 10);
				if (ran > 4)
				{
					if (_tilemap->levelIntMap[(int)_destination.y - 2][(int)_destination.x] == 2)
					{
						_moveDirection = UP;
						MoveUp();
					} 
					else
					{
						_moveDirection = DOWN;
						MoveDown();
					}
				}
				else
				{
					if (_tilemap->levelIntMap[(int)_destination.y + 1][(int)_destination.x] != 1)
					{
						_moveDirection = DOWN;
						MoveDown();
					}
					else
					{
						_moveDirection = UP;
						MoveUp();
					}
				}
			}
			else
			{
				StopAllMovement();
				setOnGround();
				ran = (rand() % 10);
				_destination.y++;
				if (ran > 4)
				{
					if (_tilemap->levelIntMap[(int)_destination.y + 1][(int)_destination.x + 1] == 1)
					{
						_moveDirection = RIGHT;
						MoveRight();
					}
					else
					{
						std::cout << "Can't move right : moving left" << std::endl;
						_moveDirection = LEFT;
						MoveLeft();
					}
				}
				else
				{
					if (_tilemap->levelIntMap[(int)_destination.y + 1][(int)_destination.x - 1] == 1)
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
		if (_moveDirection == RIGHT && !_onLadder) _destination.x--;

		if (_destination.x == 0)
			_destination.x = 1;
	}
	else
	{
		_onLadder = true;
		bool needsMinus = true;
		bool firstTime = true;
		while (_tilemap->levelIntMap[(int)_destination.y][(int)_destination.x] == 2)
		{
			if (_moveDirection == UP)
				_destination.y--;
			else
				_destination.y++;

			if (_destination.y == 26 || _destination.y == 0)
				break;

			if ((_tilemap->levelIntMap[(int)_destination.y][(int)_destination.x - 1] == 1 || _tilemap->levelIntMap[(int)_destination.y][(int)_destination.x + 1] == 1) && !firstTime)
			{
				needsMinus = false;
				break;
			}

			firstTime = false;
		}

		if (_moveDirection != DOWN)
		{
			if (needsMinus)
				_destination.y++;
			else
				_destination.y -= 2;
		}
		else
		{
			_destination.y-= 2;
			position.y -= 5;
		}
	}
}