#pragma once

#include <iostream>
#include <SDL.h>
#include <string>
#include <vector>

#include "Sprite.h"
class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1, Vector location, Size size1, const bool blank = false);
	~AnimatedSprite();

	void setVelocity(Vector newVelocity) { velocity = newVelocity; };
	Vector getVelocity() { return velocity; };

	void Update(float time);

	Vector acceleration;

	Vector velocity;
private: 
	std::vector<Sprite*> _sprites;
	void importFromJSON(std::string path);
};

