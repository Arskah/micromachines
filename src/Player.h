#pragma once

<<<<<<< HEAD
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
=======
class Player
{

>>>>>>> 907e73a61a51f63dc57ced1954648f7f709b21f3
};