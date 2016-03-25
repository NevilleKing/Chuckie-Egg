#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "Sprite.h"
class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(SDL_Renderer* ren, std::string imagePath, float velocity1, Vector location, Size size1);
	~AnimatedSprite();

	void setVelocity(float newVelocity) { velocity = newVelocity; };
	float getVelocity() { return velocity; };
private: 
	float velocity;
};

