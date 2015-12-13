#pragma once
#include "Config.h"
#include "Hitbox.h"
#include "Map.h"
#include "Player.h"
//#include "Object.h"
#include "Vehicle.h"
#include <math.h>

namespace AI
{
	std::pair<Config::InputType, Config::InputType> calculateAIinput(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	//std::pair<Config::InputType, Config::InputType> AIBeam(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	//Config::InputType doShoot(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);

	//int calcDistance(Object*, Object*);
	//float calcAngle(Object*, Object*);
};
