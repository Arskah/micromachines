#pragma once

#include "SFML/Graphics.hpp"
#include "Config.h"

class Object : public sf::Drawable, public sf::Transformable
{
public:
	//Returns location from Object.
	sf::Vector2u getLocation() const;
	//Returns speed from Object.
	float getSpeed() const;
	//Returns type from Object.
	Config::ObjectType getType() const;

private:
	sf::Vector2u location;
	float speed;
	Config::ObjectType type;

	//Loads texture to Object.
	void loadTexture(sf::Texture * const texture);

	//Makes object drawable to sf::RenderWindow with: window.draw(Object);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture * m_texture;

protected:
	//Default constructor.
	Object(sf::Texture * const texture, const sf::Vector2u location, const float speed, const Config::ObjectType type);

	//Set new speed for the Object. Inherited by Vehicle and Projectile. Meant for Vehicle to be able to accelerate.
	void setSpeed(const float speed);
};
