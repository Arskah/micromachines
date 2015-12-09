#pragma once
#include "Config.h"
#include "Hitbox.h"
#include "Map.h"
#include "Player.h"
//#include "Object.h"
#include "Vehicle.h"

namespace AI
{
	Config::InputType calculateAIinput(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	bool doShoot(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile> * projectiles, Map& map);
	Config::InputType isCrashing(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map & map);
	//bool 
};
