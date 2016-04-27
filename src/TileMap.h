#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <SDL.h>

#include "LevelPiece.h"
#include "AnimatedSprite.h"
#include "AI.h"

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 27

class TileMap
{
public:
	TileMap(std::string levelFile, SDL_Renderer* ren, void(*scoreCallback)(int));
	~TileMap();

	std::vector<std::unique_ptr<LevelPiece>> level;
	std::vector<std::unique_ptr<AnimatedSprite>> level_animated;
	int levelIntMap[LEVEL_HEIGHT][LEVEL_WIDTH];

	std::vector<std::unique_ptr<AI>> enemies;

	std::vector<std::unique_ptr<Character>> players;

private:
	void readFromFile(std::string filePath, SDL_Renderer* ren, void(*scoreCallback)(int));
};

