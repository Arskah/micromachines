#pragma once

#include "Object.h"

/*
The class defining a Vehicle object.
*/
class Vehicle : public Object
{
public:
	//Default constructor
	Vehicle(sf::Texture * const texture, const Config::ObjectType type,
		const float acceleration, const float maxspeed, const float turnrate, const float weapontimer); //Projectile * weapon);

	//Increases speed of the Vehicle by a function of member variable acceleration.
	void accelerate();
	//Decreases speed of the Vehicle by a function of member variable acceleration.
	void brake();
	//Increases rotation angle of the Vehicle by a function of member variable turnrate.
	void turn(bool left);
	//Launches a Projectile from the Vehicle
	void shoot();

private:
	float acceleration;
	float maxspeed;
	float turnrate;
	float weapontimer;
	//Projectile weapon
};
