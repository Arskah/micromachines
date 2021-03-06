//#pragma once
#include "Engine.h"

void Engine::update(sf::RenderWindow& window, ResourceManager * resourcemanager, std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles, Map& map, 
	std::vector<std::pair<Player*, Config::InputType>> userinput, float dt, sf::Text gametime, sf::Text lapCount, std::vector<Player*>* humanPlayers)
{
	for (auto it : userinput)
	{
		Player* player = it.first;

		/* Call AI calculations. */
		
		if (!(player->getHuman()))
		{
			// AI bypassed
			std::pair<Config::InputType, Config::InputType> AI_input_pair(Config::InputType::None, Config::InputType::None);
			//AI_input_pair = AI::calculateAIinput(player, vehicles, projectiles, map);
			Engine::handleInput(player, AI_input_pair.first, dt, projectiles, resourcemanager);
			it.second = AI_input_pair.second;
		}
		
		/* AI and player movement handling */
		Engine::handleInput(player, it.second, dt, projectiles, resourcemanager);

		/* Removing all explosions */
		for (auto projectile = projectiles->begin(); projectile != projectiles->end();)
		{
			if (projectile->getType() == Config::ObjectType::Explosion)
			{
				projectile = projectiles->erase(projectile);
			}
			else
				projectile++;
		}
	}

	/* Move vehicles. Players and AI move depends on input handling */
	for (auto it = vehicles->begin(); it != vehicles->end(); it++)
	{
		it->slow(Engine::getFriction(&(*it), map), dt);
		it->setWeapontimer(dt);
		if (it->getPenalty() == true)
			it->setPenaltytimer(dt);
		if (it->getPenaltytimer() >= 1.0f)
			it->resetPenaltytimer();
		Engine::moveVehicle(&(*it));
	}

	Engine::checkCollisions(vehicles, projectiles, map, resourcemanager, dt);

	//TODO: projectiles
	/*
	for (auto it = projectiles.begin(); it != projectiles.end(); it++)
	{
		Engine::calculatePosProjectile(it);
	}
	*/
	Engine::updateLap(vehicles, map);
	/* Call function to handle all drawing */
	Engine::draw(window, vehicles, projectiles, map, gametime, lapCount, humanPlayers);

}

/* Handles userinput before moving the vehicle*/
void Engine::handleInput(Player* player, Config::InputType input, float dt, std::vector<Projectile> * projectiles, ResourceManager * resourcemanager)
{
	/* This switch handles refreshing of movement for vehicle class attributes. Draw handles drawing on screen based on new position of vehicles */
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
	case Config::InputType::None:
		break;
	default:
		break;
	}
}
//TODO
/* Finds the block a vehicle is currently on and gets the block's friction multiplier
*/
float Engine::getFriction(Vehicle * vehicle, Map& map)
{
	sf::Vector2f location = vehicle->getPosition();
	return map.getBlock(int(location.x), int(location.y)).getFriction();
}


