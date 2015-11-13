#pragma once

<<<<<<< HEAD
#include "SFML\Graphics.hpp"

class Object : public sf::Drawable, public sf::Transformable
{
public:
	//Returns location from Object.
	sf::Vector2u getLocation() const;
	//Returns speed from Object.
	float getSpeed() const;
	//Returns type from Object.
	int getType() const;

private:
	sf::Vector2u location;
	float speed;
	int type;

	//Loads texture to Object.
	void loadTexture(sf::Texture * const texture);

	//Makes object drawable to sf::RenderWindow with: window.draw(Object);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture * m_texture;

protected:
	//Default constructor.
	Object(sf::Texture * const texture, const sf::Vector2u location, const float speed, const int type);

	//Set new speed for the Object. Inherited by Vehicle and Projectile. Meant for Vehicle to be able to accelerate.
	void setSpeed(const float speed);
=======
class Object
{

>>>>>>> 907e73a61a51f63dc57ced1954648f7f709b21f3
};
