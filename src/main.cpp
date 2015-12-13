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
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Micro Machines");

	bool menudata;
	bool loading;
	bool start_editor;
	//std::string name = "Playah";
	//std::string name2 = "Kalle";
	//std::pair<const std::string, Config::ObjectType> pair(name, Config::ObjectType::Car1);
	//std::pair<const std::string, Config::ObjectType> pair2(name2, Config::ObjectType::Car2);
	std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> playerdata;			// ((normal playerdata) isHumanPlayer?)
	//playerdata.push_back(pair);
	//playerdata.push_back(pair2);
	std::string mapdata; // = "src/resources/mapsavetest.png";

	ResourceManager resourcemanager;


	/*
	//EXAMPLE HOW EASY IT IS TO START THE EDITOR
	//ESC escapes from editor and doesn't close window
	Editor editor(window, *resourcemanager.getBlockTextures());
	editor.runEditor();
	*/

	sf::Music music;
	music.setLoop(true);
	music.setVolume(30);
	if (music.openFromFile("src/resources/sounds/themesong.wav"))
		music.play();

	Menu menu(window, &resourcemanager);
	menudata = menu.runMenu(window, playerdata, mapdata, music, start_editor);
	if (menudata == false)
	{
		exit(0);
	}
	else if (start_editor == true)
	{
		Editor editor(window, *resourcemanager.getBlockTextures());
		editor.runEditor();
	}
	else
		loading = true;

	//Integers for loading screen
	sf::Sprite sprite;
	sf::Texture tex_1;
	tex_1.loadFromFile("src/resources/menu/loading3.png");
	sprite.setPosition(((float) window.getSize().x / 2 - 50), (float) window.getSize().y / 2);
	//draw loading screen
	sprite.setTexture(tex_1, true);
	window.draw(sprite);
	window.display();

	Game game(window, &resourcemanager, playerdata, mapdata);
	game.run(loading);

	return 0;
}
