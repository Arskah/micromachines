#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>
#include <list>
#include "Config.h"


class Button
{
public:

	Button();

	~Button() {};

	//create button
	void createButton(std::string name, int player, int state, float loc_X, float loc_y);
	
	//Modify button
	//Add one state to button
	void addState(sf::Texture &texture1, sf::Texture &texture2, sf::Texture &texture3);
	//Raise buttons state
	void raiseState();
	//Lower buttons state
	void lowerState();
	//Move buttons position (sprites position)
	void movePosition(int loc_x, int loc_y);
	//on mouse over state
	void mouseOver();
	//on mouse out state
	void mouseOut();
	//set texture
	void setSpriteTexture();
	//set own sprite texrure
	void setOwnSpriteTexture(sf::Texture tex);

	//read button
	//Returns buttons state
	int getState();
	//Return texture
	sf::Texture getTexture();
	//returns sprite to draw
	sf::Sprite getSprite();
	//get drawable sprite
	sf::Sprite * Button::getDrawable();
	//get button x position
	float getPosition_x();
	//get button y position
	float getPosition_y();
	//get buttoin name
	std::string getName();


private:
	int player = 0;
	int state = 0;
	int max_states = 0;
	float loc_y = 0;
	float loc_x = 0;
	int pressed = 0;
	int mouse_state = 0;

	sf::Sprite sprite;
	std::vector<std::vector<sf::Texture>> textures;
	std::string name;
};