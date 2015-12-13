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

	//Returns the projectile of the vehicle.
	Projectile * getWeapon() const;
	//Returns the time that has passed since the projectile was last launched.
	float getWeapontimer() const;
	//Increments the timer by adding dt to it.
	void setWeapontimer(float dt);
	
	//Returns true/false depending on if the vehicle has driven into an oilspill.
	//This will prevent steering for one second.
	bool getPenalty() const;
	//Change the state of the penalty.
	void setPenalty(bool penalty);
	//Returns the time the vehicle has been in the penalty state.
	float getPenaltytimer() const;
	//Increments the penalty timer by adding dt to it.
	void setPenaltytimer(float dt);
	//Sets the penaltytimer to 0 and the state to false.
	void resetPenaltytimer();

private:
	float acceleration;
	float maxspeed;
	float turnrate;
	float weapontimer;
	float braketimer = 0.f;
	bool penalty = false;
	float penaltytimer = 0.f;
	Projectile weapon;
};
