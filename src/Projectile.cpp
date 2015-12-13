#include "Projectile.h"

Projectile::Projectile(sf::Texture * const texture, const float speed, const Config::ObjectType type, const float cooldown) : Object(texture, speed, type)
{
	this->cooldown = cooldown;
	this->setSpeed(speed);
}

float Projectile::getCooldown() const
{
	return cooldown;
}

