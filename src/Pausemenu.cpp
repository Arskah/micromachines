#include <SFML/Graphics/Rect.hpp>

#include "Pausemenu.h"
#include <stdlib.h>


PauseMenu::PauseMenu(sf::RenderWindow& window) : window(window)
{

	width = window.getSize().x;
	height = window.getSize().y;

}
void PauseMenu::loadContent()
{

}
void PauseMenu::createButtons()
{

}
bool PauseMenu::runMenu(sf::RenderWindow& window)
{
	return false;
}
void PauseMenu::draw(sf::RenderWindow& window)
{

}