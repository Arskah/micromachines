#pragma once

#include "SFML/Graphics.hpp"
#include "Config.h"

class Object : public sf::Drawable, public sf::Transformable
{
public:
	//Returns speed from Object.
	float getSpeed() const;
	//Returns type from Object.
	Config::ObjectType getType() const;
	//Return m_vertices from Object
	sf::VertexArray getVertices() const;
	//Set new speed for the Object. Inherited by Vehicle and Projectile. Meant for Vehicle to be able to accelerate.
	void setSpeed(const float speed);

private:
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
	Object(sf::Texture * const texture, const float speed, const Config::ObjectType type);
};
