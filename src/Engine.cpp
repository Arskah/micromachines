#pragma once
#include "Engine.h"

void Engine::update(sf::RenderWindow& window, ResourceManager * resourcemanager, std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles, Map& map, 
	std::vector<std::pair<Player*, Config::InputType>> userinput, float dt, sf::Text gametime)
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

	Engine::checkCollisions(vehicles, projectiles);

	//TODO: projectiles
	/*
	for (auto it = projectiles.begin(); it != projectiles.end(); it++)
	{
		Engine::calculatePosProjectile(it);
	}
	*/

	/* Call function to handle all drawing */
	Engine::draw(window, vehicles, projectiles, map, gametime);
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

void Engine::checkCollisions(std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles)
{
	//Checks Vehicle - Vehicle collisions and moves them apart
	//Loop all vehicles through
	for (auto vehicle_1 = vehicles->begin(); vehicle_1 != vehicles->end(); vehicle_1++)
	{
		for (auto vehicle_2 = vehicles->begin(); vehicle_2 != vehicles->end(); vehicle_2++)
		{
			//Don't want to check collisions on self
			if (vehicle_1 != vehicle_2)
			{
				//While we are still in collision state
				while (Hitbox::checkCollision(&(*vehicle_1), &(*vehicle_2)))
				{

					//THIS WHOLE PART CAN BE CHANGED
					//THIS WAS JUST EXPERIMENTAL

					const float magic_number = 0.5f;
					//Move vehicles apart from each other on the xy-grid by amount magic_number, 0.5f selected for smooth movement
					//X-coordinate
					if (std::abs(vehicle_1->getPosition().x - vehicle_2->getPosition().x) > vehicle_1->getVertices()[1].position.x)
					{
						if (vehicle_1->getPosition().x < vehicle_2->getPosition().x)
						{
							vehicle_1->move(sf::Vector2f(-magic_number, 0.f));
							vehicle_2->move(sf::Vector2f(magic_number, 0.f));
						}
						else
						{
							vehicle_1->move(sf::Vector2f(magic_number, 0.f));
							vehicle_2->move(sf::Vector2f(-magic_number, 0.f));
						}
					}

					//Y-coordinate
					//if (std::abs(vehicle_1->getPosition().y - vehicle_2->getPosition().y) > vehicle_1->getVertices()[2].position.y)
					{
						if (vehicle_1->getPosition().y < vehicle_2->getPosition().y)
						{
							vehicle_1->move(sf::Vector2f(0.f, -magic_number));
							vehicle_2->move(sf::Vector2f(0.f, magic_number));
						}
						else
						{
							vehicle_1->move(sf::Vector2f(0.f, magic_number));
							vehicle_2->move(sf::Vector2f(0.f, -magic_number));
						}
					}
				}
			}
		}
	}

	//Checks Vehicle - Projectile collisions
	for (auto vehicle = vehicles->begin(); vehicle != vehicles->end(); vehicle++)
	{
		for (auto projectile = projectiles->begin(); projectile != projectiles->end(); projectile++)
		{
			//Need something to happen per ObjectType of projectile
		}
	}

}

void Engine::draw_vehicles(sf::RenderWindow& window, std::vector<Vehicle> * vehicles)
{
	for (auto it = vehicles->begin(); it != vehicles->end(); it++)
	{
		window.draw(*it);

		//For debug purposes
		//window.draw(Hitbox::createHitboxRect(&(*it)));
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
void Engine::draw(sf::RenderWindow& window, std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles, Map& map, sf::Text gametime)
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
		view.setSize(window.getSize().x /2, window.getSize().y);
		view.setRotation(vehicles->at(i).getRotation() - 180.f);
		view.setViewport(sf::FloatRect(0.5f * i, 0, 0.5f, 1)); // player 1 is on the left, 2 is on the right.
		window.setView(view);
		window.draw(*map.getDrawable());
		Engine::draw_projectiles(window, projectiles);		// Projectiles don't overwrite on vehicles
		Engine::draw_vehicles(window, vehicles);   // On top of everything
		
		// Drawing the gametimer to the top-left corner TODO: add standings etc.
		if (i == 0)
		{
			gametime.setRotation(vehicles->at(0).getRotation() - 180.f);
			sf::Vector2i pixelpos = sf::Vector2i(0,0);
			sf::Vector2f worldpos = window.mapPixelToCoords(pixelpos);
			gametime.setPosition(worldpos);
			window.draw(gametime);
		}
	}


	window.display();							// Update drawings
}