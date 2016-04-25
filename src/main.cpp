#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <map>

#include <random>
#include <time.h>
#include <chrono>
#include <math.h>

#ifdef _WIN32 // compiling on windows
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else // NOT compiling on windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

// custom classes
#include "Text.h"
#include "AnimatedSprite.h"
#include "Size.h"
#include "Vector.h"
#include "Audio.h"
#include "Player.h"
#include "LevelPiece.h"
#include "TileMap.h"

std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_Renderer *ren; //pointer to the SDL_Renderer

std::unique_ptr<Player> player;

std::unique_ptr<TileMap> levelMap;

bool done = false;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::steady_clock::time_point TimePoint;

Size windowSize = Size(1300, 594);
Vector windowPosition = Vector(50, 50);

bool _isPaused = false;

// TEMP
TimePoint prevTime;
std::map<std::string, std::unique_ptr<Text>> texts;
int score = 0;
std::unique_ptr<Text> scoreTxt;
// END TEMP

float toSeconds(float nanoseconds)
{
	return nanoseconds / 1000000000;
}

void addScore(int scoreToAdd)
{
	score += scoreToAdd;
	std::stringstream ss;
	ss << std::setw(6) << std::setfill('0') << score;
	scoreTxt->ChangeText(ss.str(), ren);
}

void handleInput()
{
	//Event-based input handling
	//The underlying OS is event-based, so **each** key-up or key-down (for example)
	//generates an event.
	//  - https://wiki.libsdl.org/SDL_PollEvent
	//In some scenarios we want to catch **ALL** the events, not just to present state
	//  - for instance, if taking keyboard input the user might key-down two keys during a frame
	//    - we want to catch based, and know the order
	//  - or the user might key-down and key-up the same within a frame, and we still want something to happen (e.g. jump)
	//  - the alternative is to Poll the current state with SDL_GetKeyboardState

	SDL_Event event; //somewhere to store an event

	//NOTE: there may be multiple events per frame
	while (SDL_PollEvent(&event)) //loop until SDL_PollEvent returns 0 (meaning no more events)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			done = true; //set donecreate remote branch flag if SDL wants to quit (i.e. if the OS has triggered a close event,
							//  - such as window close, or SIGINT
			break;

			//keydown handling - we should to the opposite on key-up for direction controls (generally)
		case SDL_KEYDOWN:
			//Keydown can fire repeatable if key-repeat is on.
			//  - the repeat flag is set on the keyboard event, if this is a repeat event
			//  - in our case, we're going to ignore repeat events
			//  - https://wiki.libsdl.org/SDL_KeyboardEvent
			if (!event.key.repeat)
				switch (event.key.keysym.sym)
				{
					//hit escape to exit
				case SDLK_ESCAPE: done = true; break;
				case SDLK_SPACE: 
					if (!_isPaused) player->Jump();
					break;
				case SDLK_LEFT:
					if (!_isPaused) player->MoveLeft();
					break;
				case SDLK_RIGHT:
					if (!_isPaused) player->MoveRight();
					break;
				case SDLK_UP:
					if (!_isPaused) player->MoveUp();
					break;
				case SDLK_DOWN:
					if (!_isPaused) player->MoveDown();
					break;
				case SDLK_p:
					_isPaused = !_isPaused; // toggle pause
				}
			break;
		case SDL_KEYUP:
			if (!event.key.repeat)
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					if (!_isPaused) player->StopMovingLeft();
					break;
				case SDLK_RIGHT:
					if (!_isPaused) player->StopMovingRight();
					break;
				case SDLK_UP:
					if (!_isPaused) player->StopMovingUp();
					break;
				case SDLK_DOWN:
					if (!_isPaused) player->StopMovingDown();
					break;
				}
			break;
		}
	}
}
// end::handleInput[]

// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
	// Time since last frame
	auto currTime = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - prevTime).count();
	prevTime = Clock::now();

	player->Update(toSeconds(currTime), levelMap->level, windowSize);
}

