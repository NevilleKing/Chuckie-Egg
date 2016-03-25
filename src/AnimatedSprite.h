#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "Sprite.h"
class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1, Vector location, Size size1);
	~AnimatedSprite();

	void setVelocity(Vector newVelocity) { velocity = newVelocity; };
	Vector getVelocity() { return velocity; };

	void Update(float time);

	Vector acceleration;

private: 
	Vector velocity;
};

