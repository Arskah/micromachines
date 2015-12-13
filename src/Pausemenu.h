#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Config.h"
//#include "Button.h"
#include "Menu.h"
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

	button continue_game;
	button exit_game;
	button music;

	std::vector<struct button> buttons;

	sf::RenderWindow& window;

	sf::Sprite spri_exit;
	sf::Sprite spri_continue;
	sf::Sprite spri_music;

	//Load music texture
	sf::Texture tex_music12;
	sf::Texture tex_music22;
	sf::Texture tex_music32;
	sf::Texture tex_music42;
	sf::Texture tex_music52;
	sf::Texture tex_music62;
	sf::Sprite spri_music2;
};
	