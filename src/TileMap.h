#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <SDL.h>

#include "LevelPiece.h"
#include "AnimatedSprite.h"

class TileMap
{
public:
	TileMap(std::string levelFile, SDL_Renderer* ren, void(*scoreCallback)(int));
	~TileMap();

	std::vector<std::unique_ptr<LevelPiece>> level;
	std::vector<std::unique_ptr<AnimatedSprite>> level_animated;
private:
	void readFromFile(std::string filePath, SDL_Renderer* ren, void(*scoreCallback)(int));
};

