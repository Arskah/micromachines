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
	// Normal braking situation (decreasing speed)
	if (this->getSpeed() > 0.f)
	{
		this->setSpeed(this->getSpeed() - 3.f * acceleration * dt);
		if (this->getSpeed() < 0.f)
			this->setSpeed(0.f);
	}

	// Car is already standing still -> increase braketimer
	if (this->getSpeed() == 0.f)
	{
		this->braketimer += dt;
	}

	// After 0.5 seconds of standing still the car can reverse
	if (this->braketimer > 0.5f)
	{
		// The reversing acceleration is half of the forward acceleration
		this->setSpeed(this->getSpeed() - 0.5f * acceleration * dt);
		// The maximum reversing speed is half of the forward maximum speed
		if (this->getSpeed() < - 0.5f * this->maxspeed)
			this->setSpeed(- 0.5f * maxspeed);
		// No longer reversing -> set the braketimer to zero again
		if (this->getSpeed() >= 0.f)
			this->braketimer = 0.f;
	}
}

void Vehicle::turn(bool left, float dt)
{
	/* This needs some explaining...
	(this->getSpeed() / abs(this->getSpeed())) simply makes sure the sign of the speed stays the same (e.g. minus or plus)
	sqrt(abs(this->getSpeed() / this->maxspeed)) makes the cars turn better when they have low speed
	(1.5f - abs(this->getSpeed()) / this->maxspeed) makes it more dificult to steer when the speed gets high
	turnrate * dt is simply the rate of turning
	*/
	if (this->getSpeed() != 0.f)
	{
		if (left)
		{
			this->setRotation(this->getRotation() - (this->getSpeed() / abs(this->getSpeed())) * sqrt(abs(this->getSpeed() / this->maxspeed)) * (1.5f - abs(this->getSpeed()) / this->maxspeed) * turnrate * dt);
		}

		else
		{
			this->setRotation(this->getRotation() + (this->getSpeed() / abs(this->getSpeed())) * sqrt(abs(this->getSpeed() / this->maxspeed)) * (1.5f - abs(this->getSpeed()) / this->maxspeed) * turnrate * dt);
		}
	}
}

void Vehicle::slow(float friction, float dt)
{
	// Slowing friction while going forward
	if (this->getSpeed() > 0)
	{
		this->setSpeed(this->getSpeed() - (abs(this->getSpeed())/this->maxspeed) * pow(friction,3) * dt);
		// Making sure the car stops properly and doesn't just reverse direction
		if (this->getSpeed() < 0)
		{
			this->setSpeed(0.f);
		}
	}

	// Same but backwards
	if (this->getSpeed() < 0)
	{
		this->setSpeed(this->getSpeed() + (abs(this->getSpeed()) / this->maxspeed) * pow(friction,3) * dt);
		// Making sure the car stops properly and doesn't just reverse direction
		if (this->getSpeed() > 0)
		{
			this->setSpeed(0.f);
		}
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
	direction *= 100.f; // Offset for the projectile

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