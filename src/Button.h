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

	Button(std::string name, int state, float loc_X, float loc_y);

	~Button() {};

	//Modify button
	//Add one state to button
	void addState(sf::Texture texture1, sf::Texture texture2, sf::Texture texture3);
	//Raise buttons state
	bool raiseState();
	//Lower buttons state
	bool lowerState();
	//Move buttons position (sprites position)
	void movePosition(int loc_x, int loc_y);

	//read button
	//Returns buttons state
	int getState();
	//Return texture
	sf::Texture getTexture(int mousestate);
	//returns sprite to draw
	sf::Sprite getSprite(int mousestate);
	std::vector<int> getPosition();



private:
	int player;
	int state;
	int max_states;
	float loc_y;
	float loc_x;
	int pressed = 0;
	buttonType type;
	sf::Sprite sprite;
	std::vector<sf::Texture> textures_temp;
	std::vector<std::vector<sf::Texture>> textures;
	std::string name;

};