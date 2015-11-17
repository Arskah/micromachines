#pragma once
#include "Engine.h"

void Engine::update(sf::RenderWindow& window, std::vector<Vehicle>& vehicles, std::vector<Projectile>& projectiles, Map& map, std::vector<std::pair<Player*, Config::InputType>> userinput)
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

/* Handles userinput before moving the vehicle*/
void Engine::handleInput(std::vector<std::pair<Player*, Config::InputType>> userinput)
{
	for (auto it : userinput)
	{
		Player* player = it.first;
		Config::InputType input = it.second;
		switch (input)
		{
		case Config::InputType::TurnLeft:
			player->getVehicle()->turn(true);
			break;
		case Config::InputType::TurnRight:
			player->getVehicle()->turn(false);
			break;
		case Config::InputType::Accelerate:
			player->getVehicle()->accelerate();
			break;
		case Config::InputType::Brake:
			player->getVehicle()->brake();
			break;
		case Config::InputType::Shoot:
			player->getVehicle()->shoot();
			break;
		default:
			break;
		}
	}
}
//TODO
/* Finds the block a vehicle is currently on and gets the block's friction multiplier
float Engine::getFriction(Vehicle vehicle)
{
	vehicle.getLocation();
}
*/

void Engine::moveVehicle(Vehicle& vehicle)
{
	float speed = vehicle.getSpeed();
	if (speed != 0.0f)
	{
		float rotation = vehicle.getRotation();
		sf::Vector2f movementVec; //normal vector based on current direction
		const sf::Vector2f forwardVec(0.f, 1.f); //normal vec pointing forward

		sf::Transform t;		// create dummy object for vector handling
		t.rotate(rotation);
		movementVec = t.transformPoint(forwardVec);
		//TODO friction etc.
		vehicle.move(movementVec * speed);
	}
}
/*
void Engine::moveProjectile(Vehicle& projectile)
{
	
}
*/

void Engine::draw_vehicles(sf::RenderWindow& window, std::vector<Vehicle>& vehicles)
{
	for (auto it : vehicles)
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
void Engine::draw(sf::RenderWindow& window, std::vector<Vehicle>& vehicles, std::vector<Projectile>& projectiles, Map& map)
{
	(void) projectiles;
	window.clear(sf::Color::Black);				// Clear previous frame
	//window->draw(map.getDrawable());							//TODO: Map			'BOTTOM' drawing
	//Engine::draw_projectiless(projectiles);		// Projectiles don't overwrite on vehicles
	Engine::draw_vehicles(window, vehicles);			// On top of everything
	window.display();							// Update drawings
}