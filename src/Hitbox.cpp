#include "Hitbox.h"

/*
* Mathematical constant pi
*/
static const float PI = 3.1415927f;

/*
* Converts degrees to radians
*/
static float degToRad(const float degree)
{
	return degree * PI / 180.f;
}

/*
* Converts radians to degrees
*/
static float radToDeg(const float rad)
{
	return rad * 180.f / PI;
}

/*
Calculate which side a point is compared to a line
*/
static float calculate(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd);

/*
Check if a given point is inside a closed box
*/
static bool pointInsideBox(sf::Vector2f point, sf::VertexArray lines);

/*
Check if two boxes have collided ie. some of their end points are within one another
*/
static bool checkCollisionBetweenHitboxes(sf::VertexArray hitbox1, sf::VertexArray hitbox2);

namespace Hitbox
{
	/*
	Function for the Engine to call for collision checking for two objects.
	*/
	bool checkCollision(const Object * object1, const Object * object2)
	{
		bool value = checkCollisionBetweenHitboxes(createHitboxRect(object1), createHitboxRect(object2));
		return value;
	}

	/*
	Create a Hitbox from an Object pointer. This creates a closed rectangular box that contains the Object with no additional overhead as with the SFML BoundingBox method.
	*/
	sf::VertexArray createHitboxRect(const Object * object)
	{
		if (object->getVertices().getVertexCount() != 4)
			throw std::invalid_argument("createHitboxRect received wrong parameter");

		sf::VertexArray area;
		area.setPrimitiveType(sf::LinesStrip);

		const float len = std::sqrt(std::pow(object->getOrigin().x, 2) + std::pow(object->getOrigin().y, 2));

		for (int i = object->getVertices().getVertexCount() - 1; i >= 0; i--)
		{
			float offset = std::atan((object->getOrigin().y - object->getVertices()[i].position.y) / (object->getOrigin().x - object->getVertices()[i].position.x));
			if (object->getOrigin().y < object->getVertices()[i].position.y)
				offset -= PI;
			area.append(sf::Vector2f(object->getPosition().x + std::cos(degToRad(object->getRotation()) + offset) * len,
				object->getPosition().y + std::sin(degToRad(object->getRotation()) + offset) * len));
		}

		area.append(area[0].position);

		return area;
	}
};

/*
Calculate which side a point is compared to a line
*/
float calculate(sf::Vector2f point, sf::Vector2f lineStart, sf::Vector2f lineEnd)
{
	float value = (point.x - lineStart.x) * (lineEnd.y - lineStart.y) - (point.y - lineStart.y) * (lineEnd.x - lineStart.x);
	return value;
}

/*
Check if a given point is inside a closed box
*/
bool pointInsideBox(sf::Vector2f point, sf::VertexArray lines)
{
	for (std::size_t i = 0; i < lines.getVertexCount() - 1; i++)
	{
		if (calculate(point, lines[i].position, lines[i + 1].position) > 0)
			return false;
	}
	return true;
}

/*
Check if two boxes have collided ie. some of their end points are within one another
*/
bool checkCollisionBetweenHitboxes(sf::VertexArray hitbox1, sf::VertexArray hitbox2)
{
	if (hitbox1.getPrimitiveType() != sf::LinesStrip)
		throw std::invalid_argument("Collision handed invalid box");
	if (hitbox2.getPrimitiveType() != sf::LinesStrip)
		throw std::invalid_argument("Collision handed invalid box");

	if (hitbox1[0].position != hitbox1[hitbox1.getVertexCount() - 1].position)
		throw std::invalid_argument("Hitbox is faulty");
	if (hitbox2[0].position != hitbox2[hitbox2.getVertexCount() - 1].position)
		throw std::invalid_argument("Hitbox is faulty");

	for (std::size_t i = 0; i < hitbox1.getVertexCount() - 1; i++)
	{
		if (pointInsideBox(hitbox1[i].position, hitbox2))
			return true;
	}

	for (std::size_t i = 0; i < hitbox2.getVertexCount() - 1; i++)
	{
		if (pointInsideBox(hitbox2[i].position, hitbox1))
			return true;
	}

	return false;
}