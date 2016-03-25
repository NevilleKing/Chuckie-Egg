#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, float velocity1 = 0) : Sprite(ren, imagePath)
{
	velocity = velocity1;
}


AnimatedSprite::~AnimatedSprite()
{
}
