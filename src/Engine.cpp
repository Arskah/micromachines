#pragma once
#include "Engine.h"

void Engine::update(sf::RenderWindow& window, ResourceManager * resourcemanager, std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles, Map& map, std::vector<std::pair<Player*, Config::InputType>> userinput, float dt)
{
	/* AI and player movement handling */
	Engine::handleInput(userinput, dt, projectiles, resourcemanager);

	/* Move vehicles. Players and AI move depends on input handling */
	for (auto it = vehicles->begin(); it != vehicles->end(); it++)
	{
		it->slow(Engine::getFriction(&(*it), map), dt);
		it->setWeapontimer(dt);
		Engine::moveVehicle(&(*it));
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
void Engine::handleInput(std::vector<std::pair<Player*, Config::InputType>> userinput, float dt, std::vector<Projectile> * projectiles, ResourceManager * resourcemanager)
{
	for (auto it : userinput)
	{
		Player* player = it.first;
		Config::InputType input = it.second;
		switch (input)
		{
		case Config::InputType::TurnLeft:
			player->getVehicle()->turn(true, dt);
			break;
		case Config::InputType::TurnRight:
			player->getVehicle()->turn(false, dt);
			break;
		case Config::InputType::Accelerate:
			player->getVehicle()->accelerate(dt);
			break;
		case Config::InputType::Brake:
			player->getVehicle()->brake(dt);
			break;
		case Config::InputType::Shoot:
			if (player->getVehicle()->getWeapontimer() >= player->getVehicle()->getWeapon()->getCooldown())
			{
				projectiles->emplace_back(player->getVehicle()->shoot());
				resourcemanager->playSound("shoot");
			}
			break;
		default:
			break;
		}
	}
}
//TODO
/* Finds the block a vehicle is currently on and gets the block's friction multiplier
*/
float Engine::getFriction(Vehicle * vehicle, Map& map)
{
	// change the getPosition() to getLocation() once it's properly implemented.
	sf::Vector2f location = vehicle->getPosition();
	return map.getBlock(location.x, location.y).getFriction();
}


void Engine::moveVehicle(Vehicle * vehicle)
{
	float speed = vehicle->getSpeed();
	if (speed > 0.0f)
	{
		float rotation = vehicle->getRotation();
		sf::Vector2f movementVec; //normal vector based on current direction
		const sf::Vector2f forwardVec(0.f, 1.f); //normal vec pointing forward

		sf::Transform t;		// create dummy object for vector handling
		t.rotate(rotation);
		movementVec = t.transformPoint(forwardVec);
		vehicle->move(movementVec * speed);
	}
}
/*
void Engine::moveProjectile(Vehicle& projectile)
{
	
}
*/

void Engine::draw_vehicles(sf::RenderWindow& window, std::vector<Vehicle> * vehicles)
{
	for (auto it = vehicles->begin(); it != vehicles->end(); it++)
	{
		window.draw(*it);
	}
}


void Engine::draw_projectiles(sf::RenderWindow& window, std::vector<Projectile> * projectiles)
{
	for (auto it = projectiles->begin(); it != projectiles->end(); it++)
	{
		window.draw(*it);
	}
}

/* Draw main function. NOTE: excpects that draw function for any object is defined in the respected class. 
TODO: view individual for players and moving view: not all should be drawn on every frame
*/
void Engine::draw(sf::RenderWindow& window, std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles, Map& map)
{
	(void) projectiles;
	window.clear(sf::Color::Black);				// Clear previous frame
	/*
	window.draw(*map.getDrawable());							//TODO: Map			'BOTTOM' drawing
	Engine::draw_projectiles(window, projectiles);		// Projectiles don't overwrite on vehicles
	Engine::draw_vehicles(window, vehicles);   // On top of everything
	*/

	// This is a ghetto version of the centered view. TODO: implement check for AI vs Human player.
	for (size_t i = 0; i < vehicles->size(); i++)
	{
		sf::View view;
		view.setCenter(sf::Vector2f(vehicles->at(i).getPosition().x, vehicles->at(i).getPosition().y));
		view.setSize(640.f, 720.f);
		view.setRotation(vehicles->at(i).getRotation() - 180.f);
		view.setViewport(sf::FloatRect(0.5f * i, 0, 0.5f, 1)); // player 1 is on the left, 2 is on the right.
		window.setView(view);
		window.draw(*map.getDrawable());							//TODO: Map			'BOTTOM' drawing
		Engine::draw_projectiles(window, projectiles);		// Projectiles don't overwrite on vehicles
		Engine::draw_vehicles(window, vehicles);   // On top of everything
	}
	
	window.display();							// Update drawings
}