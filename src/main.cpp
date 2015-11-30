#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"
#include "ResourceManager.h"
#include "Editor.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Micro Machines");
	//window.setFramerateLimit(60);

	std::string name = "Playah";
	std::string name2 = "Kalle";
	Config::ObjectType type = Config::ObjectType::Car;
	std::pair<const std::string, Config::ObjectType> pair(name, type);
	std::pair<const std::string, Config::ObjectType> pair2(name2, type);
	std::vector<std::pair<const std::string, Config::ObjectType>> playerdata;
	playerdata.push_back(pair);
	playerdata.push_back(pair2);
	std::string mapdata = "src/resources/mapsavetest.png";

	ResourceManager resourcemanager;

	/*
	//EXAMPLE HOW EASY IT IS TO START THE EDITOR
	//ESC escapes from editor and doesn't close window
	Editor editor(window, *resourcemanager.getBlockTextures());
	editor.runEditor();
	*/
	
	/*
	//EXAMPLE ON HOW EASY IT IS TO USE A MAP
	//Loading takes a while still, please just wait
	//No need for parameters to ctor
	Map mapperino;
	//Need only filepath and reference to blocktextures from resourcemanager
	mapperino.loadFromImage("src/resources/mapsavetest.png", (*resourcemanager.getBlockTextures()));

	while (window.isOpen())
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
		//THIS IS HOW YOU GET THE DRAWABLE SPRITE
		//getDrawable returns sf::Sprite *, that you need to just dereference
		window.draw((*mapperino.getDrawable()));
		window.display();
	}	
	*/

	Game game(window, &resourcemanager, playerdata, mapdata);
	game.run();

	/*
	
	PASS THE WINDOW TO THE MENU HERE PLS
	
	*/

	return 0;
}
