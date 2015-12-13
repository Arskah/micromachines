#include "AI.h"

std::pair<Config::InputType, Config::InputType> AI::calculateAIinput(Player * player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map & map)
{
	//std::pair<Config::InputType, Config::InputType> input_pair;			// First for Accelerate/Brake, Second for turn or shoot

	//input_pair = AI::AIBeam(player, vehicles, projectiles, map);

	//if (input_pair.second == Config::InputType::None)
	//	input_pair.second = AI::doShoot(player, vehicles, projectiles, map);
	//return input_pair;
	return std::pair<Config::InputType, Config::InputType>(Config::InputType::None, Config::InputType::None);		// Bypass AI, no AI calculation for release :(
}
//std::pair<Config::InputType, Config::InputType> AI::AIBeam(Player * player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map & map)
//{
//	std::pair<Config::InputType, Config::InputType> input_pair(Config::InputType::None, Config::InputType::None);
//	Vehicle* aiVehicle = player->getVehicle();
//
//	// Create dummy object that is invisible and can be used for Hitbox::checkCollision
//	//sf::Texture* nulltex = NULL;
//	//Vehicle hitTester(nulltex, aiVehicle->getType(), 0.f, 0.f, 0.f, 0.f, *(aiVehicle->getWeapon()));		// This dummy vehicle can be moved to check for collisions with objects
//	//hitTester.rotate(aiVehicle->getRotation());
//	//sf::Vector2f movementVec;					//normal vector based on current direction
//	//const sf::Vector2f forwardVec(0.f, 1.f);	//normal vec pointing forward
//	//sf::Transform t;							// create dummy object for vector handling
//	//t.rotate(aiVehicle->getRotation());
//	//movementVec = t.transformPoint(forwardVec);
//
//	std::vector<std::pair<float, int>> beams;
//	int maxdistance = 1000;									// Max distance AI "sees" the turn and starts to do playing moves
//	int maxOffsetDeg = 20;									// AI starts to correct heading if more than 5 degree offset
//	float minFov = aiVehicle->getRotation() - 30;			// 60 deg field of view
//	float maxFov = aiVehicle->getRotation() + 30;
//	float aiPosX = aiVehicle->getPosition().x;
//	float aiPosY = aiVehicle->getPosition().y;
//	Config::BlockType trackMaterial = map.getTrackMaterial();
//
//	Block aiblock = map.getBlock((int)aiPosX, (int)aiPosY);
//	if (aiblock.getType() != trackMaterial && aiblock.getType() != Config::BlockType::Checkerboard)			// If Ai not on road find closest track material
//	{
//		for (float angle = 0; angle <= 360; angle = angle + 5 )
//		{
//			for (int distance = 0; distance <= maxdistance; distance = distance + 100)
//			{
//				double x = std::round(aiPosX - distance * sin((angle)* 3.14159265 / 180));		// Deg to rad
//				double y = std::round(aiPosY + distance * cos((angle)* 3.14159265 / 180));
//				Block block = map.getBlock((int)x, (int)y);
//				if (block.getType() == Config::BlockType::RockWall)		// Impassable routes need to be taken in to account
//					break;
//				if (block.getType() == trackMaterial || block.getType() == Config::BlockType::Checkerboard)
//				{
//					std::pair<float, int> pair;
//					pair.first = angle;
//					pair.second = distance;
//					beams.push_back(pair);
//					break;
//				}
//			}
//		}
//		if (!beams.empty())
//		{
//			// Find maximum distance and corresponding angle
//			std::pair<float, int> minpair;
//			minpair.first = -1;		// -1 Deg so gets overwritten
//			minpair.second = 1000;	// 1000 so gets overwritten. RISKY!
//			for (auto it = beams.begin(); it != beams.end(); it++)
//			{
//				if (it->second < minpair.second)
//				{
//					minpair.first = it->first;
//					minpair.second = it->second;
//				}
//			}
//			if (aiVehicle->getRotation() + 90 < minpair.first || minpair.first > 270 + aiVehicle->getRotation())		// If turn would be too great, reverse
//			{
//				input_pair.first = Config::InputType::Brake;
//			}
//			else								// Else accelerate
//			{
//				input_pair.first = Config::InputType::Accelerate;
//			}
//			// Check if need to turn
//			if (minpair.first - maxOffsetDeg > aiVehicle->getRotation())
//				input_pair.second = Config::InputType::TurnRight;
//			else if (minpair.first + maxOffsetDeg < aiVehicle->getRotation())
//				input_pair.second = Config::InputType::TurnLeft;
//			else
//				input_pair.second = Config::InputType::None;
//		}
//		else
//		{
//			input_pair.first = Config::InputType::None;
//			input_pair.second = Config::InputType::None;
//		}
//	}
//	else
//	{
//		for (float angle = minFov; angle <= maxFov; angle++)
//		{
//			for (int distance = 0; distance <= maxdistance; distance = distance + 100)
//			{
//
//				//if (distance < 500)
//				//{
//				//	hitTester.move(movementVec);
//				//	for (auto it : *vehicles)
//				//	{
//				//		if ((aiVehicle != &(it)) && Hitbox::checkCollision(&(hitTester), &(it)) && aiVehicle->getSpeed() > it.getSpeed())		// Check for car in front, and if possible car is slower than aiVehicle car
//				//		{
//				//			break;
//				//		}
//				//	}
//				//	for (auto it : *projectiles)
//				//	{
//				//		if (Hitbox::checkCollision(&(hitTester), &(it)))
//				//		{
//				//			break;
//				//		}
//				//	}
//				//}
//
//				double x = std::round(aiPosX - distance * sin((angle)* 3.14159265 / 180));		// Deg to rad
//				double y = std::round(aiPosY + distance * cos((angle)* 3.14159265 / 180));
//				Block block = map.getBlock((int)x, (int)y);
//				if ((block.getType() != trackMaterial && block.getType() != Config::BlockType::Checkerboard) || (distance == maxdistance && block.getType() == trackMaterial))		// If on road find longest path for something else than road, drive there
//				{
//					std::pair<float, int> pair;
//					pair.first = angle;
//					pair.second = distance;
//					beams.push_back(pair);
//					break;
//				}
//			}
//		}
//		if (!beams.empty())
//		{
//			// Find maximum distance and corresponding angle
//			std::pair<float, int> maxpair;
//			maxpair.first = 0;
//			maxpair.second = 0;
//			for (auto it = beams.begin(); it != beams.end(); it++)
//			{
//				if (it->second > maxpair.second)
//				{
//					maxpair.first = it->first;
//					maxpair.second = it->second;
//				}
//			}
//			// Check accelerate/brake
//			if (maxpair.second > 100)
//				input_pair.first = Config::InputType::Accelerate;
//			else
//				input_pair.first = Config::InputType::Brake;
//
//			// Check if need to turn
//			if (maxpair.first - maxOffsetDeg > aiVehicle->getRotation())
//				input_pair.second = Config::InputType::TurnRight;
//			else if (maxpair.first + maxOffsetDeg < aiVehicle->getRotation())
//				input_pair.second = Config::InputType::TurnLeft;
//			else
//				input_pair.second = Config::InputType::None;
//		}
//		else
//		{
//			input_pair.first = Config::InputType::None;
//			input_pair.second = Config::InputType::None;
//		}
//	}
//
//	return input_pair;
//}
//
//Config::InputType AI::doShoot(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map &map)
//{
//	
//	Vehicle* aiVehicle = player->getVehicle();
//	Projectile* weapon = aiVehicle->getWeapon();
//	if (aiVehicle->getWeapontimer() >= weapon->getCooldown())		// Check that AI can shoot
//	{
//		for (auto it : *vehicles)			// Loop for finding targets
//		{
//			if ((aiVehicle != &(it)))		// Ai vehicle is in the vehicle vector, so lets not shoot ourselves.
//			{
//				switch (weapon->getType())		// Check what weapon is in use. If shooting condition = true, fire.
//				{
//				case Config::ObjectType::Mine:
//					if (false)						// Condition to shoot
//						return Config::InputType::Shoot;			// Shoot
//					break;
//				case Config::ObjectType::Oilspill:
//					if (false)
//						return Config::InputType::Shoot;
//					break;
//				default:
//					break;
//				}
//			}
//		}
//	}
//	
//	return Config::InputType::None;
//}