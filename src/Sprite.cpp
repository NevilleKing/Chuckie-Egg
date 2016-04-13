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

	// X Axis
	float otherMinMaxX[2] = { other.getPosition().x - other.getSize().width / 2, other.getPosition().x + other.getSize().width / 2 };
	float thisMinMaxX[2] = { getPosition().x - getSize().width / 2, getPosition().x + getSize().width / 2 };

	if (!(otherMinMaxX[0] >= thisMinMaxX[0] && otherMinMaxX[0] <= thisMinMaxX[1] ||
		otherMinMaxX[1] <= thisMinMaxX[1] && otherMinMaxX[1] >= thisMinMaxX[0]))
		return false;

	// Y Axis
	float otherMinMaxY[2] = { other.getPosition().y - other.getSize().height / 2, other.getPosition().y + other.getSize().height / 2 };
	float thisMinMaxY[2] = { getPosition().y - getSize().height / 2, getPosition().y + getSize().height / 2 };

	if (!(otherMinMaxY[0] >= thisMinMaxY[0] && otherMinMaxY[0] <= thisMinMaxY[1] ||
		otherMinMaxY[1] <= thisMinMaxY[1] && otherMinMaxY[1] >= thisMinMaxY[0]))
		return false;

	return true;
}

// Returns a direction based on where the other object is in relation to this one (the objects don't have to be colliding)
Sprite::collisionDirection Sprite::checkCollisionDirection(Sprite& other)
{
	Vector otherPos = other.getPosition();
	Vector thisPos = this->getPosition();

	Size otherSize = other.getSize() / 2;
	Size thisSize = this->getSize() / 2;

	// get overlap of 2 objects
	if (thisPos.y + thisSize.height > otherPos.y - otherSize.height && (thisPos.x + thisSize.width < otherPos.x - otherSize.width || thisPos.x - thisSize.width > otherPos.x + otherSize.width))
		return Sprite::collisionDirection::UP;

	if (thisPos.y - thisSize.height < otherPos.y + otherSize.height)
		return Sprite::collisionDirection::DOWN;

	if (thisPos.x + thisSize.width > otherPos.x - otherSize.width)
		return Sprite::collisionDirection::RIGHT;

	if (thisPos.x - thisSize.width < otherPos.x + otherSize.width)
		return Sprite::collisionDirection::LEFT;

	return Sprite::collisionDirection::NO_COLLISION;
}