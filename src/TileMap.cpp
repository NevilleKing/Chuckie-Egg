#include "TileMap.h"

#define SPRITE_WIDTH 65
#define SPRITE_HEIGHT 22

#define LEVEL_WIDTH 27
#define LEVEL_HEIGHT 20


TileMap::TileMap(std::string levelFile, SDL_Renderer* ren, void(*scoreCallback)(int))
{
	readFromFile(levelFile, ren, scoreCallback);
}


TileMap::~TileMap()
{
}

void TileMap::readFromFile(std::string filePath, SDL_Renderer* ren, void(*scoreCallback)(int))
{
	// For default each level piece is 65 wide and 22 high
	int levelIntMap[LEVEL_WIDTH][LEVEL_HEIGHT];

	// read in level file
	std::ifstream file;
	std::string line;
	file.open(filePath);
	if (!file.is_open())
		return;
	int row = 0;
	while (std::getline(file, line))
	{
		if (line.length() != 20) return; // line is not big enough
		for (int col = 0; col < line.length(); col++)
		{
			levelIntMap[row][col] = line[col] - '0';
		}
		row++;
	}
	file.close();

	// loop through and add to level
	for (int i = 0; i < LEVEL_HEIGHT; i++)
	{
		for (int j = 0; j < LEVEL_WIDTH; j++)
		{
			switch (levelIntMap[i][j])
			{
			case 0: // nothing 
				continue;
				break;
			case 1: // wall
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/platform.png", Vector(SPRITE_WIDTH * j, SPRITE_HEIGHT * i), Size(SPRITE_WIDTH, SPRITE_HEIGHT), LevelPiece::DEFAULT)));
				break;
			case 2: // ladder
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/ladder.png", Vector(SPRITE_WIDTH * j, SPRITE_HEIGHT * i), Size(SPRITE_WIDTH, SPRITE_HEIGHT), LevelPiece::LADDER)));
				break;
			case 3: // egg
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/egg.png", Vector(SPRITE_WIDTH * j, SPRITE_HEIGHT * i), Size(SPRITE_WIDTH, SPRITE_HEIGHT), LevelPiece::EGG)));
				level.back()->addScoreCallback(scoreCallback);
				break;
			case 4: // grain
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/food.png", Vector(SPRITE_WIDTH * j, SPRITE_HEIGHT * i), Size(SPRITE_WIDTH, SPRITE_HEIGHT), LevelPiece::FOOD)));
				level.back()->addScoreCallback(scoreCallback);
				break;
			}
		}
	}
}
