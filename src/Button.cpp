#include <SFML/Graphics/Rect.hpp>

#include "Button.h"
#include <stdlib.h>

Button::Button(std::string name, int state, float loc_x, float loc_y)
{
	name = name;
	state = state;
	loc_x = loc_x;
	loc_y = loc_y;
}
void Button::addState(sf::Texture texture1, sf::Texture texture2, sf::Texture texture3)
{
	textures_temp.push_back(texture1);
	textures_temp.push_back(texture2);
	textures_temp.push_back(texture3);
	textures.push_back(textures_temp);
	textures_temp.pop_back();
	textures_temp.pop_back();
	textures_temp.pop_back();
	max_states++;
}
bool Button::raiseState() 
{
	if (state < max_states-1)
	{
		state++;
		return true;
	}
	else
		return false;
}
bool Button::lowerState()
{
	if (state != 0)
	{
		state--;
		return true;
	}
	else
		return false;
}
void Button::movePosition(int loc_x, int loc_y)
{
	sprite.setPosition(loc_x, loc_y);
}
int Button::getState()
{
	return state;
}
sf::Texture Button::getTexture(int mousestate)
{
	textures_temp = textures.at(state);
	return textures_temp.at(mousestate);
}
sf::Sprite Button::getSprite(int mousestate)
{
	textures_temp = textures.at(state);
	sprite.setTexture(textures_temp.at(mousestate), true);
	return sprite;
}
std::vector<int> Button::getPosition()
{
	std::vector<int> temp;
	temp.push_back(loc_x);
	temp.push_back(loc_y);
	return temp;
}

