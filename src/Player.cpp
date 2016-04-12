#include "Player.h"

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
		_freezeY = false;
		setVelocity(Vector(0, -100));
	}
}

void Player::MoveLeft()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		if (_state == MOVING_RIGHT) _state = IDLE;
		else _state = MOVING_LEFT;
	}
}

void Player::MoveRight()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		if (_state == MOVING_LEFT) _state = IDLE;
		else _state = MOVING_RIGHT;
	}
}

void Player::StopMovingLeft()
{
	if (_state == MOVING_LEFT) _state = IDLE;
}

void Player::StopMovingRight()
{
	if (_state == MOVING_RIGHT) _state = IDLE;
}

void Player::setOnGround()
{
	_freezeY = true;
}

void Player::Update(float time) 
{
	setVelocity(Vector(100 * _state, 0));

	this->AnimatedSprite::Update(time);
}