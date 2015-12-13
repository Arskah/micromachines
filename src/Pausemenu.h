#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Config.h"
#include "Button.h"
#include "Config.h"
#include <stdlib.h>
#include <vector>
#include <list>

class PauseMenu
{
public:

	PauseMenu(sf::RenderWindow& window);
	~PauseMenu() {};

	void createButtons();

	bool runMenu(sf::RenderWindow& window, sf::Music &music);
	void draw(sf::RenderWindow& window);

	int width;
	int height;

private:
	int heightDivider = 7;

	sf::Image backgroundImage;
	sf::Font font;

	Button continue_game;
	Button exit_game;
	Button music;

	std::vector<class Button> buttons;

	sf::RenderWindow& window;
};
	