#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, float velocity1 = 0, Vector location = Vector(100,100), Size size1 = Size(100,100)) : Sprite(ren, imagePath, location, size1)
{
	velocity = velocity1;
}


AnimatedSprite::~AnimatedSprite()
{
}
