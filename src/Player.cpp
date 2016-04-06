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
		_onGround = false;
		_freezeY = false;
		setVelocity(Vector(0, -100));
	}
}

void Player::MoveLeft()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		std::cout << "Called" << std::endl;
		setVelocity(Vector(-100, 0));
	}
}

void Player::MoveRight()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		setVelocity(Vector(100, 0));
	}
}

void Player::setOnGround()
{
	_freezeY = true;
}
