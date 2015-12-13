#include "Projectile.h"

Projectile::Projectile(sf::Texture * const texture, const sf::Vector2f location, const float speed, const Config::ObjectType type, const float cooldown) : Object(texture, location, speed, type)
{
	this->cooldown = cooldown;
	this->setSpeed(speed);
}

float Projectile::getCooldown() const
{
	return cooldown;
}

