#pragma once

#include "SFML/Graphics.hpp"
#include "Map.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <deque>

class Editor
{
public:
	Editor(sf::RenderWindow & window, const std::map<Config::BlockType, sf::Image> * blocktextures);

	void runEditor();

private:
	enum class BoxTypes
	{
		Text,
		Number,
		Alphanumeric
	};

	//Run when creating new map
	void initMap();
	//Open a new window with a small textbox for user textinput
	std::string openTextbox(const std::string &box_name, const BoxTypes box_type = BoxTypes::Alphanumeric);
	//Create a UI element from given list of images and build it into ui_image
	void createUI(const std::vector<const sf::Image *> images, sf::Image * ui_image);
	//Create red selection rectangle for blockUI
	sf::VertexArray createSelected(std::vector<const sf::Image *> * block_images, const sf::Sprite * blocks_ui, const int num);
	
	sf::RenderWindow & window;
	sf::Vector2u size;
	Map map;
	const std::map<Config::BlockType, sf::Image> * blocktextures;
};

/*
#include <SFML/Graphics.hpp>
#include "Editor.h"

int main()
{
sf::RenderWindow window(sf::VideoMode(1280, 720), "Micro Machines");

std::map<Config::BlockType, sf::Image> blocktextures;
Editor editor(&window, &blocktextures);
editor.runEditor();

while(window.isOpen())
{
sf::Event event;
while (window.pollEvent(event))
{
switch (event.type)
{
case sf::Event::Closed:
window.close();
break;
case sf::Event::KeyPressed:
if (event.key.code == sf::Keyboard::Escape)
window.close();
break;
}
}

window.clear();
window.display();
}

return 0;
}

*/