#include "Character.h"

#define GRAVITY 150

Character::Character(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1, Vector location, Size size1) : AnimatedSprite(ren, imagePath, JSONPath, velocity1, location, size1)
{
	_originalLocation = location;
}

Character::~Character()
{
}

void Character::Jump()
{
	if (!_isJumping && (_isOnLadder || !_isFalling))
	{
		if (_isOnLadder)
		{
			changeState(_afterState);
		}
		else
			_afterState = _state;
		_isJumping = true;
		_isOnGround = false;
		_yVelocity = -100;
		Audio::Play_SFX("Jump");
	}
}

void Character::MoveLeft()
{
	if (!_isJumping && !_isFalling || _isAI) // when jumping no movement can occur
	{
		changeState(LEFT);
	}
	else
	{
		_afterState = LEFT;
	}
}

void Character::MoveRight()
{
	if (!_isJumping && !_isFalling || _isAI) // when jumping no movement can occur
	{
		changeState(RIGHT);
	}
	else
	{
		_afterState = RIGHT;
	}
}

void Character::MoveUp()
{
	if (_isOnLadder)
		changeLadderState(UP);
}

void Character::MoveDown()
{
	if (_isOnLadder)
		changeLadderState(DOWN);
}

void Character::StopMovingLeft()
{
	if (!_isJumping && !_isFalling) // when jumping no movement can occur
	{
		if (_state == LEFT) changeState(IDLE);

	}
	else
	{
		if (_afterState == LEFT)  _afterState = IDLE;
	}
}

void Character::StopMovingRight()
{
	if (!_isJumping && !_isFalling) // when jumping no movement can occur
	{
		if (_state == RIGHT) changeState(IDLE);
	}
	else
	{
		if (_afterState == RIGHT)  _afterState = IDLE;
	}
}

void Character::StopMovingUp()
{
	if (_ladderState == UP) changeLadderState(IDLE);
}

void Character::StopMovingDown()
{
	if (_ladderState == DOWN) changeLadderState(IDLE);
}

void Character::StopAllMovement()
{
	_afterState = IDLE;
	changeLadderState(IDLE);
	changeState(IDLE);
}

void Character::ResetPosition()
{
	changeState(IDLE);
	changeLadderState(IDLE);
	position = _originalLocation;
}

void Character::setOnGround()
{
	if (_isJumping && _yVelocity > 0)
	{
		changeState(_afterState); // reset state just in case player was jumping left or right
		_isJumping = false;
	}
	else
		_isOnGround = true;

	if (_isFalling)
	{
		if (!_isOnLadder) changeState(_afterState);
		_isFalling = false;
	}
}

void Character::UpdateCollisions(std::vector<std::unique_ptr<LevelPiece>> &level, Size windowSize)
{
	// reset variables
	_isOnLadder = false;
	_isOnGround = false;

	// check level collisions
	for (int i = 0; i < level.size(); i++)
	{
		if (level[i]->isColliding(*this))
		{
			switch (level[i]->getType())
			{
			case LevelPiece::TileType::BIG_BIRD:
				// no collision
				break;
			case LevelPiece::TileType::LADDER:
				_isOnLadder = true;
				break;
			case LevelPiece::TileType::EGG:
				if (!_isAI)
				{
					level[i]->releaseScore();
					level.erase(level.begin() + i);
					Audio::Play_SFX("Pickup");
				}
				break;
			case LevelPiece::TileType::FOOD:
				if (!_isAI)
				{
					level[i]->releaseScore();
					level.erase(level.begin() + i);
					Audio::Play_SFX("Pickup");
				}
				break;
			default:
				switch (this->checkCollisionDirection(*level[i]))
				{
				case Sprite::collisionDirection::DOWN:
					if (this->position.y + this->size.height / 2 > level[i]->getPosition().y - level[i]->getSize().height / 2)     // just in case the player is stuck inside the floor (player will reset to above
						this->position.y = (level[i]->getPosition().y - level[i]->getSize().height / 2) - (this->size.height / 2); // the floor to stop collisions with the right & left of other objects)
					_isOnGround = true;
					break;
				case Sprite::collisionDirection::UP:
					if (_yVelocity < 0) _yVelocity = 0;
					break;
				case Sprite::collisionDirection::LEFT:
					if (_isJumping) changeState(RIGHT, false);
					else if (_state == LEFT)
						changeState(IDLE);
					break;
				case Sprite::collisionDirection::RIGHT:
					if (_isJumping) changeState(LEFT, false);
					else if (_state == RIGHT)
						changeState(IDLE);
					break;
				}
				break;
			}
		}
	}

	if (_isOnGround) this->setOnGround();

	// check collisions with window
	float minX = this->getPosition().x - (this->getSize().width / 2);
	float maxX = this->getPosition().x + (this->getSize().width / 2);
	float minY = this->getPosition().y + (this->getSize().height / 2);
	float maxY = this->getPosition().y - (this->getSize().height / 2);

	// left
	if (minX < 0)
	{
		if (_isJumping) changeState(RIGHT, false);
		else if (_state == LEFT)
			changeState(IDLE);
	}
	// right
	else if (maxX > windowSize.width)
	{
		if (_isJumping) changeState(LEFT, false);
		else if (_state == RIGHT)
			changeState(IDLE);
	}
}

