#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Config.h"
#include "Map.h"
#include <stdlib.h>
#include <vector>
#include <list>

enum class buttonType {
    pao,
    car,
    start,
    exit,
	map,
	music,
	editor
};

struct button {
	int player;
	int state;
	int max_states;
	float loc_y;
	float loc_x;
	int pressed = 0;
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
	std::string checkName(button &it_button);
	std::string checkMap(button it_button);

	bool runMenu(sf::RenderWindow& window, std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> &playerdata, std::string &mapdata, sf::Music &music, bool& start_editor);
	void draw(sf::RenderWindow& window);


//	int getAmountItems() const;
//	sf::Text getSelected() const;

//	sf::RenderWindow window;
	int width;
	int height;

private:
	int amount_players = 4;
	int heightDivider = 7;

    sf::Font font;
    //static buttons 
	button map;
	button start;
    button exit;
	button music;
	button editor;
        
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

	// start textures
	sf::Texture tex_start_N;
	sf::Texture tex_start_O;
	sf::Texture tex_start_P;
	sf::Sprite spri_start;

	//exit textures
	sf::Texture tex_exit_N;
	sf::Texture tex_exit_O;
	sf::Texture tex_exit_P;
	sf::Sprite spri_exit;

	//Load map texture for develop use
	sf::Texture tex_map1;
	sf::Texture tex_map2;
	sf::Texture tex_map3;
	sf::Sprite spri_map1;
        
    //Load car images
	sf::Texture tex_car1;
	sf::Texture tex_car2;
	sf::Texture tex_car3;
	sf::Texture tex_car4;
    sf::Sprite spri_car;

	//Load music texture
	sf::Texture tex_music1;
	sf::Texture tex_music2;
	sf::Texture tex_music3;
	sf::Texture tex_music4;
	sf::Texture tex_music5;
	sf::Texture tex_music6;
	sf::Sprite spri_music;

	//Load editor textures 
	sf::Texture tex_editor1;
	sf::Texture tex_editor2;
	sf::Texture tex_editor3;
	sf::Sprite spri_editor;
};