#pragma once
#include <SFML/Graphics.hpp>

#include "AI.h"
#include "Block.h"
#include "Map.h"
#include "Object.h"
#include "Player.h"
#include "Projectile.h"
#include "Vehicle.h"

namespace Engine
{
	/* Main function of the namespace. Handles calling of other namespace functions. Called on every frame by the Game class.
	Parameters:
	- window: a pointer to the application window
	- players: list of players
	- vehicles: list of vehicles
	- projectiles: list of projectiles
	- map: game map.
	- userinput: this structure maps the player (by name) to the input the player gave
	this list is passed to the engine with every cycle of the loop
	*/
	void update(sf::RenderWindow* window, std::vector<Vehicle> vehicles, std::vector<Projectile> projectiles, Map map, std::vector<std::pair<Player*, Config::InputType>> userinput);

	/* Input handling
	Parameters:
	- userinput: this structure maps the player to the input the player gave.
	This vector structure is passed to the engine with every cycle of the loop
	*/
	void handleInput(std::vector<std::pair<Player*, Config::InputType>>);

	/* Function that handles moving of objects each frame. Executed after input handling
	Parameters:
	- vehicle: reference to a vehicle object being moved on loop
	*/
	void moveVehicle(Vehicle&);

	/*
	void moveProjectile(Projectile);
	*/


	/* Function draws all vehicles
	Parameters:
	- window: a pointer to the application window
	- vehicles: list of vehicles
	*/
	void draw_vehicles(sf::RenderWindow* window, std::vector<Vehicle> vehicles);

	//void draw_projectiles(sf::renderWindow * window, std::vector<Projectile> projectiles);

	/* Main function for drawing a frame.
	Parameters:
	- window: a pointer to the application window
	- vehicles: list of vehicles
	- projectiles: list of projectiles
	- map: game map.
	*/
	void draw(sf::RenderWindow* window, std::vector<Vehicle> vehicles, std::vector<Projectile> projectiles, Map map);
}