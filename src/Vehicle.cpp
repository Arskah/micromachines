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
	this->setScale(sf::Vector2f(0.5, 0.5));
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
	else
	{
		this->setSpeed(maxspeed);
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
	{
		this->setSpeed(this->getSpeed() - 1.5 * acceleration * dt);
		if (this->getSpeed() < 0)
			this->setSpeed(0.f);
	}
	else
	{
		this->setSpeed(this->getSpeed() + 1.5 * acceleration * dt);
		if (this->getSpeed() > 0)
			this->setSpeed(0.f);
	}

}

void Vehicle::turn(bool left, float dt)
{
	if (left)
		this->setRotation(this->getRotation() - turnrate * dt);
	else
		this->setRotation(this->getRotation() + turnrate * dt);
}

void Vehicle::slow(float friction, float dt)
{
	if (this->getSpeed() > 0)
	{
		this->setSpeed(this->getSpeed() - friction * dt);
	}
}

/**
 * Prototype of shoot.
 *
 * Needs to be decided on how to deliver shot Projectile to engine.
 */
void Vehicle::shoot()
{

}