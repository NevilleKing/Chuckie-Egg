#pragma once

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <string>
#include <vector>
#include <chrono>

#include "Sprite.h"
#include "json.hpp"

class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1 = Vector(), Vector location = Vector(100, 100), Size size1 = Size(100, 100));
	AnimatedSprite(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1 = Vector(), Vector location = Vector(100, 100), Size size1 = Size(100, 100));

	~AnimatedSprite();

	void setVelocity(Vector newVelocity) { _velocity = newVelocity; };
	Vector getVelocity() { return _velocity; };

	void setAcceleration (Vector newAcceleration) { _acceleration = newAcceleration; };
	Vector getAcceleration() { return _acceleration; };

	void Update(float time);

	void render(SDL_Renderer* ren);
private: 
	bool importFromJSON(std::string path);
	
	nlohmann::json j;
	int currentFrame = 0;
	int maxFrames = 0;

	std::chrono::steady_clock::time_point last_animation_step;

	int animation_speed = 0; // in nano seconds

	Vector _velocity;
	Vector _acceleration;

protected:
	bool _freezeY = false;
};

