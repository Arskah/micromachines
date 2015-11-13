#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Player.h"
#include "Object.h"
#include "Map.h"

<<<<<<< HEAD

/*
This class keeps track of the map, players and objects, runs the event loop
and calls the Engine. This class also initiates the game.
*/
=======
>>>>>>> 907e73a61a51f63dc57ced1954648f7f709b21f3
class Game
{
public:
	/*
	The constructor for the Game.
	Paremeters:
<<<<<<< HEAD
	- window: a pointer to the application window
	- playerdata: list of player names and their vehicle choices (vehicle type) TODO: replace int with proper vehicleType
	- mapdata: filepath to the map data
	*/
	Game(sf::RenderWindow *window, std::vector<std::pair<std::string, int>> playerdata, std::string mapdata);

	/* run()
	The game loop. Runs the event loop, gathers user input and passes it to the Engine.
	*/
	void run();


private:
	/* initPlayers()
	Initializes the list of players based on the information passed to the constructor.
	This is ran only by the constructor.
	Parameters:
	- playerdata: list of player names and their vehicle choices (vehicle type)
	*/
	void initPlayers(std::vector<std::pair<std::string, int>> playerdata);

	/* initObjects()
	Initializes the list of objects by randomizing some oil spills for example.
	This is ran only by the constructor.
	*/
	void initObjects();

	/* initMap()
	Initializes the map by reading the map data from a file.
	This is ran only by the constructor.
	Parameters:
	- mapdata: filepath to the map data
	*/
	void initMap(std::string mapdata);

	/*
	players: list of players
	objects: list of objects
	map: map (duh)
	window: the application window
	userinput: this structure maps the player (by name) to the input the player gave
			   this list is passed to the engine with every cycle of the loop
	*/
=======
	- w: a pointer to the application window
	- p: list of player names and their vehicle choices (vehicle type)
	- m: data of the map for initializing the map????
	*/
	Game(sf::RenderWindow *w, std::map<std::string, int> p);

private:
>>>>>>> 907e73a61a51f63dc57ced1954648f7f709b21f3
	std::vector<Player> players;
	std::vector<Object> objects;
	Map map;
	sf::RenderWindow* window;
<<<<<<< HEAD
	std::vector<std::pair<std::string, int>> userinput; //TODO: replace int with proper inputType

=======
	// inputlist here
>>>>>>> 907e73a61a51f63dc57ced1954648f7f709b21f3
	// Also possibly load and store all textures here?
};
