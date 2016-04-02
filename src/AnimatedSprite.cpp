#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1 = Vector(), Vector location = Vector(100,100), Size size1 = Size(100,100), const bool blank) : Sprite(ren, imagePath, location, size1, blank)
{
	velocity = velocity1;

	if (!blank)
		importFromJSON(imagePath);
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Update(float time)
{
	//velocity += acceleration * time;
	position += velocity * time;
}

void AnimatedSprite::importFromJSON(std::string path)
{

}
