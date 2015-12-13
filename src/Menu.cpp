#include <SFML/Graphics/Rect.hpp>

#include "Menu.h"
#include <stdlib.h>


/* BASE CLASS MAIN MENU*/
Menu::Menu(sf::RenderWindow& window, ResourceManager* resourcemanager) : window(window), resourcemanager(resourcemanager)
{
	// Get window size
	width = window.getSize().x;
	height = window.getSize().y;
}
void Menu::loadContent() {
	//Background
	backgroundImage.loadFromFile("src/resources/menu/background.png");

	// create num1
	tex_num1.loadFromFile("src/resources/menu/num1.png");
	spri_num1.setTexture(tex_num1);
	// create num2
	tex_num2.loadFromFile("src/resources/menu/num2.png");
	spri_num2.setTexture(tex_num2);
	// create num3
	tex_num3.loadFromFile("src/resources/menu/num3.png");
	spri_num3.setTexture(tex_num3);
	// create num4
	tex_num4.loadFromFile("src/resources/menu/num4.png");
	spri_num4.setTexture(tex_num4);
        
	//load player/AI/off content
	tex_player_N.loadFromFile("src/resources/menu/N_player.png");
	tex_player_O.loadFromFile("src/resources/menu/O_player.png");
	tex_player_P.loadFromFile("src/resources/menu/P_player.png");

	tex_ai_N.loadFromFile("src/resources/menu/N_ai.png");
	tex_ai_O.loadFromFile("src/resources/menu/O_ai.png");
	tex_ai_P.loadFromFile("src/resources/menu/P_ai.png");

	tex_off_N.loadFromFile("src/resources/menu/N_off.png");
	tex_off_O.loadFromFile("src/resources/menu/O_off.png");
	tex_off_P.loadFromFile("src/resources/menu/P_off.png");

	spri_player.setTexture(tex_player_N);

	//load start
	tex_start_N.loadFromFile("src/resources/menu/N_start.png");
	tex_start_O.loadFromFile("src/resources/menu/O_start.png");
	tex_start_P.loadFromFile("src/resources/menu/P_start.png");

	spri_start.setTexture(tex_start_N);

	//load exit 
	tex_exit_N.loadFromFile("src/resources/menu/N_quit.png");
	tex_exit_O.loadFromFile("src/resources/menu/O_quit.png");
	tex_exit_P.loadFromFile("src/resources/menu/P_quit.png");

	spri_exit.setTexture(tex_exit_N);

	//load map textures
	Map mapperino;
	mapperino.createThumbnail("src/resources/map1.png");
	tex_map1 = *mapperino.getDrawable()->getTexture();
	mapperino.createThumbnail("src/resources/map2.png");
	tex_map2 = *mapperino.getDrawable()->getTexture();
	spri_map1.setTexture(tex_map1);
       
	//Load car textures
	tex_car1.loadFromFile("src/resources/car1.png");
	tex_car2.loadFromFile("src/resources/car2.png");
	tex_car3.loadFromFile("src/resources/car3.png");
	tex_car4.loadFromFile("src/resources/car4.png");
	spri_car.setTexture(tex_car1);

	//load music textures
	tex_music1.loadFromFile("src/resources/menu/N_music.png");
	tex_music2.loadFromFile("src/resources/menu/O_music.png");
	tex_music3.loadFromFile("src/resources/menu/P_music.png");
	tex_music4.loadFromFile("src/resources/menu/N_muted.png");
	tex_music5.loadFromFile("src/resources/menu/O_muted.png");
	tex_music6.loadFromFile("src/resources/menu/P_muted.png");
	spri_music.setTexture(tex_music1);

	//load editor textures
	tex_editor1.loadFromFile("src/resources/menu/N_editor.png");
	tex_editor2.loadFromFile("src/resources/menu/O_editor.png");
	tex_editor3.loadFromFile("src/resources/menu/P_editor.png");
	spri_editor.setTexture(tex_editor1);

    //font 
    font.loadFromFile("src/resources/arial.ttf");
}

