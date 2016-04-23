#pragma once
#include "AnimatedSprite.h"

#include <iostream>
#include <string>

#include <SDL.h>
#include "Vector.h"
#include <memory>
#include "Size.h"
#include "LevelPiece.h"

class Player :
	public AnimatedSprite
{
public:
	Player(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1 = Vector(), Vector location = Vector(100, 100), Size size1 = Size(100, 100));
	~Player();

	void Jump();
	void MoveLeft();
	void MoveRight();

	void StopMovingLeft();

	void StopMovingRight();

	void Update(float time, const std::vector<std::unique_ptr<LevelPiece>> &level, Size windowSize);


	void setOnGround();

	enum MoveState {LEFT = -1, IDLE = 0, RIGHT = 1};

private:
	bool _isJumping = false;
	bool _isFalling = false;
	bool _isOnGround = false;
	MoveState _state = IDLE;
	MoveState _afterState = IDLE;
	float _yVelocity = 0;

	void UpdateCollisions(const std::vector<std::unique_ptr<LevelPiece>> &level, Size windowSize);

	void changeState(Player::MoveState newState, bool flip = true);
};

