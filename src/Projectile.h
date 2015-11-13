#pragma once

#include "Object.h"

class Projectile : public Object
{
<<<<<<< HEAD
public:
	//Default constructor.
	Projectile(sf::Texture * const texture, const sf::Vector2u location, const float speed, const int type, const float cooldown);

	//Returns cooldown from Projectile.
	float getCooldown() const;

private:
	float cooldown;
=======

>>>>>>> 907e73a61a51f63dc57ced1954648f7f709b21f3
};
