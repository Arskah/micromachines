#include "Menu.h"
/* BASE CLASS FOR ALL MENUS*/
Menu::Menu(sf::RenderWindow& window) : window(window)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}
	width = window.getSize().x;
	height = window.getSize().y;
	this->draw(window);
	this->eventLoop(window);
}

void Menu::eventLoop(sf::RenderWindow& window)
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			this->select();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		//TODO Mouse over selection
		{
			this->moveDown();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		//TODO Mouse over selection
		{
			this->moveUp();
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

void Menu::moveUp()
{
	if (this->selectedItem > 0)
	{
		this->getSelected().setColor(sf::Color::White);
		this->selectedItem--;
		this->getSelected().setColor(sf::Color::Red);
	}
}
void Menu::moveDown()
{
	if (this->selectedItem < this->getAmountItems())
	{
		this->getSelected().setColor(sf::Color::White);
		this->selectedItem++;
		this->getSelected().setColor(sf::Color::Red);
	}
}

int Menu::getAmountItems() const
{
	return this->items.size();
}
sf::Text Menu::getSelected() const
{
	return this->items.at(selectedItem).first;
}

/* END OF BASE CLASS*/

/* MAIN MENU*/
void MainMenu::select()
{
	switch (selectedItem)		// TODO: from up to down, these will call functions that do things in menus. Like if MainMenu top selection is 'Single Player', case 0 will call Single Player Menu. Enum good here??
	{
	case 0:		// Want to play Single player
		SinglePlayerMenu::SinglePlayerMenu(this->window);
		break;
	case 1:		// Want to play multiplayer
		MultiplayerMenu::MultiPlayerMenu(this->window);
		break;
	case 2:		// Open settings
		SettingsMenu::SettingsMenu(this->window);
		break;
	case 3:		//EXIT GAME
		window.close();
		break;
	}
}

/* SETTINGS MENU*/
void SettingsMenu::select()
{
	switch (selectedItem)
	{
	case 0:
		break;
	}
}

/* SINGLEPLAYER MENU*/
void SinglePlayerMenu::select()
{
	switch (selectedItem)
	{
	case 0:		// Start game
		break;	// TODO: car changing; # of AI etc. settings. Maybe need to tweak base class items to take other objects than text as well
	}
}

/* MULTIPLAYER MENU*/
void MultiPlayerMenu::select()
{
	switch (selectedItem)
	{
	case 0:		// Start game
		break;
	}
}

/* PAUSE MENU*/
void PauseMenu::select()
{
	switch (selectedItem)
	{
	case 0:		// Continue
		break;
	}
}