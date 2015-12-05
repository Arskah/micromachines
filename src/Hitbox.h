#pragma once
#ifndef HITBOX_H
#define HITBOX_H

#include "SFML/Graphics/VertexArray.hpp"
#include "Object.h"
#include <memory>

/*
This class is used to create a vector<VertexArray> that is the Hitbox of an object ie. hostile Ammunitions colliding into this area should damage it's host depending on Affiliation.
*/
namespace Hitbox
{
	sf::VertexArray createHitboxRect(const Object * object);
	bool checkCollision(const Object * object1, const Object * object2);
};

#endif