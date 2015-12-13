#include "Object.h"

Object::Object(sf::Texture * const texture, const float speed, const Config::ObjectType type)
{
	if (texture)
		loadTexture(texture);
	
	this->speed = speed;
	this->type = type;
}


float Object::getSpeed() const
{
	return speed;
}

Config::ObjectType Object::getType() const
{
	return type;
}

/*
Returns vertices, mainly for Hitbox
*/
sf::VertexArray Object::getVertices() const
{
	return m_vertices;
}

void Object::loadTexture(sf::Texture * const texture)
{
	//Assign texture to self
	m_texture = texture;

	//Make a box to go around it
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);

	//Take texture sizes
	float textureX = float(m_texture->getSize().x);
	float textureY = float(m_texture->getSize().y);

	//Build box according to these sizes
	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(textureX / 4.f, 0);
	m_vertices[2].position = sf::Vector2f(textureX / 4.f, textureY / 4.f);
	m_vertices[3].position = sf::Vector2f(0, textureY / 4.f);

	//Also the same box for the actual texture
	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(textureX, 0);
	m_vertices[2].texCoords = sf::Vector2f(textureX, textureY);
	m_vertices[3].texCoords = sf::Vector2f(0, textureY);

	//Set origin to middle of box. This is the coordinate that the inherited getPosition() returns.
	this->setOrigin(m_vertices[2].position.x / 2, m_vertices[2].position.y / 2);
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	states.texture = m_texture;			// apply the texture
	target.draw(m_vertices, states);	// draw the vertex array
}

void Object::setSpeed(const float speed)
{
	this->speed = speed;
}