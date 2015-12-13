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
	std::pair<Config::InputType, Config::InputType> AIBeam(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	//Config::InputType doAccelerate(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	//Config::InputType doTurn(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	Config::InputType doShoot(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	//Config::InputType isCrashing(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map & map);
};
