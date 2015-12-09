#pragma once

#include <string>

class Vehicle;

class Player
{
public:
	//Default constructor.
	Player(const std::string name, Vehicle * const vehicle, bool human = true);

	//Returns name from Player.
	std::string getName() const;
	//Returns vehicle from Player.
	Vehicle* getVehicle() const;
	//Returns false for AI
	bool getHuman() const;

private:
	std::string name;
	Vehicle * vehicle;
	bool human;
};