void Menu::createButtons()
{
	// create player option menus
	//std::map<Config::ObjectType, sf::Texture> tex_cars = *resourcemanager->getObjectTextures();
	for (int i = 0; i < amount_players; i++) 
        {
			// create Pleyer/AI/Off button for all players
			button plaioff;
			//choose 2 player to be player, 2 to be AI
			if (i < 2)
				plaioff.state = 0;
			else
				plaioff.state = 1;
			plaioff.max_states = 3;
			plaioff.loc_x = (float) (width / 2 - 100);
			plaioff.loc_y = (float) (height / heightDivider * (i+2));
			plaioff.textures.push_back(tex_player_N);
			plaioff.textures.push_back(tex_player_O);
			plaioff.textures.push_back(tex_player_P);
			plaioff.textures.push_back(tex_ai_N);
			plaioff.textures.push_back(tex_ai_O);
			plaioff.textures.push_back(tex_ai_P);
			plaioff.textures.push_back(tex_off_N);
			plaioff.textures.push_back(tex_off_O);
			plaioff.textures.push_back(tex_off_P);
			plaioff.type = buttonType::pao;
			plaioff.spri = spri_player;
			plaioff.spri.setPosition(plaioff.loc_x, plaioff.loc_y);
			plaioff.player = i+1;
			buttons.push_back(plaioff);

			// create car button for all players
			button cars;
			cars.state = i;
			cars.max_states = 4;
			cars.loc_x = (float) (width / 2);
			cars.loc_y = (float) (height / heightDivider * (i+2));
			cars.player = i+1;
			cars.spri = spri_car;
			cars.spri.setPosition(cars.loc_x, cars.loc_y);
			cars.spri.setScale(0.14f, 0.14f);
			cars.type = buttonType::car;	
			//Now static over ride version
			cars.textures.push_back(tex_car1);
			cars.textures.push_back(tex_car1);
			cars.textures.push_back(tex_car1);
			cars.textures.push_back(tex_car2);
			cars.textures.push_back(tex_car2);
			cars.textures.push_back(tex_car2);
			cars.textures.push_back(tex_car3);
			cars.textures.push_back(tex_car3);
			cars.textures.push_back(tex_car3);
			cars.textures.push_back(tex_car4);
			cars.textures.push_back(tex_car4);
			cars.textures.push_back(tex_car4);
		
			//for finding all cars from ogjectTexturemap        
			//for future use
	//		for(unsigned int j = 0; j < resourcemanager->getObjectTextures()->size(); j++) {
	//			std::string type = "Car" + std::to_string(j);
	//                        auto it_cars = resourcemanager->getObjectTextures(); //std::map<Config::ObjectType, sf::Texture>::iterator
	//			it_cars = resourcemanager->getObjectTextures()->find(type);
	//			if(it_cars != resourcemanager->getObjectTextures()->end(){
	//				cars.textures.push_back(it_cars->second);
	//				cars.max_states++;
	//			}
	//      }
        

			buttons.push_back(cars);

	}
		
	//Create Map button
	map.state = 0;
	map.max_states = 2;
	map.loc_x = (float) (width / 2 - 40);
	map.loc_y = (float) (height / heightDivider * 1 - 10);
	map.textures.push_back(tex_map1);
	map.textures.push_back(tex_map1);
	map.textures.push_back(tex_map1);
	map.textures.push_back(tex_map2);
	map.textures.push_back(tex_map2);
	map.textures.push_back(tex_map2);

	map.spri = spri_map1;
	map.spri.setPosition(map.loc_x, map.loc_y);
	//map.spri.setScale(0.1, 0.1);
	map.type = buttonType::map;
	map.player = 97;
	buttons.push_back(map);

    //Create start game button
    start.state = 0;
	start.max_states = 2;
	start.loc_x = (float) (width / 2 + 75);
	start.loc_y = (float) (height / heightDivider * 6);
	start.textures.push_back(tex_start_N);
    start.textures.push_back(tex_start_O);
    start.textures.push_back(tex_start_P);
	start.textures.push_back(tex_start_N);
	start.textures.push_back(tex_start_O);
	start.textures.push_back(tex_start_P);
    start.spri = spri_start;
    start.spri.setPosition(start.loc_x,start.loc_y);
    start.type = buttonType::start;
	start.player = 98;
	buttons.push_back(start);
        
    //Create exit game button   
    exit.state = 0;
	exit.max_states = 2;
	exit.loc_x = (float) (width / 2 - 225);
	exit.loc_y = (float) (height / heightDivider * 6);
	exit.textures.push_back(tex_exit_N);
    exit.textures.push_back(tex_exit_O);
    exit.textures.push_back(tex_exit_P);
	exit.textures.push_back(tex_exit_N);
	exit.textures.push_back(tex_exit_O);
	exit.textures.push_back(tex_exit_P);
    exit.spri = spri_exit;
    exit.spri.setPosition(exit.loc_x,exit.loc_y);
    exit.type = buttonType::exit; 
	exit.player = 99;
	buttons.push_back(exit);

	//create music/muted button
	music.state = 0;
	music.max_states = 2;
	music.loc_x = (float) (width / 2 - 50);
	music.loc_y = (float) (height / heightDivider * 6);
	music.textures.push_back(tex_music1);
	music.textures.push_back(tex_music2);
	music.textures.push_back(tex_music3);
	music.textures.push_back(tex_music4);
	music.textures.push_back(tex_music5);
	music.textures.push_back(tex_music6);
	music.spri = spri_music;
	music.spri.setPosition(music.loc_x, music.loc_y);
	music.type = buttonType::music;
	music.player = 96;
	buttons.push_back(music);  

	//create editor button
	editor.state = 0;
	editor.max_states = 2;
	editor.loc_x = (float)(width / 2 - 500);
	editor.loc_y = (float)(height / heightDivider * 1);
	editor.textures.push_back(tex_editor1);
	editor.textures.push_back(tex_editor2);
	editor.textures.push_back(tex_editor3);
	editor.textures.push_back(tex_editor1);
	editor.textures.push_back(tex_editor2);
	editor.textures.push_back(tex_editor3);
	editor.spri = spri_editor;
	editor.spri.setPosition(editor.loc_x, editor.loc_y);
	editor.type = buttonType::editor;
	editor.player = 95;
	buttons.push_back(editor);
}

