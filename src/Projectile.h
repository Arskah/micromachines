#pragma once

#include "Object.h"

class Projectile : public Object
{
public:
	//Default constructor.
	Projectile(sf::Texture * const texture, const float speed, const Config::ObjectType type, const float cooldown);

	//Returns cooldown from Projectile.
	float getCooldown() const;

private:
	float cooldown;
};
