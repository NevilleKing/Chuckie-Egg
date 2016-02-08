#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


#ifdef _WIN32 // compiling on windows
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#else // NOT compiling on windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_Renderer *ren; //pointer to the SDL_Renderer
SDL_Surface *surface; //pointer to the SDL_Surface
SDL_Texture *tex; //pointer to the SDL_Texture
SDL_Surface *messageSurface; //pointer to the SDL_Surface for message
SDL_Texture *messageTexture; //pointer to the SDL_Texture for message
SDL_Rect message_rect; //SDL_rect for the message

bool done = false;

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
					case SDLK_ESCAPE: done = true;
				}
			break;
		}
	}
}
// end::handleInput[]

// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
  //CHANGE ME
}

void render()
{
		//First clear the renderer
		SDL_RenderClear(ren);

		//Draw the texture
		SDL_RenderCopy(ren, tex, NULL, NULL);

		//Draw the text
		SDL_RenderCopy(ren, messageTexture, NULL, &message_rect);

		//Update the screen
		SDL_RenderPresent(ren);
}

void cleanExit(int returnValue)
{
	if (messageTexture != nullptr) SDL_DestroyTexture(messageTexture);
	if (tex != nullptr) SDL_DestroyTexture(tex);
	if (ren != nullptr) SDL_DestroyRenderer(ren);
	if (win != nullptr) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(returnValue);
}

// based on http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
int main( int argc, char* args[] )
{
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

	std::string imagePath = "./assets/Opengl-logo.svg.png";
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr){
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (tex == nullptr){
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}


	if( TTF_Init() == -1 )
	{
		std::cout << "TTF_Init Failed: " << TTF_GetError() << std::endl;
		cleanExit(1);
	}

	TTF_Font* sans = TTF_OpenFont("./assets/Hack-Regular.ttf", 96);
	if (sans == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		cleanExit(1);
	}
	SDL_Color White = {255, 255, 255};
	messageSurface = TTF_RenderText_Solid(sans, "Hello World!", White);
	messageTexture = SDL_CreateTextureFromSurface(ren, messageSurface);
	message_rect.x = 0;
	message_rect.y = 0;
	message_rect.w = 300;
	message_rect.h = 100;

	while (!done) //loop until done flag is set)
	{
		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		SDL_Delay(20); // unless vsync is on??
	}

	cleanExit(0);
	return 0;
}