void render()
{
	// check pause state
	if (_isPaused)
	{
		if (texts.find("PAUSE") == texts.end())
			texts["PAUSE"] = std::unique_ptr<Text>(new Text(ren, "./assets/Hack-Regular.ttf", "PAUSED", { 255,255,255 }, Size(250, 100), Vector(windowSize.width/2, windowSize.height/2), 150)); // create pause text in middle of screen
	}
	else
	{
		if (texts.find("PAUSE") != texts.end())
			texts.erase("PAUSE");
	}

	//First clear the renderer
	SDL_RenderClear(ren);

	//Draw the level on screen
	for (auto const& spr : levelMap->level)
		spr->render(ren);

	//Draw the text on screen
	for (auto const& spr : texts)
		spr.second->render(ren);

	player->render(ren);

	scoreTxt->render(ren);

	//Update the screen
	SDL_RenderPresent(ren);
}

void cleanExit(int returnValue)
{
	if (ren != nullptr) SDL_DestroyRenderer(ren);
	if (win != nullptr) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(returnValue);
}

// based on http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
int main( int argc, char* args[] )
{
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL initialised OK!\n";

	//create window
	win = SDL_CreateWindow("Chuckie Egg", windowPosition.x, windowPosition.y, windowSize.width, windowSize.height, SDL_WINDOW_SHOWN);

	//error handling
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL CreatedWindow OK!\n";

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	if( TTF_Init() == -1 )
	{
		std::cout << "TTF_Init Failed: " << TTF_GetError() << std::endl;
		cleanExit(1);
	}

	//Audio::init();

	//Audio::Load_SFX("./assets/music1.mp3", "YaySound");

	//SFX = Audio::Fade_In_SFX("YaySound", 10.0f);

	player = (std::unique_ptr<Player>(new Player(ren, "./assets/player.png", "./assets/walking.json", Vector(), Vector(550, 0), Size(50, 50))));

	//level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/platform.png", Vector(650, 500), Size(1500, 25), LevelPiece::TileType::DEFAULT)));

	//level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/box.png", Vector(650, 400), Size(200, 150), LevelPiece::TileType::DEFAULT)));

	//level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/ladder.png", Vector(900, 400), Size(50, 150), LevelPiece::TileType::LADDER)));
	//
	//level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/egg.png", Vector(200, 450), Size(20, 20), LevelPiece::TileType::EGG)));
	//level.back()->addScoreCallback(addScore);

	//level.push_back(std::unique_ptr<LevelPiece>(new LevelPiece(ren, "./assets/food.png", Vector(1000, 475), Size(20,20), LevelPiece::TileType::FOOD)));
	//level.back()->addScoreCallback(addScore);

	texts["SCORE"] = (std::unique_ptr<Text>(new Text(ren, "./assets/Hack-Regular.ttf", "SCORE", { 255,0,255 }, Size(100, 50), Vector(70, 30), 25)));

	scoreTxt = (std::unique_ptr<Text>(new Text(ren, "./assets/Hack-Regular.ttf", "000000", { 255,0,255 }, Size(100, 50), Vector(200, 30), 25)));

	levelMap = std::unique_ptr<TileMap>(new TileMap("./assets/level1.txt", ren, addScore));

	if (!Audio::init())
	{
		std::cout << "Issue loading Audio" << std::endl;
	}
	else
	{
		Audio::Load_SFX("./assets/audio/bgMusic.mp3", "Music");
		Audio::Load_SFX("./assets/audio/pickups.wav", "Pickup");
		Audio::Load_SFX("./assets/audio/walk.wav", "Walk");

		Audio::Set_SFX_Volume(30, "Music");
		Audio::Fade_In_SFX("Music", 5.0f);
	}

	prevTime = Clock::now();

	while (!done) //loop until done flag is set)
	{
		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		//SDL_Delay(20); // unless vsync is on??
	}

	cleanExit(0);
	return 0;
}

