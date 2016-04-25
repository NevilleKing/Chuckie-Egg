#pragma once
#include "AnimatedSprite.h"

#include <iostream>
#include <string>

#include <SDL.h>
#include "Vector.h"
#include <memory>
#include "Size.h"
#include "LevelPiece.h"
#include "Audio.h"

class Player :
	public AnimatedSprite
{
public:
	Player(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1 = Vector(), Vector location = Vector(100, 100), Size size1 = Size(100, 100));
	~Player();

	void Jump();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void StopMovingLeft();
	void StopMovingRight();
	void StopMovingUp();
	void StopMovingDown();

	void Update(float time, std::vector<std::unique_ptr<LevelPiece>> &level, Size windowSize);


	void setOnGround();

	enum MoveState {LEFT = -1, IDLE = 0, RIGHT = 1, UP = -1, DOWN = 1};

private:
	bool _isJumping = false;
	bool _isFalling = false;
	bool _isOnGround = false;
	bool _isOnLadder = false;
	MoveState _state = IDLE;
	MoveState _ladderState = IDLE;
	MoveState _afterState = IDLE;
	float _yVelocity = 0;
	float _xVelocity = 0;

	bool _walkingPlaying = false;
	int _walkingChannel = 0;

	void UpdateCollisions(std::vector<std::unique_ptr<LevelPiece>> &level, Size windowSize);

	void changeState(Player::MoveState newState, bool flip = true);
	void changeLadderState(Player::MoveState newState);
};