void Engine::moveVehicle(Vehicle * vehicle)
{
	float speed = vehicle->getSpeed();
	if (speed != 0.f)
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

void Engine::checkCollisions(std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles, Map& map, ResourceManager * resourcemanager, float dt)
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
	if (projectiles->size() > 0)
	{
		// Checking all vehicle - projectile combinations.
		for (auto vehicle = vehicles->begin(); vehicle != vehicles->end();)
		{
			for (auto projectile = projectiles->begin(); projectile != projectiles->end();)
			{
				if (Hitbox::checkCollision(&(*vehicle), &(*projectile)))
				{
					// In case of a Mine, the mine needs to be deleted.
					if (projectile->getType() == Config::ObjectType::Mine)
					{
						// This prevents division by zero error if a mine is spawned on top of a standing vehicle.
						if (vehicle->getSpeed() == 0.f)
							break;

						// The mine will launch the vehicle backwards with a slight random variation in the angle.
						srand((unsigned int) time(NULL));
						vehicle->rotate((float) (rand() % 60 - 30));
						vehicle->accelerate(-(vehicle->getSpeed() / std::abs(vehicle->getSpeed()))*5.f);
						resourcemanager->playSound("mine");

						// Creating the explosion object to be displayed briefly.
						Projectile explosion(&(resourcemanager->getObjectTextures()->find(Config::ObjectType::Explosion)->second), 0.f, Config::ObjectType::Explosion, 0.f);
						explosion.setPosition(projectile->getPosition());
						explosion.setRotation(vehicle->getRotation());
						explosion.setScale(2.0, 2.0);

						// Removing the mine from projectiles vector and adding the explosion.
						// The explosion is removed after it has been drawn.
						projectile = projectiles->erase(projectile);
						projectiles->shrink_to_fit();
						projectiles->push_back(explosion);
						break;
					}
					if (projectile->getType() == Config::ObjectType::Oilspill)
					{
						vehicle->setPenalty(true); // This penalty setting will prevent all controll of the car for a second.
						++projectile;
						break;
					}
				}
				else
					++projectile;
			}
			++vehicle;
		}
	}


	//Checks Vehicle - Obstacle (rockwall) collisions
	for (auto vehicle = vehicles->begin(); vehicle != vehicles->end(); vehicle++)
	{
		sf::VertexArray hitbox = Hitbox::createHitboxRect(&(*vehicle));

		// Going through the corner points of the hitbox.
		for (size_t i = 0; i < hitbox.getVertexCount(); i++)
		{	
			sf::Vector2f position = hitbox[i].position;
			if (map.getBlock(int(position.x), int(position.y)).getType() == Config::BlockType::RockWall)
			{
				sf::Vector2f heading(0.f, 1.f);
				sf::Transform t;
				t.rotate(vehicle->getRotation() - 180);
				sf::Vector2f movement = t.transformPoint(heading); // This vector now points opposite to the car's heading.

				// Playing the collision sound (the magic number stops the "machine gun" sound when pressed against a wall).
				if (std::abs(vehicle->getSpeed()) >= 1.f)
					resourcemanager->playSound("collision");

				if (vehicle->getSpeed() == 0.f)
				{
					break;
				}

				// Bumping the vehicle away from the rockwall.
				vehicle->move(movement * vehicle->getSpeed()/std::abs(vehicle->getSpeed()) * 30.f);
				vehicle->setSpeed(vehicle->getSpeed() * 0.3f);
			}
		}
	}

	//Checks if Vehicle out of bounds
	for (auto vehicle = vehicles->begin(); vehicle != vehicles->end(); vehicle++)
	{
		sf::Vector2u map_size = map.getDrawable()->getTexture()->getSize();

		// x < 0
		if (vehicle->getPosition().x < 0)
		{
			vehicle->setPosition(0, vehicle->getPosition().y);
		}

		// y < 0
		if (vehicle->getPosition().y < 0)
		{
			vehicle->setPosition(vehicle->getPosition().x, 0);
		}

		// x > bounds
		if (vehicle->getPosition().x > map_size.x - 1)
		{
			vehicle->setPosition(float(map_size.x - 1), vehicle->getPosition().y);
		}

		// y > bounds
		if (vehicle->getPosition().y > map_size.y - 1)
		{
			vehicle->setPosition(vehicle->getPosition().x, float(map_size.y - 1));
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
void Engine::draw(sf::RenderWindow& window, std::vector<Vehicle> * vehicles, std::vector<Projectile> * projectiles, Map& map, sf::Text gametime, sf::Text lapCount, std::vector<Player*>* humanPlayers)
{
	(void) projectiles;
	window.clear(sf::Color::Black);				// Clear previous frame


	// This is a ghetto version of the centered view.
	for (unsigned int i = 0; i < humanPlayers->size(); i++)
	{
		sf::View view;
		view.setCenter(sf::Vector2f(humanPlayers->at(i)->getVehicle()->getPosition().x, humanPlayers->at(i)->getVehicle()->getPosition().y));
		if (humanPlayers->size() == 1)			// I think modifiable for 4 players now
		{
			view.setSize((float) window.getSize().x, (float) window.getSize().y);
			view.setRotation(humanPlayers->at(i)->getVehicle()->getRotation() - 180.f);
		}
		if (humanPlayers->size() == 2)
		{
			view.setSize((float) window.getSize().x /2, (float) window.getSize().y);
			view.setRotation(humanPlayers->at(i)->getVehicle()->getRotation() - 180.f);
			view.setViewport(sf::FloatRect(0.5f * i, 0, 0.5f, 1)); // player 1 is on the left, 2 is on the right.
		}
		if (humanPlayers->size() == 3)
		{
			view.setSize((float) window.getSize().x / 2, (float) window.getSize().y / 2);
			view.setRotation(humanPlayers->at(i)->getVehicle()->getRotation() - 180.f);
			if (i == 0 || i == 1)
				view.setViewport(sf::FloatRect(0.5f * i, 0, 0.5f, 0.5f)); // player 1 is on the left, 2 is on the right.
			else
				view.setViewport(sf::FloatRect(0.5f * (i-2), 0.5f, 0.5f, 0.5f)); // player 3 is on left down
		}
		if (humanPlayers->size() == 4)
		{
			view.setSize((float) window.getSize().x / 2, (float) window.getSize().y / 2);
			view.setRotation(humanPlayers->at(i)->getVehicle()->getRotation() - 180.f);
			if (i == 0 || i == 1)
				view.setViewport(sf::FloatRect(0.5f * i, 0, 0.5f, 0.5f)); // player 1 is on the left, 2 is on the right.
			else
				view.setViewport(sf::FloatRect(0.5f * (i - 2), 0.5f, 0.5f, 0.5f)); // player 3 is on left down, player 4 is on the right down
		}
		window.setView(view);
		map.drawMap(window);
		Engine::draw_projectiles(window, projectiles);		// Projectiles don't overwrite on vehicles
		Engine::draw_vehicles(window, vehicles);   // On top of everything
		
		// Drawing the gametimer to the top-left corner TODO: add standings etc.
		if (i == 0)
		{
			gametime.setRotation(humanPlayers->at(0)->getVehicle()->getRotation() - 180.f);
			sf::Vector2i pixelpos = sf::Vector2i(0,0);
			sf::Vector2f worldpos = window.mapPixelToCoords(pixelpos);
			gametime.setPosition(worldpos);
			window.draw(gametime);

			lapCount.setRotation(humanPlayers->at(0)->getVehicle()->getRotation() - 180.f);
			pixelpos = sf::Vector2i(0, 20);
			worldpos = window.mapPixelToCoords(pixelpos);
			lapCount.setPosition(worldpos);
			window.draw(lapCount);
		}

	}


	window.display();							// Update drawings
}

void Engine::updateLap(std::vector<Vehicle>* vehicles, Map & map)
{
	for (auto it = vehicles->begin(); it != vehicles->end(); it++)
	{
		sf::Vector2f pos = it->getPosition();
		sf::Vector2f lastTickPos = it->getLastTickPos();
		std::pair<std::size_t, std::pair<std::size_t, std::size_t>> finishline = map.getFinishline();
		if ( finishline.second.first < lastTickPos.y && lastTickPos.y < finishline.second.second && finishline.second.first < pos.y && pos.y < finishline.second.second)
		{

			if ((lastTickPos.x > finishline.first && pos.x < finishline.first))
			{
				it->decreaselaps();
			}
			else if (lastTickPos.x < finishline.first && pos.x > finishline.first)
			{
				it->increaselaps();
			}
		}
		it->updateLastTickPos(pos);
	}
}
