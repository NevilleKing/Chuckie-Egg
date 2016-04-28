#include "TileMap.h"

#define SPRITE_WIDTH 65
#define SPRITE_HEIGHT 22

TileMap::TileMap(std::string levelFile, SDL_Renderer* ren, void(*scoreCallback)(int), std::vector<std::unique_ptr<Character>> &players)
{
	readFromFile(levelFile, ren, scoreCallback, players);
}


TileMap::~TileMap()
{
}

void TileMap::readFromFile(std::string filePath, SDL_Renderer* ren, void(*scoreCallback)(int), std::vector<std::unique_ptr<Character>> &players)
{
	// For default each level piece is 65 wide and 22 high

	// read in level file
	std::ifstream file;
	std::string line;
	file.open(filePath);
	if (!file.is_open())
		return;
	int row = 0;
	while (std::getline(file, line))
	{
		// blank line
		if (line == "") continue;
		else
		{
			if (line.length() != 20) return; // line is not big enough
			for (int col = 0; col < line.length(); col++)
			{
				levelIntMap[row][col] = line[col] - '0';
			}
			row++;
		}
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
				break;
			case 1: // wall
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/platform.png", Vector(SPRITE_WIDTH * j + (SPRITE_WIDTH/2), SPRITE_HEIGHT * i + (SPRITE_HEIGHT / 2)), Size(SPRITE_WIDTH, SPRITE_HEIGHT), LevelPiece::DEFAULT)));
				break;
			case 2: // ladder
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/ladder.png", Vector(SPRITE_WIDTH * j + (SPRITE_WIDTH / 2), SPRITE_HEIGHT * i + (SPRITE_HEIGHT / 2)), Size(SPRITE_WIDTH, SPRITE_HEIGHT), LevelPiece::LADDER)));
				break;
			case 3: // egg
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/egg.png", Vector(SPRITE_WIDTH * j + (SPRITE_WIDTH / 2), SPRITE_HEIGHT * i + (SPRITE_HEIGHT / 2)), Size(40, 20), LevelPiece::EGG)));
				level.back()->addScoreCallback(scoreCallback);
				break;
			case 4: // grain
				level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/food.png", Vector(SPRITE_WIDTH * j + (SPRITE_WIDTH / 2), SPRITE_HEIGHT * i + (SPRITE_HEIGHT / 2)), Size(60, 15), LevelPiece::FOOD)));
				level.back()->addScoreCallback(scoreCallback);
				break;
			case 5: // enemy - have to callback to avoid circular dependancy
				enemyList.push_back(Vector(SPRITE_WIDTH * j + (SPRITE_WIDTH / 2), SPRITE_HEIGHT * i + (SPRITE_HEIGHT / 2)));
				enemyList2.push_back(Vector(j, i));
				break;
			case 6: // player start
				players.push_back(std::unique_ptr<Character>(new Character(ren, "./assets/player.png", "./assets/player.json", Vector(), Vector(SPRITE_WIDTH * j + (SPRITE_WIDTH / 2), SPRITE_HEIGHT * i + (SPRITE_HEIGHT / 2)), Size(50, 50))));
				break;
			}
		}

	}

	// add bird in top left corner
	level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/cage.png", Vector(70, 130), Size(140, 160), LevelPiece::BIG_BIRD)));
	level_animated.push_back(std::unique_ptr<AnimatedSprite>(new AnimatedSprite(ren, "./assets/bird.png", "./assets/bird.json", Vector(), level.back()->getPosition() + Vector(0, 10), Size(100, 80))));
	level_animated.back()->changeAnimationCycle("CHIRP"); // start animation
}
