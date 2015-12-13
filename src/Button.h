#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>
#include <list>


enum class buttonType {
	pao,
	car,
	start,
	exit,
	map,
	music
};

class Button
{
public:

	Button();

	~Button() {};

	//create button
	void createButton(std::string name, int state, float loc_X, float loc_y);
	
	//Modify button
	//Add one state to button
	void addState(sf::Texture texture1, sf::Texture texture2, sf::Texture texture3);
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

	//read button
	//Returns buttons state
	int getState();
	//Return texture
	sf::Texture getTexture(int mousestate);
	//returns sprite to draw
	sf::Sprite getSprite();
	//get button x position
	int getPosition_x();
	//get button y position
	int getPosition_y();
	//get buttoin name
	std::string getName();


private:
	int player = 0;
	int state = 0;
	int max_states = 0;
	float loc_y = 0;
	float loc_x = 0;
	int pressed = 0;
	buttonType type;
	sf::Sprite sprite;
	std::vector<sf::Texture> textures_temp;
	std::vector<std::vector<sf::Texture>> textures;
	std::string name;
};