#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Config.h"
#include <stdlib.h>

enum class buttonType {
    pao,
    car,
    start,
    exit,
	map
};

struct button {
	int player;
	int state;
	int max_states;
	float loc_y;
	float loc_x;
    buttonType type;
        
	sf::Sprite spri;
	std::vector<sf::Texture> textures;
};


class Menu
{
public:
	Menu(sf::RenderWindow& window, ResourceManager * resourcemanager);
	~Menu() {}

	void loadContent();
	void createButtons();
	std::string checkName(button it_button);

	bool runMenu(sf::RenderWindow& window, std::vector<std::pair<const std::string, Config::ObjectType>> &playerdata, std::string &mapdata);
	void draw(sf::RenderWindow& window);


//	int getAmountItems() const;
//	sf::Text getSelected() const;

//	sf::RenderWindow window;
	int width;
	int height;

private:
    
	float offset_x = 100;
	float offset_y = 100;
	int amount_players = 4;
	int heightDivider = 7;

    sf::Font font;
    //static buttons 
	button map;
	button start;
    button exit;
        
	ResourceManager* resourcemanager;
    sf::RenderWindow& window;
	sf::Image backgroundImage;
        
	std::vector<struct button> buttons;


	// declare all button images
	// numerators
	sf::Texture tex_num1;
	sf::Sprite spri_num1;

	sf::Texture tex_num2;
	sf::Sprite spri_num2;

	sf::Texture tex_num3;
	sf::Sprite spri_num3;

	sf::Texture tex_num4;
	sf::Sprite spri_num4;
	
        // player opptions
	sf::Texture tex_player_N;
	sf::Texture tex_player_O;
	sf::Texture tex_player_P;

	sf::Texture tex_ai_N;
	sf::Texture tex_ai_O;
	sf::Texture tex_ai_P;

	sf::Texture tex_off_N;
	sf::Texture tex_off_O;
	sf::Texture tex_off_P;
	sf::Sprite spri_player;

	// start/exit
	sf::Texture tex_start_N;
	sf::Texture tex_start_O;
	sf::Texture tex_start_P;
	sf::Sprite spri_start;

	sf::Texture tex_exit_N;
	sf::Texture tex_exit_O;
	sf::Texture tex_exit_P;
	sf::Sprite spri_exit;



	//Load map texture for develop use
	sf::Texture tex_map1;
	sf::Sprite spri_map1;
        
    //Load car textures
    sf::Sprite spri_car;
};







// Not in use - Jan G.
//class SettingsMenu : public Menu
//{
//	SettingsMenu(sf::RenderWindow& window) : Menu(window)
//	{
//
//	}
//protected:
//	virtual void select();
//private:
//	sf::Image* backgroundImage;
//	//sf::Font font = ;
//	std::vector<std::pair<sf::Text, std::string>> items;
//};
//
//class SinglePlayerMenu : public Menu
//{
//	SinglePlayerMenu(sf::RenderWindow& window) : Menu(window)
//	{
//
//	}
//protected:
//	virtual void select();
//private:
//	sf::Image* backgroundImage;
//	//sf::Font font = ;
//	std::vector<std::pair<sf::Text, std::string>> items;
//};
//
//class MultiPlayerMenu : public Menu
//{
//	MultiPlayerMenu(sf::RenderWindow& window) : Menu(window)
//	{
//
//	}
//protected:
//	virtual void select();
//private:
//	sf::Image* backgroundImage;
//	//sf::Font font = ;
//	std::vector<std::pair<sf::Text, std::string>> items;
//};
//
//class PauseMenu : public Menu
//{
//	PauseMenu(sf::RenderWindow& window) : Menu(window)
//	{
//
//	}
//protected:
//	virtual void select();
//private:
//	sf::Image* backgroundImage;
//	//sf::Font font = ;
//	std::vector<std::pair<sf::Text, std::string>> items;
//};
