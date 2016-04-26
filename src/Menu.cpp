#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::renderMenu(SDL_Renderer * ren)
{
	for (auto const& txt : _text)
		txt.first->render(ren);
}

void Menu::addText(Text* txtToAdd, void(*callbackFunction)(const Text*))
{
	_text[std::unique_ptr<Text>(txtToAdd)] = callbackFunction;
}

// Check if click is inside box of text. If so run a function
void Menu::clickMenuItem(Vector mousePos)
{
	for (auto const& txt : _text)
	{
		Vector textPosition = txt.first->getPosition();
		Size textSize = txt.first->getSize() / 2;
		if (mousePos.x > textPosition.x - textSize.width &&
			mousePos.x < textPosition.x + textSize.width &&
			mousePos.y > textPosition.y - textSize.height &&
			mousePos.y < textPosition.y + textSize.height)
		{
			txt.second(txt.first.get()); // make a call to the callback function
			return;
		}
	}
}
