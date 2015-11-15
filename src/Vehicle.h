#pragma once

#include "Object.h"

class Vehicle : public Object
{
<<<<<<< HEAD
public:
	//Default constructor
	Vehicle(sf::Texture * const texture, const sf::Vector2u location, const float speed, const Config::ObjectType type,
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
=======

>>>>>>> 907e73a61a51f63dc57ced1954648f7f709b21f3
};
