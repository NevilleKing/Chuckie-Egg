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

std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_Renderer *ren; //pointer to the SDL_Renderer

std::map<std::string, std::unique_ptr<AnimatedSprite>> sprites; // maps std::string => sprite class. Can be called: sprites['name']

bool done = false;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::steady_clock::time_point TimePoint;

// TEMP
TimePoint prevTime;
// END TEMP

float toSeconds(float nanoseconds)
{
	return nanoseconds / 1000000000;
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
				case SDLK_2: sprites.erase(sprites.begin()); break;

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

	sprites["earth"]->acceleration = Vector(1,1) / (sprites["earth"]->getPosition() - sprites["sun"]->getPosition()).pow1();

	Vector direction = sprites["earth"]->getPosition() - sprites["sun"]->getPosition();

	sprites["earth"]->velocity = sprites["earth"]->velocity - (direction * toSeconds(currTime));

	for (auto const& spr : sprites)
		spr.second->Update(toSeconds(currTime));
}

void render()
{
		//First clear the renderer
		SDL_RenderClear(ren);

		//Draw the texture
		for (auto const& spr : sprites)
			spr.second->render(ren); // .first is the key, .second is the data

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
	win = SDL_CreateWindow("SDL Hello World!", 100, 100, 600, 600, SDL_WINDOW_SHOWN);

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

	sprites["sun"] = (std::unique_ptr<AnimatedSprite>(new AnimatedSprite(ren, "./assets/sun.png", Vector(), Vector((600 / 2) - 50,(600 / 2) - 50), Size(100,100))));
	sprites["earth"] = (std::unique_ptr<AnimatedSprite>(new AnimatedSprite(ren, "./assets/earth.png", Vector(100,0), Vector((600 / 2) - 25, (600 / 2) - 200), Size(50, 50))));


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

