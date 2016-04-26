#pragma once

#include <iostream>
#include <SDL.h>
#include <memory>
#include <vector>

#include "Text.h"
#include <map>
#include "Size.h"

class Menu
{
public:
	Menu();
	~Menu();

	void renderMenu(SDL_Renderer* ren);

	void addText(Text* txtToAdd, void(*callbackFunction)(const Text*));

	void clickMenuItem(Vector mousePos);

private:
	std::map<std::unique_ptr<Text>, void(*)(const Text*)> _text;
};

