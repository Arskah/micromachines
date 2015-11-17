#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Micro Machines");

	std::string name = "Okko";
	Config::ObjectType type = Config::ObjectType::Car;
	std::pair<const std::string, Config::ObjectType> pair(name, type);
	std::vector<std::pair<const std::string, Config::ObjectType>> playerdata;
	playerdata.push_back(pair);
	std::string mapdata = "lol";

	Game game(&window, playerdata, mapdata);
	game.run();

	/*
	
	PASS THE WINDOW TO THE MENU HERE PLS
	
	*/

	return 0;
}
