#include "Projectile.h"

Projectile::Projectile(sf::Texture * const texture, const sf::Vector2u location, const float speed, const int type, const float cooldown) : Object(texture, location, speed, type)
{
	this->cooldown = cooldown;
}

float Projectile::getCooldown() const
{
	return cooldown;
}

