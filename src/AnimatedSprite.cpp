#include "AnimatedSprite.h"

typedef nlohmann::json json;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::steady_clock::time_point TimePoint;

AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1, Vector location, Size size1) : Sprite(ren, imagePath, location, size1)
{
	_velocity = velocity1;

	last_animation_step == Clock::now();
}

AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1, Vector location, Size size1) : Sprite(ren, imagePath, location, size1)
{
	_velocity = velocity1;
	if (!importFromJSON(JSONPath)) 
		j = nullptr;
	last_animation_step == Clock::now();
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Update(float time)
{
	position += _velocity * time;

	// update animation
	if (j != nullptr)
	{
		// limit animation
		if (std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - last_animation_step).count() > _animation_speed)
		{
			_currentFrame++;
			if (_currentFrame == _maxFrames)
				_currentFrame = 0;
			last_animation_step = Clock::now();
		}
	}
}

bool AnimatedSprite::importFromJSON(std::string path)
{
	// read in json file
	std::ifstream file;
	std::string line;
	std::string string_json = "";
	file.open(path);
	if (!file.is_open())
		return false;
	while (std::getline(file, line))
	{
		string_json += line;
	}
	file.close();

	j = json::parse(string_json);

	// for each frame
	for (auto& e : j["frames"])
	{
		for (auto& element : e)
		{
			if (element.count("x") == 0 || element.count("y") == 0 ||
				element.count("width") == 0 || element.count("height") == 0)
			{
				return false;
			}

			// check to see if all values are there and correct
			if (!element["x"].is_number() || !element["y"].is_number() ||
				!element["width"].is_number() || !element["height"].is_number())
			{
				return false;
			}
		}
	}

	// check for idle animation state
	if (j["frames"].count("IDLE") == 0)
		return false;

	_maxFrames = countChildren(j["frames"]["IDLE"]);

	if (j.count("info") == 0 || j["info"].count("speed") == 0)
		return false;

	_animation_speed = float(j["info"]["speed"]) * 1000000000.0f;

	return true;
	
}

int AnimatedSprite::countChildren(nlohmann::basic_json<> element)
{
	int frames = 0;
	// loop through to get the 
	for (auto& e : element)
	{
		frames++;
	}

	return frames;
}

void AnimatedSprite::render(SDL_Renderer* ren)
{
	// set the positions of the rectangle for rendering
	// destination rect
	SDL_Rect rect;

	// src rect
	SDL_Rect src_rect = { 0,0,0,0 };
	if (j != nullptr)
	{
		std::string frame = "f" + std::to_string(_currentFrame);
		src_rect.x = j["frames"][_animationCycle][frame]["x"];
		src_rect.y = j["frames"][_animationCycle][frame]["y"];
		src_rect.w = j["frames"][_animationCycle][frame]["width"];
		src_rect.h = j["frames"][_animationCycle][frame]["height"];

		/*rect.w = j["frames"][frame]["width"];
		rect.h = j["frames"][frame]["height"];*/
		rect.w = size.width;
		rect.h = size.height;
		rect.x = position.x - /*(float(j["frames"][frame]["width"]) / 2) -*/ (size.width / 2);
		rect.y = position.y - /*(float(j["frames"][frame]["height"]) / 2) -*/ (size.height / 2);
	}
	else
	{
		rect.x = position.x - (size.width / 2);
		rect.y = position.y - (size.height / 2);
		rect.w = size.width;
		rect.h = size.height;
	}
	// if the width and height are zero the texture must be the full image
	if (src_rect.h == 0 && src_rect.w == 0)
		SDL_RenderCopyEx(ren, texture, NULL, &rect, 0, NULL, flip);
	else // otherwise use the rectangle
		SDL_RenderCopyEx(ren, texture, &src_rect, &rect, 0, NULL, flip);

}

bool AnimatedSprite::changeAnimationCycle(std::string newAnimationCycle)
{
	if (j["frames"].count(newAnimationCycle) == 1)
	{
		_animationCycle = newAnimationCycle;
		_currentFrame = 0;
		_maxFrames = countChildren(j["frames"][_animationCycle]);
		return true;
	}

	return false;
}

void AnimatedSprite::flipAnimation(bool right)
{
	if (right)
		flip = SDL_FLIP_NONE;
	else
		flip = SDL_FLIP_HORIZONTAL;
}
