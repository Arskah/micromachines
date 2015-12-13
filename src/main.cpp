#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"
#include "ResourceManager.h"
#include "Editor.h"
#include "Game.h"
#include "Menu.h"
#include <tuple>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Micro Machines");

	bool menudata = false;
	bool start_game = false;
	bool start_editor = false;
	bool game_running = true;

	//create integers for playerdata and mapdata
	std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> playerdata;
	std::string mapdata;

	ResourceManager resourcemanager;


	/*
	//EXAMPLE HOW EASY IT IS TO START THE EDITOR
	//ESC escapes from editor and doesn't close window
	Editor editor(window, *resourcemanager.getBlockTextures());
	editor.runEditor();
	*/

	//Integers for loading screen
	sf::Sprite sprite;
	sf::Texture tex_1;
	tex_1.loadFromFile("resources/menu/loading3.png");
	sprite.setPosition(((float)window.getSize().x / 2 - 50), (float)window.getSize().y / 2);
	sprite.setTexture(tex_1, true);

	//create music 
	sf::Music music;
	music.setLoop(true);
	music.setVolume(30);
	if (music.openFromFile("resources/sounds/themesong.wav"))
	music.play();

	//screenhandler loop
	while (game_running == true) 
	{
		
		Menu menu(window, &resourcemanager);
		menudata = menu.runMenu(window, playerdata, mapdata, music, start_editor);
		if (menudata == false)
		{
			game_running = false;
			exit(0);
		}
		else
			if (start_editor == false)
				start_game = true;
		
		//start editor
		if(start_editor == true)
		{
			//loading screen
			window.draw(sprite);
			window.display();
			//start editor
			Editor editor(window, *resourcemanager.getBlockTextures());
			editor.runEditor();
		}
		//start game
		if (start_game == true)
		{
			//loading screen
			window.draw(sprite);
			window.display();
			//start game 
			Game game(window, &resourcemanager, playerdata, mapdata);
			game.run(music);
			//loading screen
			window.draw(sprite);
			window.display();
			playerdata.clear();
			mapdata.clear();
		}
	}
	return 0;
}
