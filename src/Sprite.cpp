#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* ren, const std::string imagePath, const Vector location, const Size size1)
{
	position = location;
	size = size1;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Constructed(%p)", this);
	auto surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("Sprite surface not initialised: ") + SDL_GetError()));
		return;
	}

	texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr) {
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, (char("Sprite texture not initialised: ") + SDL_GetError()));
		return;
	}
}

Sprite::Sprite(const Sprite& sprite) {
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Constructed(%p) - Copied from(%p)", this, sprite);
}

Sprite::~Sprite()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite Destructed(%p)", this);
}

bool Sprite::isColliding(Sprite& other)
{
	// check if the other box is inside this box

	Vector thisPosition = this->getPosition();

	// X Axis
	float otherMinMaxX[2] = { other.getPosition().x - other.getSize().width / 2, other.getPosition().x + other.getSize().width / 2 };
	float thisMinMaxX[2] = { getPosition().x - getSize().width / 2, getPosition().x + getSize().width / 2 };

	if (!(otherMinMaxX[0] >= thisMinMaxX[0] && otherMinMaxX[0] <= thisMinMaxX[1] ||
		  otherMinMaxX[1] <= thisMinMaxX[1] && otherMinMaxX[1] >= thisMinMaxX[0] ||
		  otherMinMaxX[0] <= thisPosition.x && otherMinMaxX[1] >= thisPosition.x ))
		return false;

	// Y Axis
	float otherMinMaxY[2] = { other.getPosition().y - other.getSize().height / 2, other.getPosition().y + other.getSize().height / 2 };
	float thisMinMaxY[2] = { getPosition().y - getSize().height / 2, getPosition().y + getSize().height / 2 };

	if (!(otherMinMaxY[0] >= thisMinMaxY[0] && otherMinMaxY[0] <= thisMinMaxY[1] ||
		  otherMinMaxY[1] <= thisMinMaxY[1] && otherMinMaxY[1] >= thisMinMaxY[0] ||
		  otherMinMaxY[0] <= thisPosition.y && otherMinMaxY[1] >= thisPosition.y ))
		return false;

	return true;
}

// Returns a direction based on where the other object is in relation to this one (the objects don't have to be colliding)
Sprite::collisionDirection Sprite::checkCollisionDirection(Sprite& other)
{
	Vector thisPosition = this->getPosition();
	Vector otherPosition = other.getPosition();

	Size thisSize = this->getSize();
	Size otherSize = other.getSize();

	float width = (thisSize.width + otherSize.width) / 2;
	float height = (thisSize.height + otherSize.height) / 2;

	float diffY = (thisPosition.y - otherPosition.y) * width;
	float diffX = (thisPosition.x - otherPosition.x) * height;

	if (diffY > diffX)
	{
		if (diffY > -diffX)
			return Sprite::collisionDirection::UP;
		else
			return Sprite::collisionDirection::RIGHT;
	}
	else
	{
		if (diffY > -diffX)
			return Sprite::collisionDirection::LEFT;
		else
			return Sprite::collisionDirection::DOWN;
	}
}