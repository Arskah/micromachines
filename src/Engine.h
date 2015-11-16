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
	void update(sf::renderWindow*, std::vector<Player>, std::vector<Object>, std::vector<Projectile>, Map, std::vector<std::pair<std::string, int>>);



	/* Input handling and AI calling
	Parameters:
	- player: player and AI
	- userinput: this structure maps the player (by name) to the input the player gave
	this list is passed to the engine with every cycle of the loop
	*/
	void playerInput(std::vector<Player> players, std::vector<std::pair<std::string, int>>);

	/* Function that calculates new postitions for every moving object every frame.
	Parameters:
	- object:
	*/
	void moveVehicle(Object);

	//void calculatePosProjectile();

	/* Function draws all vehicles
	Parameters:
	- window: a pointer to the application window
	- vehicles: list of vehicles
	*/
	void draw_vehicles(sf::renderWindow*, std::vector<Object>);

	//void draw_projectiles(sf::renderWindow * window, std::vector<Projectile> projectiles);

	/* Main function for drawing a frame. 
	Parameters:
	- window: a pointer to the application window
	- vehicles: list of vehicles
	- projectiles: list of projectiles
	- map: game map.
	*/
	void draw(sf::renderWindow*, std::vector<Object>, std::vector<Projectile>, Map);