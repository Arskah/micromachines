#include "Player.h"

Player::Player(const std::string name, Vehicle * const vehicle)
{
	this->name = name;
	this->vehicle = vehicle;
}

std::string Player::getName() const
{
	return name;
}

Vehicle* Player::getVehicle() const
{
	return vehicle;
}