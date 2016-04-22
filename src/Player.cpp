#include "Player.h"

#define MOVE_SPEED 200
#define GRAVITY 150

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
		_afterJump = _state;
		_isJumping = true;
		_isOnGround = false;
		_yVelocity = -100;
	}
}

void Player::MoveLeft()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		_state = LEFT;
	}
	else
	{
		_afterJump = LEFT;
	}
}

void Player::MoveRight()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		_state = RIGHT;
	}
	else
	{
		_afterJump = RIGHT;
	}
}

void Player::StopMovingLeft()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		if (_state == LEFT) _state = IDLE;
	}
	else
	{
		if (_afterJump == LEFT)  _afterJump = IDLE;
	}
}

void Player::StopMovingRight()
{
	if (!_isJumping) // when jumping no movement can occur
	{
		if (_state == RIGHT)  _state = IDLE;
	}
	else
	{
		if (_afterJump == RIGHT)  _afterJump = IDLE;
	}
}

void Player::setOnGround()
{
	_isOnGround = true;
	if (_isJumping)
	{
		_state = _afterJump; // reset state just in case player was jumping left or right
		_isJumping = false;
	}
}

void Player::UpdateCollisions(const std::vector<std::unique_ptr<Sprite>> &level)
{
	for (int i = 0; i < level.size(); i++)
	{
		if (level[i]->isColliding(*this))
		{
			if (i==1) std::cout << this->checkCollisionDirection(*level[i]) << std::endl;
			if (this->checkCollisionDirection(*level[i]) == Sprite::collisionDirection::DOWN)
				this->setOnGround();
		}
	}
}

void Player::Update(float time, const std::vector<std::unique_ptr<Sprite>> &level)
{
	if (!_isOnGround)
	{
		if (_yVelocity < GRAVITY)
			_yVelocity += GRAVITY * time;
		else
			_yVelocity = GRAVITY;
	}
	else
	{
		_yVelocity = 0;
		_isOnGround = false;
	}

	setVelocity(Vector(MOVE_SPEED * _state, _yVelocity));

	// call base class Update function
	this->AnimatedSprite::Update(time);

	UpdateCollisions(level);
}