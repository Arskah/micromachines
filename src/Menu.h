#pragma once
#include <SFML/Graphics.hpp>

struct button {
	int state;
	int max_states;
	int loc_y;
	int loc_x;
	sf::Sprite spri;
	std::vector<sf::Texture> textures;
};


class Menu
{
public:
	Menu(sf::RenderWindow& window);
	~Menu() {}

	void loadContent();
	void createButtons();

	bool runMenu(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);


	int getAmountItems() const;
	sf::Text getSelected() const;

	sf::RenderWindow window;
	int width;
	int height;
private:
	int amount_players;
	
	sf::Image* backgroundImage;

	std::vector<struct button> buttons;

	// declare all button images
	// numerators
	sf::Texture tex_num1;
	sf::Sprite spri_num1;

	sf::Texture tex_num2;
	sf::Sprite spri_num2;

	sf::Texture tex_num3;
	sf::Sprite spri_num3;

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
