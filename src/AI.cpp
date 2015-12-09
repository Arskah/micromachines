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
	for (auto it : *vehicles)
	{
		Vehicle* aiVehicle = player->getVehicle();
		aiVehicle->getWeapon();
		if ((aiVehicle != &(it)))		// Ai vehicle is in the vehicle vector, so lets not shoot ourselves
		{
			// TODO: Tarkasta ase, aseille ampumissäännöt. Jos jokin toteutuu, return true
		}
	}
	return false;
}

Config::InputType AI::isCrashing(Player* player, std::vector<Vehicle>* vehicles, std::vector<Projectile>* projectiles, Map &map)
{
	// Create dummy object that is invisible and can be used for Hitbox::checkCollision
	Vehicle* aiVehicle = player->getVehicle();
	sf::Texture* nulltex = NULL;
	Vehicle hitTester(nulltex, aiVehicle->getType(), 0.f, 0.f, 0.f, 0.f, *(aiVehicle->getWeapon()));		// This dummy vehicle can be moved to check for collisions with objects

	hitTester.rotate(aiVehicle->getRotation());


	sf::Vector2f movementVec;					//normal vector based on current direction
	const sf::Vector2f forwardVec(0.f, 1.f);	//normal vec pointing forward
	sf::Transform t;							// create dummy object for vector handling
	t.rotate(aiVehicle->getRotation());
	movementVec = t.transformPoint(forwardVec);

	/* Check if other car is in front of AI, then compare speeds. Should try to overtake? */
	for (int dist = 0; dist < 100; dist++)		// Move hitTester 100 pixels in front
	{
		hitTester.move(movementVec);
		for (auto it : *vehicles)
		{
			if ((aiVehicle != &(it)) && Hitbox::checkCollision(&(hitTester), &(it)) && aiVehicle->getSpeed() >= it.getSpeed())		// Check for car in front, and if possible car is slower than aiVehicle car
			{
				// We are hitting a car in front. Do some turning!!
				// TODO: recursive testing should we turn left or right
			}
		}
		
		/* Check for objects on road */
		/*
		if ()
		{

		}
		*/
	}

	/* Check if circuit is turning */
	// TODO: reference circuit for map class
	/*
	if (player->getVehicle()->getRotation() - map.getReferenceDir(player->getVehicle()->getLocation()) > 10)		// Calculate of difference between reference course and current course. If bigger than value, start fixing heading
	{

	}
	*/
	return Config::InputType::None;
}
