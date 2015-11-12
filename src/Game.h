#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Player.h"
#include "Object.h"
#include "Map.h"

class Game
{
public:
	/*
	The constructor for the Game.
	Paremeters:
	- w: a pointer to the application window
	- p: list of player names and their vehicle choices (vehicle type)
	- m: data of the map for initializing the map????
	*/
	Game(sf::RenderWindow *w, std::map<std::string, int> p);

private:
	std::vector<Player> players;
	std::vector<Object> objects;
	Map map;
	sf::RenderWindow* window;
	// inputlist here
	// Also possibly load and store all textures here?
};
