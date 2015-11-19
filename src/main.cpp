#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"
#include "ResourceManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Micro Machines");
	window.setFramerateLimit(60);
	std::string name = "Okko";
	Config::ObjectType type = Config::ObjectType::Car;
	std::pair<const std::string, Config::ObjectType> pair(name, type);
	std::vector<std::pair<const std::string, Config::ObjectType>> playerdata;
	playerdata.push_back(pair);
	std::string mapdata = "lol";

	ResourceManager resourcemanager;
	Game game(window, &resourcemanager, playerdata, mapdata);
	game.run();

	/*
	
	PASS THE WINDOW TO THE MENU HERE PLS
	
	*/

	return 0;
}
