#pragma once

#include <string>

class Vehicle;

class Player
{
public:
	//Default constructor.
	Player(const std::string name, Vehicle * const vehicle);

	//Returns name from Player.
	std::string getName() const;
	//Returns vehicle from Player.
	Vehicle* getVehicle() const;

private:
	std::string name;
	Vehicle * vehicle;
};