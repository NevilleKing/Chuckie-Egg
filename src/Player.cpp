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

void Player::UpdateCollisions(const std::vector<std::unique_ptr<Sprite>> &level, Size windowSize)
{
	// check level collisions
	for (int i = 0; i < level.size(); i++)
	{
		if (level[i]->isColliding(*this))
		{
			switch (this->checkCollisionDirection(*level[i]))
			{
			case Sprite::collisionDirection::DOWN:
				this->setOnGround();
				break;
			case Sprite::collisionDirection::UP:
				if (_yVelocity < 0) _yVelocity = 0;
				break;
			case Sprite::collisionDirection::LEFT:
				if (_isJumping) _state = RIGHT;
				else if (_state == LEFT)
					_state = IDLE;
				break;
			case Sprite::collisionDirection::RIGHT:
				if (_isJumping) _state = LEFT;
				else if (_state == RIGHT)
					_state = IDLE;
				break;
			}
		}
	}

	// check collisions with window
	float minX = this->getPosition().x - (this->getSize().width / 2);
	float maxX = this->getPosition().x + (this->getSize().width / 2);
	float minY = this->getPosition().y + (this->getSize().height / 2);
	float maxY = this->getPosition().y - (this->getSize().height / 2);

	// left
	if (minX < 0)
	{
		if (_isJumping) _state = RIGHT;
		else if (_state == LEFT)
			_state = IDLE;
	}
	// right
	else if (maxX > windowSize.width)
	{
		if (_isJumping) _state = LEFT;
		else if (_state == RIGHT)
			_state = IDLE;
	}
}

void Player::Update(float time, const std::vector<std::unique_ptr<Sprite>> &level, Size windowSize)
{
	if (!_isOnGround)
	{
		if (_isJumping)
		{
			if (_yVelocity < GRAVITY)
				_yVelocity += GRAVITY * time;
			else
				_yVelocity = GRAVITY;
		}
		else
		{
			_yVelocity = GRAVITY;
		}
		if (!_isJumping) _state = IDLE;
	}
	else
	{
		_yVelocity = 0;
		_isOnGround = false;
	}

	setVelocity(Vector(MOVE_SPEED * _state, _yVelocity));

	// call base class Update function
	this->AnimatedSprite::Update(time);

	UpdateCollisions(level, windowSize);
}