#include <SFML/Graphics/Rect.hpp>

#include "Menu.h"
#include <stdlib.h>


/* BASE CLASS MAIN MENU*/
Menu::Menu(sf::RenderWindow& window, ResourceManager* resourcemanager) : window(window), resourcemanager(resourcemanager)
{
	//if (!font.loadFromFile("arial.ttf"))
	//{
	//	// handle error
	//}
	width = window.getSize().x;
	height = window.getSize().y;
//	this->draw(window);
//	this->runMenu(window);

}
void Menu::loadContent() {
	//Background
	backgroundImage.loadFromFile("src/resources/menu/background.png");

	// create num1
	tex_num1.loadFromFile("src/resources/menu/num1.png");
	spri_num1.setTexture(tex_num1);
	// create num2
	tex_num2.loadFromFile("src/resources/menu/num2.png");
	spri_num1.setTexture(tex_num2);
	// create num3
	tex_num3.loadFromFile("src/resources/menu/num3.png");
	spri_num1.setTexture(tex_num3);
	// create num4
	tex_num4.loadFromFile("src/resources/menu/num4.png");
	spri_num1.setTexture(tex_num4);
        
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

	//load start/exit content
	tex_start_N.loadFromFile("src/resources/menu/N_start.png");
	tex_start_O.loadFromFile("src/resources/menu/O_start.png");
	tex_start_P.loadFromFile("src/resources/menu/P_start.png");
	spri_start.setTexture(tex_start_N);

	tex_exit_N.loadFromFile("src/resources/menu/N_exit.png");
	tex_exit_O.loadFromFile("src/resources/menu/O_exit.png");
	tex_exit_P.loadFromFile("src/resources/menu/P_exit.png");
	spri_exit.setTexture(tex_exit_N);

	//Load maps for develop use
        //tex_map1.loadFromFile("src/resources/menu/map1.png");
	//spri_map1.setTexture(tex_map1);
        
        //font 
        font.loadFromFile("src/resources/arial.ttf");
}

void Menu::createButtons(){
	// create player option menus
	//std::map<Config::ObjectType, sf::Texture> tex_cars = *resourcemanager->getObjectTextures();
	for (int i = 0; i < amount_players; i++) 
        {
		button plaioff;
		plaioff.state = 0;
		plaioff.max_states = 3;
		plaioff.loc_x = offset_x;
		plaioff.loc_y = offset_y;
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

		button cars;
		cars.state = 0;
		cars.loc_x = offset_x;
		cars.loc_y = offset_y + 100;
		cars.player = i;
                cars.spri = spri_car;
                cars.spri.setPosition(cars.loc_x, cars.loc_y);

		//for finding all cars from ogjectTexturemap
                //Now static over ride version
                cars.textures.push_back(resourcemanager->getObjectTextures()->find(Config::ObjectType::Car1)->second);
                cars.textures.push_back(resourcemanager->getObjectTextures()->find(Config::ObjectType::Car1)->second);
                
                //for future use
//		for(unsigned int j = 0; j < resourcemanager->getObjectTextures()->size(); j++) {
//			std::string type = "Car" + std::to_string(j);
//                        auto it_cars = resourcemanager->getObjectTextures(); //std::map<Config::ObjectType, sf::Texture>::iterator
//			it_cars = resourcemanager->getObjectTextures()->find(type);
//			if(it_cars != resourcemanager->getObjectTextures()->end(){
//				cars.textures.push_back(it_cars->second);
//				cars.max_states++;
//			}
//                }
                
                cars.spri.setTexture(cars.textures[1]);
		buttons.push_back(cars);

		offset_x = offset_x + i*100;
	}

        
        
        start.state = 0;
	start.max_states = 2;
	start.loc_x = offset_x;
	start.loc_y = offset_y + 100;
	start.textures.push_back(tex_start_N);
        start.textures.push_back(tex_start_O);
        start.textures.push_back(tex_start_P);
        start.spri = spri_start;
        start.spri.setPosition(start.loc_x,start.loc_y);
        start.type = buttonType::start;
	start.player = 98;
        
       
        exit.state = 0;
		exit.max_states = 2;
		exit.loc_x = offset_x;
		exit.loc_y = offset_y + 200;
		exit.textures.push_back(tex_start_N);
        exit.textures.push_back(tex_start_O);
        exit.textures.push_back(tex_start_P);
        exit.spri = spri_exit;
        exit.spri.setPosition(exit.loc_x,exit.loc_y);
        exit.type = buttonType::exit; 
		exit.player = 99;
        

}


