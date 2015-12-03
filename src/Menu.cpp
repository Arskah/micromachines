#include "Menu.h"


/* BASE CLASS MAIN MENU*/
Menu::Menu(sf::RenderWindow& window) : window(window)
{
	//if (!font.loadFromFile("arial.ttf"))
	//{
	//	// handle error
	//}
	width = window.getSize().x;
	height = window.getSize().y;
	this->draw(window);
	this->runMenu(window);

}
void Menu::loadContent() {
	// create num1
	tex_num1.loadFromFile("resources\\num1.png");
	spri_num1.setTexture(tex_num1);
	// create num2
	tex_num2.loadFromFile("resources\\num2.png");
	spri_num1.setTexture(tex_num2);
	// create num3
	tex_num3.loadFromFile("resources\\num3.png");
	spri_num1.setTexture(tex_num3);
	// create num4
	tex_num4.loadFromFile("resources\\num4.png");
	spri_num1.setTexture(tex_num4);

	//load player/AI/off content
	tex_player_N.loadFromFile("resources\\N_player.png");
	tex_player_O.loadFromFile("resources\\O_player.png");
	tex_player_P.loadFromFile("resources\\P_player.png");

	tex_ai_N.loadFromFile("resources\\N_ai.png");
	tex_ai_O.loadFromFile("resources\\O_ai.png");
	tex_ai_P.loadFromFile("resources\\P_ai.png");

	tex_off_N.loadFromFile("resources\\N_off.png");
	tex_off_O.loadFromFile("resources\\O_off.png");
	tex_off_P.loadFromFile("resources\\P_off.png");

	spri_player.setTexture(tex_player_N);

	//load start/exit content
	tex_start_N.loadFromFile("resources\\N_start.png");
	tex_start_O.loadFromFile("resources\\O_start.png");
	tex_start_P.loadFromFile("resources\\P_start.png");
	spri_start.setTexture(tex_start_N);

	tex_exit_N.loadFromFile("resources\\N_exit.png");
	tex_exit_O.loadFromFile("resources\\O_exit.png");
	tex_exit_P.loadFromFile("resources\\P_exit.png");
	spri_exit.setTexture(tex_exit_N);

	//Load cars for develot use
	tex_map1.loadFromFile("resources\\map1.png");
	spri_map1.setTexture(tex_map1);
}

void Menu::createButtons(){
	// create player option menus
	//std::map<Config::ObjectType, sf::Texture> tex_cars = *resourcemanager->getObjectTextures();
	for (int i = 0; i < amount_players; i++) {
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
		plaioff.spri = spri_player;
		plaioff.player = i;

		buttons.push_back(plaioff);

		button cars;
		cars.state = 0;
		cars.loc_x = offset_x;
		cars.loc_y = offset_y + 100;
		cars.player = i;


		//for finding all cars from ogjectTExturemap *****TODO****
		for (unsigned int j = 0; j < resourcemanager.getObjectTextures()->size(); j++) {
			std::string type = "Car" + std::to_string(j);
			//std::map<Config::ObjectType, sf::Texture>::iterator
			auto it_cars = resourcemanager.getObjectTextures->find(type);
			if (it_cars != resourcemanager.getObjectTextures->end) {
				cars.textures.push_back(it_cars->second);
				cars.max_states++;
			}
		}
		buttons.push_back(cars);


		/*for (auto it = tex_cars.begin; it != tex_cars.end; it++) {
			if (it->first == Config::ObjectType::Car) {
				cars.textures.push_back(it->second);
				cars.max_states++;
			}
		}*/
	}




}


bool Menu::runMenu(sf::RenderWindow& window)
{
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
			mouse_loc = sf::Mouse::getPosition(window);
			for (auto it_button : buttons) {
				if (it_button.spri.getLocalBounds == mouse_loc){
					it_button.spri.setTexture(it_button.textures[it_button.state * 2 + 1], true);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//tähän kaikki sprite tarkistukset
			mouse_loc = sf::Mouse::getPosition(window);
			for (auto it_button : buttons) {
				if (it_button.spri.getLocalBounds == mouse_loc) {
					it_button.spri.setTexture(it_button.textures[it_button.state * 2 + 2], true);
					if (it_button.state == it_button.max_states)
						it_button.state = 0;
					else
						it_button.state++;
				}
			}
		}
		//Mitäs jos nappulasta pääsetetään irti? TODO
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//{
		//	//tähän kaikki sprite tarkistukset
		//	mouse_loc = sf::Mouse::getPosition(window);
		//	for (auto it_button : buttons) {
		//		if (it_button.spri.getLocalBounds == mouse_loc) {
		//			it_button.spri.setTexture(it_button.textures[it_button.state * 2 + 2], true);
		//			if (it_button.state == it_button.max_states)
		//				it_button.state = 0;
		//			else
		//				it_button.state++;
		//		}
		//	}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//lopeta peli
			return false; 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			// aloita peli
			return true;
		}
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(this->backgroundImage);
	int y_place = 1;
	for (auto item : this->items)
	{
		item.first.setFont(font);
		item.first.setColor(sf::Color::White);
		item.first.setString(item.second);
		item.first.setPosition(sf::Vector2f(width / 2, height / (this->getAmountItems) * y_place));
		window.draw(item.first);
		y_place++;
	}
	window.display();


int Menu::getAmountItems() const
{
	return this->items.size();
}
sf::Text Menu::getSelected() const
{
	return this->items.at(selectedItem).first;
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