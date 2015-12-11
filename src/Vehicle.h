#pragma once

#include "Object.h"
#include "Projectile.h"
#include <cmath>

/*
The class defining a Vehicle object.
*/
class Vehicle : public Object
{
public:
	//Default constructor
	Vehicle(sf::Texture * const texture, const Config::ObjectType type,
		const float acceleration, const float maxspeed, const float turnrate, const float weapontimer, Projectile projectile);
	
	//Increases speed of the Vehicle by a function of member variable acceleration.
	void accelerate(float dt);
	//Decreases speed of the Vehicle by a function of member variable acceleration.
	void brake(float dt);
	//Increases rotation angle of the Vehicle by a function of member variable turnrate.
	void turn(bool left, float dt);
	//Launches a Projectile from the Vehicle.
	Projectile shoot();
	//Decreases the speed based on the friction of the underlying block.
	void slow(float friction, float dt);

	Projectile * getWeapon();
	float getWeapontimer();
	void setWeapontimer(float dt);

private:
	float acceleration;
	float maxspeed;
	float turnrate;
	float weapontimer;
	float braketimer = 0.f;
	float penaltytimer = 0.f;
	Projectile weapon;
};