std::string Menu::checkName(button &it_button)
{
	std::string name; 
	switch (it_button.state)
	{
	case 0:
		switch (it_button.player)
		{
		case 1:
			name = "Akke";
			return name;
		case 2:
			name = "Okko";
			return name;
		case 3:
			name = "Aarni";
			return name;
		case 4:
			name = "Jan";
			return name;
		}
	case 1:
		switch (it_button.player)
		{
		case 1:
			name = "AI1";
			return name;
		case 2:
			name = "AI2";
			return name;
		case 3:
			name = "AI3";
			return name;
		case 4:
			name = "AI4";
			return name;
		}
	case 2:
		name = "Off";
		return name;
	}
	name = "Failed_load_name";
	return name;
}

std::string Menu::checkMap(button it_button) {
	std::string mapTemp;
	if (it_button.state == 0)
		mapTemp = "src/resources/map1.png";
	if (it_button.state == 1)
		mapTemp = "src/resources/map2.png";
	return mapTemp;
}


bool Menu::runMenu(sf::RenderWindow& window, std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> &playerdata, std::string &mapdata, sf::Music &music, bool& start_editor)
{   
    Menu::loadContent();
    Menu::createButtons();
	/*
	sf::Music music;
	music.setLoop(true);
	music.setVolume(30);
	if (music.openFromFile("src/resources/sounds/themesong.wav"))
		music.play();
	*/
    while (window.isOpen())
    {
        sf::Vector2i mouse_loc = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        if(event.type == sf::Event::MouseMoved)
        {
			for (auto it_button = buttons.begin(); it_button != buttons.end(); it_button++)
            {
                sf::IntRect rect((int) it_button->spri.getPosition().x, (int) it_button->spri.getPosition().y, (int) it_button->spri.getGlobalBounds().width, (int) it_button->spri.getGlobalBounds().height);
				//If mouse is over some button
				if(rect.contains(sf::Mouse::getPosition(window)))
				{
					it_button->spri.setTexture(it_button->textures.at(it_button->state * 3 + 1), true);
					break;
                }
				//If mouse is not over any button
				else
				{
					it_button->spri.setTexture(it_button->textures.at(it_button->state * 3), true);
				}
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            //all button pressed checked
			for (auto it_button2 = buttons.begin(); it_button2 != buttons.end(); it_button2++)
            {

                sf::IntRect rect((int) it_button2->spri.getPosition().x, (int) it_button2->spri.getPosition().y, (int) it_button2->spri.getGlobalBounds().width, (int) it_button2->spri.getGlobalBounds().height);
				if(rect.contains(sf::Mouse::getPosition(window)))
                {
					it_button2->spri.setTexture(it_button2->textures.at(it_button2->state * 3 + 2), true);
                    if(it_button2->state == it_button2->max_states-1 && it_button2->pressed == 0)
                    {
                        it_button2->state = 0;
						it_button2->spri.setTexture(it_button2->textures.at(it_button2->state * 3 + 2), true);
						it_button2->pressed = 1;
                    }
                    else
                    {
						if (it_button2->pressed == 0)
						{
							it_button2->state++;
							it_button2->spri.setTexture(it_button2->textures.at(it_button2->state * 3 + 2), true);
							it_button2->pressed = 1;
						}
                    }

					if (it_button2->type == buttonType::exit && it_button2->state == 1)
					{
						//end game
						return false;
					}
					if (it_button2->type == buttonType::editor && it_button2->state == 1)
					{
						start_editor = true;
						return true;
					}
					if(it_button2->type == buttonType::start && it_button2->state == 1)
					{
						// reset start button
						it_button2->state = 0;
						// start game
						std::string name;
						for (auto it_button3 = buttons.begin(); it_button3 != buttons.end(); it_button3++)
						{
							if (it_button3->type == buttonType::pao)
							{
								name = checkName(*it_button3);
							}
							if (it_button3->type == buttonType::car)
							{
								if (it_button3->state == 0)
								{
									if (name == "Off") {
										continue;
									}
									else
									{
										bool human = true;
										if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
											human = false;
										std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car1);
										std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
										playerdata.push_back(player1);
										continue;
									}
								}
								if (it_button3->state == 1)
								{
									if (name == "Off") {
										continue;
									}
									else
									{
										bool human = true;
										if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
											human = false;
										std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car2);
										std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
										playerdata.push_back(player1);
										continue;
									}
								}
								if (it_button3->state == 2)
								{
									if (name == "Off") {
										continue;
									}
									else
									{
										bool human = true;
										if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
											human = false;
										std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car3);
										std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
										playerdata.push_back(player1);
										continue;
									}
								}
								if (it_button3->state == 3)
								{
									if (name == "Off") {
										continue;
									}
									else
									{
										bool human = true;
										if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
											human = false;
										std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car4);
										std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
										playerdata.push_back(player1);
										continue;
									}
								}
							}
							if (it_button3->type == buttonType::map)
							{
								mapdata = checkMap(*it_button3);
							}
						}
						return true;
					}
					if(it_button2->type == buttonType::music)
					{
						if (it_button2->state == 1)
							music.pause();
						else
							music.play();
					}
					break;
                }
            }
        }
		if (event.type == sf::Event::MouseButtonReleased)
		{
			for (auto it_button3 = buttons.begin(); it_button3 != buttons.end(); it_button3++)
			{
				if (it_button3->pressed == 1) 
				{
					it_button3->pressed = 0;
					it_button3->spri.setTexture(it_button3->textures.at(it_button3->state * 3 + 1), true);
				}

			}
		}
        
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
                //end game
				return false;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {

            // start game
            std::string name;
			for (auto it_button4 = buttons.begin(); it_button4 != buttons.end(); it_button4++)
            {
				if(it_button4->type == buttonType::pao)
                {
					name = checkName(*it_button4);
                }
                if(it_button4->type == buttonType::car)
                {
                    if (it_button4->state == 0)
                    {
						if (name == "Off") {
							continue;
						}
						else
						{
							bool human = true;
							if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
								human = false;
							std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car1);
							std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
							playerdata.push_back(player1);
							continue;
						}
					}
					if (it_button4->state == 1)
					{
						if (name == "Off") {
							continue;
						}
						else
						{
							bool human = true;
							if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
								human = false;
							std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car2);
							std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
							playerdata.push_back(player1);
							continue;
						}
					}
					if (it_button4->state == 2)
					{
						if (name == "Off") {
							continue;
						}
						else
						{
							bool human = true;
							if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
								human = false;
							std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car3);
							std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
							playerdata.push_back(player1);
							continue;
						}
					}
					if (it_button4->state == 3)
					{
						if (name == "Off") {
							continue;
						}
						else
						{
							bool human = true;
							if (name == "AI1" || name == "AI2" || name == "AI3" || name == "AI4")
								human = false;
							std::pair<const std::string, Config::ObjectType> data(name, Config::ObjectType::Car4);
							std::pair<std::pair<const std::string, Config::ObjectType>, bool> player1(data, human);
							playerdata.push_back(player1);
							continue;
						}
					}
               }
				if (it_button4->type == buttonType::map)
				{
					mapdata = checkMap(*it_button4);
				}
            }
            return true;
        }

		Menu::draw(window);
    }
	return false;
}
void Menu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	sf::Text text;
	// Can't draw image, need to attch it to a texture of sf::drawable
	sf::Texture texture;
	texture.loadFromImage(this->backgroundImage);
	sf::Sprite sprite;
	sprite.setTexture(texture, true);
	window.draw(sprite);

	int y_place = 1;

	spri_num1.setPosition((float) (width / 2 - 200), (float) (height / heightDivider * 2));
	spri_num2.setPosition((float) (width / 2 - 200), (float) (height / heightDivider * 3));
	spri_num3.setPosition((float) (width / 2 - 200), (float) (height / heightDivider * 4));
	spri_num4.setPosition((float) (width / 2 - 200), (float) (height / heightDivider * 5));
	window.draw(spri_num1);
	window.draw(spri_num2);
	window.draw(spri_num3);
	window.draw(spri_num4);


	for (auto it_but = buttons.begin(); it_but != buttons.end(); it_but++)
	{
		it_but->spri.setPosition(it_but->loc_x, it_but->loc_y);
		window.draw(it_but->spri);

		if (it_but->type == buttonType::pao)
		{
			text.setString(checkName(*it_but));
			text.setFont(font);
			text.setColor(sf::Color::Blue);
			text.setCharacterSize(30);
			text.setStyle(sf::Text::Regular);
			text.setPosition(it_but->loc_x + 200, it_but->loc_y);
			window.draw(text);
		}
	}

	window.draw(start.spri);
	window.draw(exit.spri);

	window.display();


}