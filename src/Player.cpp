#include "Player.h"

#define MOVE_SPEED 100
#define GRAVITY 100

Player::Player(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1, Vector location, Size size1) : AnimatedSprite(ren, imagePath, JSONPath, velocity1, location, size1)
{
}

Player::~Player()
{
}

void Player::Jump()
{
	if (!_isJumping)
	{
		_isJumping = true;
		setVelocity(Vector(0, -100));
	}
}

void Player::MoveLeft()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		_state2 -= 1;
	}
}

void Player::MoveRight()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		_state2 += 1;
	}
}

void Player::StopMovingLeft()
{
	_state2 += 1;
}

void Player::StopMovingRight()
{
	_state2 -= 1;
}

void Player::Update(float time) 
{
	float yvel = GRAVITY;

	setVelocity(Vector(MOVE_SPEED * _state2, yvel));

	// call base class Update function
	this->AnimatedSprite::Update(time);
}