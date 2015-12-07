#include "Vehicle.h"

/*
Vehicle default constructor.
NOTE: Location and speed are set to (0,0) and 0 by default.
*/
Vehicle::Vehicle(sf::Texture * const texture, const Config::ObjectType type, const float acceleration, 
				const float maxspeed, const float turnrate, const float weapontimer, Projectile projectile) : Object(texture, sf::Vector2f(0.f, 0.f), 0.f, type), weapon(projectile)
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
		this->setRotation(this->getRotation() - (this->getSpeed()/this->maxspeed) * turnrate * dt);
	else
		this->setRotation(this->getRotation() + (this->getSpeed()/this->maxspeed) * turnrate * dt);
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
Projectile Vehicle::shoot()
{
	// This solution actually only applies to mines and such
	sf::Transform t;
	t.rotate(this->getRotation() + 180.f); // This points to the opposite direction of the car's heading
	sf::Vector2f vec(0.f, 1.f);
	sf::Vector2f direction = t.transformPoint(vec);
	direction *= 80.f; // Offset for the projectile

	this->weapon.setPosition(direction + this->getPosition());
	this->weapontimer = 0.f;
	return this->weapon;
}

Projectile * Vehicle::getWeapon()
{
	return &this->weapon;
}

float Vehicle::getWeapontimer()
{
	return weapontimer;
}

void Vehicle::setWeapontimer(float dt)
{
	this->weapontimer += dt;
}