#include "AnimatedSprite.h"

typedef nlohmann::json json;

AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, Vector velocity1, Vector location, Size size1) : Sprite(ren, imagePath, location, size1)
{
	velocity = velocity1;
}

AnimatedSprite::AnimatedSprite(SDL_Renderer* ren, std::string imagePath, std::string JSONPath, Vector velocity1, Vector location, Size size1) : Sprite(ren, imagePath, location, size1)
{
	velocity = velocity1;
	importFromJSON(JSONPath);
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Update(float time)
{
	//velocity += acceleration * time;
	position += velocity * time;

	// update animation
	currentFrame++;
	if (currentFrame == maxFrames)
		currentFrame = 0;

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

	return true;
	
}

void AnimatedSprite::render(SDL_Renderer* ren)
{
	// set the positions of the rectangle for rendering
	// destination rect
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = size.width;
	rect.h = size.height;

	// src rect
	SDL_Rect src_rect = { 0,0,0,0 };
	if (j != nullptr)
	{
		std::string frame = "f" + std::to_string(currentFrame);
		src_rect.x = j["frames"][frame]["x"];
		src_rect.y = j["frames"][frame]["y"];
		src_rect.w = j["frames"][frame]["width"];
		src_rect.h = j["frames"][frame]["height"];
	}
	// if the width and height are zero the texture must be the full image
	if (src_rect.h == 0 && src_rect.w == 0)
		SDL_RenderCopy(ren, texture, NULL, &rect);
	else // otherwise use the rectangle
		SDL_RenderCopy(ren, texture, &src_rect, &rect);

}