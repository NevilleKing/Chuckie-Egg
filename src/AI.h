#pragma once

#include "TileMap.h"
#include "Character.h"

#include <stdlib.h>
#include <time.h>

#include <chrono>

using namespace std::chrono;

class AI :
	public Character
{
public:
	AI(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, TileMap* tm, Vector velocity1 = Vector(), Vector location = Vector(100, 100), Size size1 = Size(100, 100), Vector tilePosition = Vector(0,0));
	~AI();

	void UpdateEnemyCollisions(std::vector<std::unique_ptr<Character>>& players, void(*enemyCollisionCallback)(void));

	void Update(float time, std::vector<std::unique_ptr<LevelPiece>> &level, std::vector<std::unique_ptr<Character>> &players, Size windowSize, void(*enemyCollisionCallback)(void));

	void ResetPosition();

	bool checkIfReachedDestination();

	void ChooseNextDestination();

private:
	Character::MoveState _moveDirection = LEFT;

	TileMap* _tilemap;
	bool _onLadder = false;
	bool _horizontal = true;

	Vector _destination;
	Vector originalPos = Vector(0, 25);
};

