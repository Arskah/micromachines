#include "engine.hpp"
#include "Engine.h"

#define COOLDOWN 1

/* Main function in the Engine namespace. Calls all functions handling position calculation and handles drawing new frame
Parameters:
- window: The window game is drawn on
- players: vector consisting of every player and AI 
- objects: vector of all objects on map
- map: Game map
- userinput: pair consisting of userinput given by player (2nd true if input given)
*/

void Engine::update(sf::renderWindow* window, std::vector<Player> players, std::vector<Object> objects, Map map, std::pair<inputtype, bool> userinput)
{
	for (auto it = player.begin(); it != player.end(); it++)
	{
		playerInput(it, userinput);
	}
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		calculatePosObject(it);
	}
	draw(window, objects, map);
}

/* Handles userinput before moving the object*/
void Engine::playerInput(Player player, std::pair<inputtype, bool> userinput))
{
	if (userinput.second())
	{
		switch (userinput.first())
		{
		case left:
			player.getVehicle().turn(true);
		case right:
			player.getVehicle().turn(false);
		case accelerate:
			player.getVehicle().accelerate();
		case brake:
			player.getVehicle().brake();
		case default:
			// Open menu? What other inputs we have?
		}
	}
	//calculatePosObject(player);		// If player vehicles are in objects, own calcualtion is not needed
}

void Engine::calculatePosObject(Object object)
{
	float speed = object.getSpeed();
	if (speed > 0)
	{
		sf::vector2f velocity_vector(speed, direction);
		object.move(velocity_vector);
	}
}
/*
void Engine::calculatePosProjectile(Object projectile)
{
	while (projectile.getLocation())
}
*/
void Engine::draw_map(sf::renderWindow* window, Map map)
{
	for (unsigned int x = 0; x < map.size().first(); x++)
		for (unsigned int y = 0; y < map.size().second(); y++)
		{

		}
}

void Engine::draw_objects(sf::renderWindow* window)
{

}

void Engine::draw(sf::renderWindow* window, std::vector<Object> objects, Map map)
{
	window.clear(sf::Color::Black);			// Clear previous frame
	draw_map(window, map);
	draw_objects(window, objects);
	window.display();						// Update drawings
}