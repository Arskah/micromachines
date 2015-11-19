#include "Vehicle.h"

/*
Vehicle default constructor.
NOTE: Location and speed are set to (0,0) and 0 by default.
*/
Vehicle::Vehicle(sf::Texture * const texture, const Config::ObjectType type, const float acceleration, 
				const float maxspeed, const float turnrate, const float weapontimer) : Object(texture, sf::Vector2f(0.f, 0.f), 0.f, type)
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
void Vehicle::accelerate(float dt)
{
	if (this->getSpeed() < maxspeed)
	{
		this->setSpeed(this->getSpeed() + acceleration * dt);
	}

}

/**
* Prototype of brake.
*
* Exponential function of decreasing speed to be added later.
*/
void Vehicle::brake(float dt)
{
	if (this->getSpeed() > 0)
		this->setSpeed(this->getSpeed() - 1.5 * acceleration * dt);
	else
		this->setSpeed(this->getSpeed() + 1.5 * acceleration * dt);
}

void Vehicle::turn(bool left, float dt)
{
	if (left)
		this->setRotation(this->getRotation() - turnrate * dt);
	else
		this->setRotation(this->getRotation() + turnrate * dt);
}

/**
 * Prototype of shoot.
 *
 * Needs to be decided on how to deliver shot Projectile to engine.
 */
void Vehicle::shoot()
{

}