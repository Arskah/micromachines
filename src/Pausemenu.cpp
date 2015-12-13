#include "Pausemenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window) : window(window)
{
	window.setView(window.getDefaultView());
	width = window.getSize().x;
	height = window.getSize().y;
	PauseMenu::createButtons();
}
void PauseMenu::createButtons()
{
	//Background
	backgroundImage.loadFromFile("src/resources/menu/background.png");

	//font 
	font.loadFromFile("src/resources/arial.ttf");

	//create continue button
	sf::Texture tex_continue1;
	sf::Texture tex_continue2;
	sf::Texture tex_continue3;
	tex_continue1.loadFromFile("src/resources/menu/N_continue.png");
	tex_continue2.loadFromFile("src/resources/menu/O_continue.png");
	tex_continue3.loadFromFile("src/resources/menu/P_continue.png");
	float temp_loc_x = width / 2;
	float temp_loc_y = height / 3 * 2;
	continue_game.createButton("continue", 1, 0, temp_loc_x, temp_loc_y);
	continue_game.addState(tex_continue1, tex_continue2, tex_continue3);
	continue_game.addState(tex_continue1, tex_continue2, tex_continue3);
	continue_game.setSpriteTexture();
	buttons.push_back(continue_game);

	//create exit button
	sf::Texture tex_exit1;
	sf::Texture tex_exit2;
	sf::Texture tex_exit3;
	tex_exit1.loadFromFile("src/resources/menu/N_exit.png");
	tex_exit2.loadFromFile("src/resources/menu/O_exit.png");
	tex_exit3.loadFromFile("src/resources/menu/P_exit.png");
	temp_loc_x = width / 2;
	temp_loc_y = height / 3 * 3;
	exit_game.createButton("exit", 2, 0, temp_loc_x, temp_loc_y);
	exit_game.addState(tex_exit1, tex_exit2, tex_exit3);
	exit_game.addState(tex_exit1, tex_exit2, tex_exit3);
	exit_game.setSpriteTexture();
	buttons.push_back(exit_game);
}
bool PauseMenu::runMenu(sf::RenderWindow& window, sf::Music &music)
{
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (event.type == sf::Event::MouseMoved)
		{
			for (auto it_button = buttons.begin(); it_button != buttons.end(); it_button++)
			{
				sf::IntRect rect((int)it_button->getSprite().getPosition().x, (int)it_button->getSprite().getPosition().y, (int)it_button->getSprite().getGlobalBounds().width, (int)it_button->getSprite().getGlobalBounds().height);
				//If mouse is over some button
				if (rect.contains(sf::Mouse::getPosition(window)))
				{
					it_button->mouseOver();
					break;
				}
				//If mouse is not over any button
				else
				{
					it_button->mouseOut();
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//all button pressed checked
			for (auto it_button = buttons.begin(); it_button != buttons.end(); it_button++)
			{

				sf::IntRect rect((int)it_button->getSprite().getPosition().x, (int)it_button->getSprite().getPosition().y, (int)it_button->getSprite().getGlobalBounds().width, (int)it_button->getSprite().getGlobalBounds().height);
				if (rect.contains(sf::Mouse::getPosition(window)))
				{
					it_button->raiseState();
				}
				if(it_button->getName() == "continue" && it_button->getState() == 1)
				{
					return true;
				}
				if (it_button->getName() == "exit" && it_button->getState() == 1)
				{
					return false;
				}
			}
		}
		PauseMenu::draw(window);
	}

	return false;
}
void PauseMenu::draw(sf::RenderWindow& window)
{


	//clear window not needed?
	window.setView(window.getDefaultView());
	window.clear(sf::Color::Black);
	//declear needed integers
	sf::Text text;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	//draw background 
	background_texture.loadFromImage(this->backgroundImage);
	background_sprite.setTexture(background_texture, true);
	window.draw(background_sprite);

	text.setString("Game paused");
	text.setFont(font);
	text.setColor(sf::Color::Blue);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Regular);
	text.setPosition((float) width / 2, (float) height / 3 * 1);
	window.draw(text);

	//here is the problem

	//Iterate all sprites and draw them
	for (auto it_button = buttons.begin(); it_button != buttons.end(); it_button++)
	{

		//this function loses textures for some reason

		//sf::Sprite temp_sprite = it_button->getSprite;
		//temp_sprite.setTexture(it_button->getTexture());
		window.draw(it_button->getSprite());
	}
	window.display();
}