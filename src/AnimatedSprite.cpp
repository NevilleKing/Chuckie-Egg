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
	importFromJSON(JSONPath);
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
		if (std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - last_animation_step).count() > animation_speed)
		{
			currentFrame++;
			if (currentFrame == maxFrames)
				currentFrame = 0;
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
	for (auto& element : j["frames"])
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

		maxFrames++;
	}

	if (j.count("info") == 0 || j["info"].count("speed") == 0)
		return false;

	animation_speed = float(j["info"]["speed"]) * 1000000000.0f;

	return true;
	
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
		std::string frame = "f" + std::to_string(currentFrame);
		src_rect.x = j["frames"][frame]["x"];
		src_rect.y = j["frames"][frame]["y"];
		src_rect.w = j["frames"][frame]["width"];
		src_rect.h = j["frames"][frame]["height"];

		/*rect.w = j["frames"][frame]["width"];
		rect.h = j["frames"][frame]["height"];*/
		rect.w = size.width;
		rect.h = size.height;
		rect.x = position.x - (float(j["frames"][frame]["width"]) / 2);
		rect.y = position.y - (float(j["frames"][frame]["height"]) / 2);
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
		SDL_RenderCopy(ren, texture, NULL, &rect);
	else // otherwise use the rectangle
		SDL_RenderCopy(ren, texture, &src_rect, &rect);

}