bool Menu::runMenu(sf::RenderWindow& window, std::vector<std::pair<const std::string, Config::ObjectType>> &playerdata, std::string &mapdata)
{   
    Menu::loadContent();
    Menu::createButtons();

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
            //mouse_loc = sf::Mouse::getPosition(window);
            for(auto it_button : buttons) 
            {
                sf::IntRect rect(it_button.spri.getPosition().x, it_button.spri.getPosition().y, it_button.spri.getGlobalBounds().width, it_button.spri.getGlobalBounds().height);	
                if(rect.contains(sf::Mouse::getPosition()))
                {
                    it_button.spri.setTexture(it_button.textures[it_button.state * 2 + 1], true);
                }
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            //all button pressed checked
            //mouse_loc = sf::Mouse::getPosition(window);
            for(auto it_button : buttons) 
            {
                sf::IntRect rect(it_button.spri.getPosition().x, it_button.spri.getPosition().y, it_button.spri.getGlobalBounds().width, it_button.spri.getGlobalBounds().height);
                if(rect.contains(sf::Mouse::getPosition()))
                {
                    it_button.spri.setTexture(it_button.textures[it_button.state * 2 + 2], true);
                    if(it_button.state == it_button.max_states)
                    {
                        it_button.state = 0;
                        it_button.spri.setTexture(it_button.textures[it_button.state * 2 + 2], true);
                    }
                    else
                    {
                        it_button.state++;
                        it_button.spri.setTexture(it_button.textures[it_button.state * 2 + 2], true);
                    }
                }
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
                //end game
                window.close();
				return false;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || start.state == 1)
        {
            // start game
            std::string name;
            for(auto it_button : buttons)
            {
                if(it_button.type == buttonType::pao)
                {
                    switch(it_button.state)
                    {
                        case 0:
                            switch (it_button.player)
                            {
                                case 1:
                                name = "Akke";
                                continue;
                                case 2:
                                name = "Okko";
                                continue;
                                case 3:
                                name = "Aarni";
                                continue;
                                case 4:
                                name = "Jan";
                                continue;
                            }
                        case 1:
                            switch (it_button.player)
                            {
                            case 1:
                                name = "AI1";
                                continue;
                            case 2:
                                name = "AI2";
                                continue;
                            case 3:
                                name = "AI3";
                                continue;
                            case 4:
                                name = "AI4";
                                continue;
                            }
                        case 2:
                            name = "Off";
                            continue;
                    }
                }
                if(it_button.type == buttonType::car)
                {
                    if (it_button.state == 0)
                    {
                        std::pair<const std::string, Config::ObjectType> player1(name, Config::ObjectType::Car1);
                        playerdata.push_back(player1);
                        continue;
                    }
                    if (it_button.state == 1)
                    {
                        std::pair<const std::string, Config::ObjectType> player2(name, Config::ObjectType::Car2);
                        playerdata.push_back(player2);
                        continue;
                    }
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
        
    // Can't draw image, need to attch it to a texture of sf::drawable
    sf::Texture texture;
    texture.loadFromImage(this->backgroundImage);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    window.draw(sprite);

    int y_place = 1;

    spri_num1.setPosition(offset_x, offset_y);
    spri_num2.setPosition(offset_x, offset_y + 100);
    spri_num3.setPosition(offset_x, offset_y + 200);
    spri_num4.setPosition(offset_x, offset_y + 300);
    window.draw(spri_num1);
    window.draw(spri_num2);
    window.draw(spri_num3);
    window.draw(spri_num4);


    for(auto it_but : buttons)
    {
        it_but.spri.setPosition(it_but.loc_x, it_but.loc_y);
        window.draw(it_but.spri);

//          item.first.setFont(font);
//          item.first.setColor(sf::Color::White);
//          item.first.setString(item.second);
//          item.first setPosition;
//          window.draw(item.first);
//          y_place++;
    }

    start.spri.setPosition(start.loc_x, start.loc_y);
    window.draw(start.spri);
    exit.spri.setPosition(exit.loc_x, exit.loc_y);
    window.draw(exit.spri);

    window.display();


//int Menu::getAmountItems() const
//{
//	return this->items.size();
//}
//sf::Text Menu::getSelected() const
//{
//	return this->items.at(selectedItem).first;
}

/* END OF MENU CLASS*/







// Not in use - Jan G.
///* SETTINGS MENU*/
//void SettingsMenu::select()
//{
//	switch (selectedItem)
//	{
//	case 0:
//		break;
//	}
//}
//
///* SINGLEPLAYER MENU*/
//void SinglePlayerMenu::select()
//{
//	switch (selectedItem)
//	{
//	case 0:		// Start game
//		break;	// TODO: car changing; # of AI etc. settings. Maybe need to tweak base class items to take other objects than text as well
//	}
//}
//
///* MULTIPLAYER MENU*/
//void MultiPlayerMenu::select()
//{
//	switch (selectedItem)
//	{
//	case 0:		// Start game
//		break;
//	}
//}
//
///* PAUSE MENU*/
//void PauseMenu::select()
//{
//	switch (selectedItem)
//	{
//	case 0:		// Continue
//		break;
//	}
//}