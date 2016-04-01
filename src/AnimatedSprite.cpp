#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1 = Vector(), Vector location = Vector(100,100), Size size1 = Size(100,100)) : Sprite(ren, imagePath, location, size1)
{
	velocity = velocity1;
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Update(float time)
{
	velocity += acceleration * time;
	position += velocity * time;
}