void Character::Update(float time, std::vector<std::unique_ptr<LevelPiece>> &level, Size windowSize)
{
	UpdateCollisions(level, windowSize);

	_xVelocity = _state;
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
			if (!_isFalling) _afterState = _state;
			_isFalling = true;
		}
		if (!_isJumping && !_isOnLadder)
			changeState(IDLE);
		else if (_isOnLadder && _ladderState != IDLE)
			_state = IDLE;
	}
	else
	{
		if (_yVelocity > 0) _yVelocity = 0;
	}

	if (_isOnLadder && (!_isJumping || _ladderState != IDLE))
	{
		_isJumping = false;
		if (_isJumping) _afterState = IDLE;
		_yVelocity = MOVE_SPEED * _ladderState;
		if (_isOnGround && _yVelocity > 0) _yVelocity = 0;
		if (_isOnGround && _ladderState == DOWN) changeLadderState(IDLE);
	}

	// Audio
	if (_state != IDLE && !_isJumping)
	{
		if (!_walkingPlaying)
		{
			_walkingChannel = Audio::Play_SFX_Looping("Walk", -1);
			_walkingPlaying = true;
		}
		else
		{
			Audio::Set_SFX_Panning_Based_On_Position(_walkingChannel, this->position, windowSize.width);
		}
	}
	else
	{
		if (_walkingPlaying)
		{
			Audio::Stop_SFX(_walkingChannel);
			_walkingPlaying = false;
		}
	}

	if (_ladderState != IDLE && _isOnLadder)
	{
		if (!_ladderClimbPlaying)
		{
			_ladderClimbChannel = Audio::Play_SFX_Looping("LadderClimb", -1);
			_ladderClimbPlaying = true;
		}
		else
		{
			Audio::Set_SFX_Panning_Based_On_Position(_ladderClimbChannel, this->position, windowSize.width);
		}
	}
	else
	{
		if (_ladderClimbPlaying)
		{
			Audio::Stop_SFX(_ladderClimbChannel);
			_ladderClimbPlaying = false;
		}
	}

	setVelocity(Vector(MOVE_SPEED * _xVelocity, _yVelocity));

	// call base class Update function
	this->AnimatedSprite::Update(time);
}

void Character::changeState(Character::MoveState newState, bool flip)
{
	_state = newState;
	switch (_state)
	{
	case LEFT:
		changeAnimationCycle("WALK");
		if (flip) flipAnimation(false);
		break;
	case IDLE:
		if (flip) changeAnimationCycle("IDLE");
		break;
	case RIGHT:
		changeAnimationCycle("WALK");
		if (flip) flipAnimation(true);
	}
}

void Character::changeLadderState(Character::MoveState newState)
{
	_ladderState = newState;
	switch (_ladderState)
	{
	case UP:
	case DOWN:
		changeAnimationCycle("LADDER");
		break;
	case IDLE:
		changeAnimationCycle("LADDER_IDLE");
		break;
	}
}