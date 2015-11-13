#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Player.h"
#include "Object.h"
#include "Map.h"
#include "Projectile.h"
#include "Vehicle.h"
#include "Config.h"


/*
This class keeps track of the map, players and objects, runs the event loop
and calls the Engine. This class also initiates the game.
*/
class Game
{
public:
	/*
	The constructor for the Game.
	Paremeters:
	- window: a pointer to the application window
	- playerdata: list of player names and their vehicle choices (vehicle type)
	- mapdata: filepath to the map data
	*/
	Game(sf::RenderWindow * window, std::vector<std::pair<const std::string, Config::ObjectType>> playerdata, std::string mapdata);

	/* run()
	The game loop. Runs the event loop, gathers user input and passes it to the Engine.
	*/
	void run();


private:
	/* initTextures()
	Loads all the textures to a map containing object types and texture files.
	This is ran only by the constructor.
	*/
	void initTextures();

	/* initVehicle()
	Creates a Vehicle from a file.
	Pushes the created Vehicle to the objects list.
	*/
	Vehicle * initVehicle(Config::ObjectType);

	/* initPlayers()
	Initializes the list of players based on the information passed to the constructor.
	This also creates the vehicles and adds them to the objects list.
	This is ran only by the constructor.
	Parameters:
	- playerdata: list of player names and their vehicle choices (vehicle type)
	*/
	void initPlayers(std::vector<std::pair<const std::string, Config::ObjectType>> playerdata);

	/* initProjectiles()
	Initializes the list of projectiles by randomizing some oil spills for example.
	This is ran only by the constructor.
	*/
	void initProjectiles();

	/* initMap()
	Initializes the map by reading the map data from a file.
	This is ran only by the constructor.
	Parameters:
	- mapdata: filepath to the map data
	*/
	void initMap(std::string mapdata);

	/*
	players: list of players
	vehicles: list of vehicles
	projectiles: list of projectiles
	map: map (duh)
	window: the application window
	userinput: this structure maps the player (by name) to the input the player gave
			   this list is passed to the engine with every cycle of the loop
	textures: map containing ObjectTypes and textures.
	*/
	std::vector<Player> players;
	std::vector<Vehicle> vehicles;
	std::vector<Projectile> projectiles;
	Map map;
	sf::RenderWindow * window;
	std::vector<std::pair<std::string, Config::ObjectType>> userinput;
	std::map<Config::ObjectType, sf::Texture> textures;
};