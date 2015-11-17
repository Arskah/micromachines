#pragma once
#include "Engine.h"

void Engine::update(sf::RenderWindow* window, std::vector<Object> vehicles, std::vector<Projectile> projectiles, Map map, std::vector<std::pair<Player*, Config::InputType>> userinput)
{
	/* AI and player movement handling */
	Engine::handleInput(userinput);

	/* Move vehicles. Players and AI move depends on input handling */
	for (auto it : vehicles)
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
void Engine::handleInput(std::vector<std::pair<Player*, Config::InputType>> userinput)
{
	for (auto it : userinput)
	{
		Player* player = it.first();
		Config::InputType input = it.second();
		switch (input)
		{
		case TurnLeft:
			player->getVehicle()->turn(true);
			break;
		case TurnRight:
			player->getVehicle()->turn(false);
			break;
		case Accelerate:
			player->getVehicle()->accelerate();
			break;
		case Brake:
			player->getVehicle()->brake();
			break;
		case Shoot:
			player->getVehicle()->shoot();
			break;
		}
	}
}
//TODO
/* Finds the block a vehicle is currently on and gets the block's friction multiplier
float Engine::getFriction(Object vehicle)
{
	vehicle.getLocation();
}
*/

void Engine::moveVehicle(Object& vehicle)
{
	float speed = vehicle.getSpeed();
	if (speed != 0)
	{
		float rotation = vehicle.getRotation();
		sf::Vector2f movementVec; //normal vector based on current direction
		const sf::Vector2f forwardVec(0.f, 1.f); //normal vec pointing forward

		sf::Transform t;		// create dummy object for vector handling
		t.rotate(rotation);
		movementVec = t.transformPoint(forwardVec);
		//TODO friction etc.
		vehicle.move(speed * movementVec);
	}
}
/*
void Engine::moveProjectile(Object& projectile)
{
	
}
*/

void Engine::draw_vehicles(sf::RenderWindow* window, std::vector<Object> vehicles)
{
	for (auto it : vehicles)
	{
		window->draw(it);
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
void Engine::draw(sf::RenderWindow* window, std::vector<Object> vehicles, std::vector<Projectile> projectiles, Map map)
{
	(void) projectiles;
	window->clear(sf::Color::Black);				// Clear previous frame
	//window->draw(map.getDrawable());							//TODO: Map			'BOTTOM' drawing
	//Engine::draw_projectiless(projectiles);		// Projectiles don't overwrite on vehicles
	Engine::draw_vehicles(window, vehicles);			// On top of everything
	window->display();							// Update drawings
}