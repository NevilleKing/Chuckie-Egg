#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <SDL.h>

#include "LevelPiece.h"
#include "AnimatedSprite.h"
#include "Character.h"

#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 27

class TileMap
{
public:
	TileMap(std::string levelFile, SDL_Renderer* ren, void(*scoreCallback)(int), std::vector<std::unique_ptr<Character>> &players);
	~TileMap();

	std::vector<std::unique_ptr<LevelPiece>> level;
	std::vector<std::unique_ptr<AnimatedSprite>> level_animated;
	int levelIntMap[LEVEL_HEIGHT][LEVEL_WIDTH];

	std::vector<Vector> enemyList;
	std::vector<Vector> enemyList2;

private:
	void readFromFile(std::string filePath, SDL_Renderer* ren, void(*scoreCallback)(int), std::vector<std::unique_ptr<Character>> &players);
};

