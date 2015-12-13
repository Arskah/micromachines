#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"
#include "ResourceManager.h"
#include "Editor.h"
#include "Game.h"
#include "Menu.h"
#include <tuple>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Micro Machines");
	//window.setFramerateLimit(60);
	
	bool menudata;
	bool loading;
	//std::string name = "Playah";
	//std::string name2 = "Kalle";
	//std::pair<const std::string, Config::ObjectType> pair(name, Config::ObjectType::Car1);
	//std::pair<const std::string, Config::ObjectType> pair2(name2, Config::ObjectType::Car2);
	std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> playerdata;			// ((normal playerdata) isHumanPlayer?)
	//playerdata.push_back(pair);
	//playerdata.push_back(pair2);
	std::string mapdata; // = "src/resources/mapsavetest.png";

	ResourceManager resourcemanager;

		sf::Music music;
		music.setLoop(true);
		music.setVolume(30);
		if (music.openFromFile("src/resources/sounds/themesong.wav"))
				music.play();

	

	/*
	//EXAMPLE HOW EASY IT IS TO START THE EDITOR
	//ESC escapes from editor and doesn't close window
	Editor editor(window, *resourcemanager.getBlockTextures());
	editor.runEditor();
	*/
        
        Menu menu(window, &resourcemanager);
        menudata = menu.runMenu(window, playerdata, mapdata, music);
		if (menudata == false)
		{
			exit(0);
		}
		else
			loading = true;
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

	//Integers for loading screen
	sf::Sprite sprite;
	sf::Texture tex_1;
	tex_1.loadFromFile("src/resources/menu/loading3.png");
	sprite.setPosition(((float) window.getSize().x / 2 - 50), (float) window.getSize().y / 2);
	//draw loading screen
	sprite.setTexture(tex_1, true);
	window.draw(sprite);
	window.display();
	
	
        

	Game game(window, &resourcemanager, playerdata, mapdata);
	game.run(loading);

	/*
	
	PASS THE WINDOW TO THE MENU HERE PLS
	
	*/

	return 0;
}
