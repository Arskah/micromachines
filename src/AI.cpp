#include "AI.h"

Config::InputType AI::calculateAIinput(Player * player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map & map)
{
	Config::InputType input;
	if ((input = AI::isCrashing(player, vehicles, projectiles, map)) == Config::InputType::None)	//Turning and avoiding collisions is #1 priority
		if (AI::doShoot(player, vehicles, projectiles, map))								// Shoot if opportunity
			return Config::InputType::Shoot;
		else
			return Config::InputType::Accelerate;
	return input;
}

bool AI::doShoot(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map &map)
{
	/*
	Vehicle* aiVehicle = player->getVehicle();
	Projectile* weapon = aiVehicle->getWeapon();
	if (aiVehicle->getWeapontimer() >= weapon->getCooldown())		// Check that AI can shoot
	{
		for (auto it : *vehicles)			// Loop for finding targets
		{
			if ((aiVehicle != &(it)))		// Ai vehicle is in the vehicle vector, so lets not shoot ourselves.
			{
				switch (weapon->getType())		// Check what weapon is in use. If shooting condition = true, fire.
				{
				case Config::ObjectType::Mine:
					if ()						// Condition to shoot
						return true;			// Shoot
					break;
				case Config::ObjectType::Oilspill:
					if ()
						return true;
					break;
				default:
					break;
				}
			}
		}
	}
	*/
	return false;
}

Config::InputType AI::isCrashing(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map &map)
{
	// Create dummy object that is invisible and can be used for Hitbox::checkCollision
	Vehicle* aiVehicle = player->getVehicle();
	sf::Texture* nulltex = NULL;


	//Vehicle hitTester(nulltex, aiVehicle->getType(), 0.f, 0.f, 0.f, 0.f, *(aiVehicle->getWeapon()));		// This dummy vehicle can be moved to check for collisions with objects

	//hitTester.rotate(aiVehicle->getRotation());


	//sf::Vector2f movementVec;					//normal vector based on current direction
	//const sf::Vector2f forwardVec(0.f, 1.f);	//normal vec pointing forward
	//sf::Transform t;							// create dummy object for vector handling
	//t.rotate(aiVehicle->getRotation());
	//movementVec = t.transformPoint(forwardVec);

	//unsigned int recursionLevel = 0;

	///* Check if other car is in front of AI, then compare speeds. Should try to overtake? */
	//for (int dist = 0; dist < 100; dist++)		// Move hitTester 100 pixels in front
	//{
	//	hitTester.move(movementVec);
	//	for (auto it : *vehicles)
	//	{
	//		if ((aiVehicle != &(it)) && Hitbox::checkCollision(&(hitTester), &(it)) && aiVehicle->getSpeed() > it.getSpeed())		// Check for car in front, and if possible car is slower than aiVehicle car
	//		{
	//			// We are hitting a car in front. Do some turning!!
	//			// TODO: recursive testing should we turn left or right
	//		}
	//	}

	//	/* Check for objects on road */
	//	for (auto it : *projectiles)
	//	{
	//		if (Hitbox::checkCollision(&(hitTester), &(it)))
	//		{
	//			//We are hitting a mine etc. in front
	//		}
	//	}
	//}

	/* Check if circuit is turning */

	// Go through the beams
	std::vector<std::pair<int, float>> beams;
	int maxdistance = 500;								// Max distance AI "sees" the turn and starts to do playing moves
	int minFov = aiVehicle->getRotation() - 30;			// 60 deg field of view
	int maxFov = aiVehicle->getRotation() + 30;

	for (int angle = minFov; angle < maxFov + 30; angle++)
	{
		for (int distance = 0; distance < maxdistance; distance++)
		{
			int x = distance * sin(angle);
			int y = distance * cos(angle);
			Block block = map.getBlock(x, y);
			if (block.getType() != map.getTrackMaterial())
			{
				std::pair<int, float> pair;
				pair.first = angle;
				pair.second = distance;
				beams.push_back(pair);
				break;
			}
		}
	}
	if (!beams.empty())
	{
		// Find maximum distance and corresponding angle
		std::pair<int, float> maxpair;
		for (auto it = beams.begin(); it != beams.end(); it++)
		{
			if (it->second > maxpair.second)
				maxpair.first = it->first;
			maxpair.second = it->second;
		}
		if (maxpair.first > aiVehicle->getRotation())
			return Config::InputType::TurnRight;
		if (maxpair.first < aiVehicle->getRotation())
			return Config::InputType::TurnLeft;
	}

	return Config::InputType::None;
}
