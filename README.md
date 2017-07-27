# Chuckie Egg
![chuckieegg](https://user-images.githubusercontent.com/9254173/28695775-290fccfc-7329-11e7-9c71-78f2b30b4acc.png)

A clone of the game Chuckie Egg originally released in 1983. This version using SDL 2 (among other helper libraries) in C++, for the
Games Programming module at the University of Lincoln.

## Playing the Game
The easiest way to download the game is via the [releases page](https://github.com/NevilleKing/Chuckie-Egg/releases/latest).

If you have visual studio, you can also generate an sln file by using premake from the command line:

    premake5.bat vs2015
    
Default controls are:

###### Player 1
- WASD - move
- SPACE - jump
###### Player 2
- Arrow Keys - move
- Left CTRL - jump

## Features
Here is a list of extra features:
- Key remapping - within the assets folder, see the `keys1.txt` and `keys2.txt` for player 1 and 2 respectively. Each control is on a different line, in the order UP, DOWN, LEFT, RIGHT, JUMP. The keys are represented using SDL key codes found [here](https://wiki.libsdl.org/SDL_Keycode)
- A tilemap is used for the levels, read in from seperate files
- Animations use a sprite map, with data held in a JSON file and parsed at runtime
- High score is stored persistently
- The simulation accounts for real time, using std::chrono
- Window resizing - also press F11 for full screen
- Press p for a menu
- Audio can be adjusted using `-` (down) and `=` (up)
- The player movement audio uses panning (use headphones for best effect)

## Dependencies
The game uses the following dependencies:
- glew
- glm
- premake
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf
- JSON for modern C++ (see [repo](https://github.com/nlohmann/json))

Also thanks to Kevin MacLeod for the background music.
