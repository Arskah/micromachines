#pragma once
#include "Engine.h"

void Engine::update(sf::renderWindow* window, std::vector<Player> players, std::vector<Object> vehicles, std::vector<Projectile> projectiles, Map map, std::vector<std::pair<std::string, int>> userinput)
{
	/* AI and player movement handling */
	Engine::playerInput(players, userinput);

	/* Move objects. Players and AI move depends on input handling */
	for (auto it = vehicles.begin(); it != vehicles.end(); it++)
	{
		Engine::moveVehicle(it);
	}
	//TODO: projectiles
	/*
	for (auto it = projectiles.begin(); it != projectiles.end(); it++)
	{
		Engine::calculatePosProjectile(it);
	}
	*/
	/* Call function to handle all drawing */
	Engine::draw(window, vehicles, projectiles, map);
}

/* Handles userinput before moving the object*/
void Engine::playerInput(std::vector<Player> players, std::vector<std::pair<std::string, int>> userinput)
{
	for (auto it = players.begin(); it != players.end(); it++)
	{
		if ()
		{
			switch (input_it.second())
			{
			case left:
				player.getVehicle()->turn(true);
			case right:
				player.getVehicle()->turn(false);
			case accelerate:
				player.getVehicle()->accelerate();
			case brake:
				player.getVehicle()->brake();
			case default:
				// Open menu? What other inputs we have?
			}
		}
	}
}

void Engine::moveVehicle(Object vehicle)
{
	float speed = vehicle.getSpeed();
	float rotation = 0;
	if (speed != 0)
	{
		sf::Vector2f movementVec; //normal vector based on current direction
		const sf::Vector2f forwardVec(0.f, 1.f); //normal vec pointing forward

		sf::Transform t;		// create 
		t.rotate(vehicle.getRotation);
		movementVec = t.transformPoint(forwardVec);

		float speed_multiplier = speed;		//TODO friction etc.
		vehicle.move(speed_multiplier * movementVec);
	}
	
}
/*
void Engine::calculatePosProjectile(Object projectile)
{
	while (projectile.getLocation())
}
*/

void Engine::draw_vehicles(sf::renderWindow* window, std::vector<Object> vehicles)
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		window.draw(it);
	}
}

/*
void Engine::draw_projectiles(sf::renderWindow* window, std::vector<Projectile> projectiles)
{
	for (auto it = projectiles.begin(); it != projectiles.end(); it++)
	{
		window.draw(it);
	}
}
*/
/* Draw main function. NOTE: excpects that draw function for any object is defined in the respected class. 
TODO: view individual for players and moving view: not all should be drawn on every frame
*/
void Engine::draw(sf::renderWindow* window, std::vector<Object> vehicles, std::vector<Projectile> projectiles, Map map)
{
	window.clear(sf::Color::Black);				// Clear previous frame
	//window.draw(map);							//TODO: Map			'BOTTOM' drawing
	//Engine::draw_projectiless(projectiles);		// Projectiles don't overwrite on vehicles
	Engine::draw_vehicles(vehicles);			// On top of everything
	window.display();							// Update drawings
}
