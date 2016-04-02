#pragma once

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <string>
#include <vector>

#include "Sprite.h"
#include "json.hpp"

class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1 = Vector(), Vector location = Vector(100, 100), Size size1 = Size(100, 100));
	AnimatedSprite(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1 = Vector(), Vector location = Vector(100, 100), Size size1 = Size(100, 100));

	~AnimatedSprite();

	void setVelocity(Vector newVelocity) { velocity = newVelocity; };
	Vector getVelocity() { return velocity; };

	void Update(float time);

	Vector acceleration;

	Vector velocity;

	void render(SDL_Renderer* ren);
private: 
	bool importFromJSON(std::string path);
	
	nlohmann::json j;
	int currentFrame = 0;
};

