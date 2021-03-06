#include <SFML/Graphics/Rect.hpp>

#include "Button.h"
#include <stdlib.h>

Button::Button(){}
void Button::createButton(std::string name1, int player1, int state1, float loc_x1, float loc_y1)
{
	player = player1;
	name = name1;
	state = state1;
	loc_x = loc_x1;
	loc_y = loc_y1;
}
void Button::addState(sf::Texture &texture1, sf::Texture &texture2, sf::Texture &texture3)
{
	std::vector<sf::Texture> textures_temp;
	textures_temp.push_back(texture1);
	textures_temp.push_back(texture2);
	textures_temp.push_back(texture3);
	textures.push_back(textures_temp);
	sprite.setTexture(texture1);
	sprite.setPosition(loc_x, loc_y);
	max_states++;
}
void Button::raiseState() 
{
	if (state < max_states-1)
	{
		state++;
		mouse_state = 2;
		std::vector<sf::Texture> textures_temp;
		textures_temp = textures.at(state);
		sprite.setTexture(textures_temp.at(0), true);
	}
	else
	{
		state = 0;
		mouse_state = 2;
		std::vector<sf::Texture> textures_temp;
		textures_temp = textures.at(state);
		sprite.setTexture(textures_temp.at(0), true);
	}
}
void Button::lowerState()
{
	if (state != 0)
	{
		state--;
		mouse_state = 2;
		std::vector<sf::Texture> textures_temp;
		textures_temp = textures.at(state);
		sprite.setTexture(textures_temp.at(0), true);
	}
	else
	{
		state = max_states - 1;
		mouse_state = 2;
		std::vector<sf::Texture> textures_temp;
		textures_temp = textures.at(state);
		sprite.setTexture(textures_temp.at(0), true);
	}
}
void Button::movePosition(int loc_x, int loc_y)
{
	sprite.setPosition((float) loc_x, (float) loc_y);
}
void Button::mouseOver()
{
	mouse_state = 1;
	std::vector<sf::Texture> textures_temp;
	textures_temp = textures.at(state);
	sprite.setTexture(textures_temp.at(1), true);
}
void Button::mouseOut()
{
	mouse_state = 0;
	std::vector<sf::Texture> textures_temp;
	textures_temp = textures.at(state);
	sprite.setTexture(textures_temp.at(0), true);
}
void Button::setSpriteTexture()
{
	std::vector<sf::Texture> textures_temp;
	textures_temp = textures.at(state);
	sprite.setTexture(textures_temp.at(0), true);
}
void Button::setOwnSpriteTexture(sf::Texture tex) 
{
	sprite.setTexture(tex);
}

int Button::getState()
{
	return state;
}
sf::Texture Button::getTexture()
{
	std::vector<sf::Texture> textures_temp;
	textures_temp = textures.at(state);
	return textures_temp.at(mouse_state);
}
sf::Sprite  Button::getSprite()
{
	return sprite;
}
sf::Sprite * Button::getDrawable()
{
	return &(sprite);
}
float Button::getPosition_x()
{
	return  loc_x;
}
float Button::getPosition_y()
{
	return  loc_y;
}
std::string Button::getName()
{
	return name;
}

