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
}

void Menu::createButtons(){
	// create player option menus
	for (int i = 0; i < amount_players; i++) {
		button plaioff;
		plaioff.state = 0;
		plaioff.max_states = 3;
		plaioff.loc_x = 100;
		plaioff.loc_y = 100;
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

		button cars;
		cars.max_states = 

	}




}


bool Menu::runMenu(sf::RenderWindow& window)
{
	while (window.isOpen())
	{

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
			if(sf::Mouse::getPosition == )
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//tähän kaikki sprite tarkistukset
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
}


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