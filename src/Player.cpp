#include "Player.h"

Player::Player(const std::string name, Vehicle * const vehicle, bool human)
{
	this->name = name;
	this->vehicle = vehicle;
	this->human = human;
}

std::string Player::getName() const
{
	return name;
}

Vehicle* Player::getVehicle() const
{
	return vehicle;
}

bool Player::getHuman() const
{
	return human;
}