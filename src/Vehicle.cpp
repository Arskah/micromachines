#include "Vehicle.h"


Vehicle::Vehicle(sf::Texture * const texture, const sf::Vector2u location, const float speed, const Config::ObjectType type,
	const float acceleration, const float maxspeed, const float turnrate, const float weapontimer) : Object(texture, location, speed, type)
{
	this->acceleration = acceleration;
	this->maxspeed = maxspeed;
	this->turnrate = turnrate;
	this->weapontimer = weapontimer;
}

/**
 * Prototype of accelerate.
 *
 * Exponential function of increasing speed to be added later.
 */
void Vehicle::accelerate()
{
	this->setSpeed(this->getSpeed() + acceleration);
}

/**
* Prototype of brake.
*
* Exponential function of decreasing speed to be added later.
*/
void Vehicle::brake()
{
	this->setSpeed(this->getSpeed() - acceleration);
}

void Vehicle::turn(bool left)
{
	if (left)
		this->setRotation(this->getRotation() - turnrate);
	else
		this->setRotation(this->getRotation() + turnrate);
}

/**
 * Prototype of shoot.
 *
 * Needs to be decided on how to deliver shot Projectile to engine.
 */
void Vehicle::shoot()
{

}