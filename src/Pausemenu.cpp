#include "Pausemenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window) : window(window)
{
	window.setView(window.getDefaultView());
	width = window.getSize().x;
	height = window.getSize().y;
}
void PauseMenu::createButtons()
{
	//Background
	backgroundImage.loadFromFile("resources/menu/background.png");

	//font 
	font.loadFromFile("resources/arial.ttf");

	//create continue button
	sf::Texture tex_continue1;
	sf::Texture tex_continue2;
	sf::Texture tex_continue3;

	tex_continue1.loadFromFile("resources/menu/N_continue.png");
	tex_continue2.loadFromFile("resources/menu/O_continue.png");
	tex_continue3.loadFromFile("resources/menu/P_continue.png");
	//float temp_loc_x = (float) width / 2;
	//float temp_loc_y = (float) height / 3 * 2;
	//continue_game.createButton("continue", 1, 0, temp_loc_x, temp_loc_y);
	//continue_game.addState(tex_continue1, tex_continue2, tex_continue3);
	//continue_game.addState(tex_continue1, tex_continue2, tex_continue3);
	//continue_game.setSpriteTexture();
	//buttons.push_back(continue_game);


	//create exit button
	sf::Texture tex_exit1;
	sf::Texture tex_exit2;
	sf::Texture tex_exit3;

	tex_exit1.loadFromFile("resources/menu/N_exit.png");
	tex_exit2.loadFromFile("resources/menu/O_exit.png");
	tex_exit3.loadFromFile("resources/menu/P_exit.png");
	//float temp_loc_x2 = (float) width / 2;
	//float temp_loc_y2 = (float) height / 3 * 3;
	//exit_game.createButton("exit", 2, 0, temp_loc_x2, temp_loc_y2);
	//exit_game.addState(tex_exit1, tex_exit2, tex_exit3);
	//exit_game.addState(tex_exit1, tex_exit2, tex_exit3);
	//exit_game.setSpriteTexture();
	//buttons.push_back(exit_game);

	//load music textures
	tex_music12.loadFromFile("resources/menu/N_music.png");
	tex_music22.loadFromFile("resources/menu/O_music.png");
	tex_music32.loadFromFile("resources/menu/P_music.png");
	tex_music42.loadFromFile("resources/menu/N_muted.png");
	tex_music52.loadFromFile("resources/menu/O_muted.png");
	tex_music62.loadFromFile("resources/menu/P_muted.png");
	spri_music.setTexture(tex_music12);

	//Create continue game button   
	continue_game.state = 0;
	continue_game.max_states = 2;
	continue_game.loc_x = (float)(width / 2 - 50);
	continue_game.loc_y = (float)(height / heightDivider * 3);
	continue_game.textures.push_back(tex_continue1);
	continue_game.textures.push_back(tex_continue2);
	continue_game.textures.push_back(tex_continue3);
	continue_game.textures.push_back(tex_continue1);
	continue_game.textures.push_back(tex_continue2);
	continue_game.textures.push_back(tex_continue3);
	continue_game.spri = spri_exit;
	continue_game.spri.setPosition(continue_game.loc_x, continue_game.loc_y);
	continue_game.spri.setTexture(tex_continue1);
	continue_game.type = buttonType::conti;
	continue_game.player = 50;
	buttons.push_back(continue_game);

	//Create exit game button   
	exit_game.state = 0;
	exit_game.max_states = 2;
	exit_game.loc_x = (float)(width / 2 - 50);
	exit_game.loc_y = (float)(height / heightDivider * 4);
	exit_game.textures.push_back(tex_exit1);
	exit_game.textures.push_back(tex_exit2);
	exit_game.textures.push_back(tex_exit3);
	exit_game.textures.push_back(tex_exit1);
	exit_game.textures.push_back(tex_exit2);
	exit_game.textures.push_back(tex_exit3);
	exit_game.spri = spri_exit;
	exit_game.spri.setPosition(exit_game.loc_x, exit_game.loc_y);
	exit_game.spri.setTexture(tex_exit1);
	exit_game.type = buttonType::exit_pause;
	exit_game.player = 51;
	buttons.push_back(exit_game);

	//create music/muted button
	music.state = 0;
	music.max_states = 2;
	music.loc_x = (float)(width / 2 - 50);
	music.loc_y = (float)(height / heightDivider * 5);
	music.textures.push_back(tex_music12);
	music.textures.push_back(tex_music22);
	music.textures.push_back(tex_music32);
	music.textures.push_back(tex_music42);
	music.textures.push_back(tex_music52);
	music.textures.push_back(tex_music62);
	music.spri = spri_music2;
	music.spri.setPosition(music.loc_x, music.loc_y);
	music.type = buttonType::music;
	music.player = 52;
	buttons.push_back(music);
}
bool PauseMenu::runMenu(sf::RenderWindow& window, sf::Music &music)
{
	PauseMenu::createButtons();
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
				sf::IntRect rect((int)it_button->spri.getPosition().x, (int)it_button->spri.getPosition().y, (int)it_button->spri.getGlobalBounds().width, (int)it_button->spri.getGlobalBounds().height);
				//If mouse is over some button
				if (rect.contains(sf::Mouse::getPosition(window)))
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//all button pressed checked
			for (auto it_button = buttons.begin(); it_button != buttons.end(); it_button++)
			{

				sf::IntRect rect((int)it_button->spri.getPosition().x, (int)it_button->spri.getPosition().y, (int)it_button->spri.getGlobalBounds().width, (int)it_button->spri.getGlobalBounds().height);
				if (rect.contains(sf::Mouse::getPosition(window)))
				{
					it_button->spri.setTexture(it_button->textures.at(it_button->state * 3 + 2), true);
					if (it_button->state == it_button->max_states - 1 && it_button->pressed == 0)
					{
						it_button->state = 0;
						it_button->spri.setTexture(it_button->textures.at(it_button->state * 3 + 2), true);
						it_button->pressed = 1;
					}
					else
					{
						if (it_button->pressed == 0)
						{
							it_button->state++;
							it_button->spri.setTexture(it_button->textures.at(it_button->state * 3 + 2), true);
							it_button->pressed = 1;
						}
					}
					if (it_button->type == buttonType::exit_pause && it_button->state == 1)
					{
						it_button->state = 0;
						return false;
					}
					if (it_button->type == buttonType::conti && it_button->state == 1)
					{
						it_button->state = 0;
						return true;
					}
					if (it_button->type == buttonType::music)
					{
						if (it_button->state == 1)
							music.pause();
						else
							music.play();
					}

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
	text.setPosition((float) width / 2 - 75, (float) height / 3 * 1);
	window.draw(text);

	//here is the problem

	//Iterate all sprites and draw them
	for (auto it_button = buttons.begin(); it_button != buttons.end(); it_button++)
	{

		//this function loses textures for some reason

		//sf::Sprite temp_sprite = it_button->getSprite;
		//temp_sprite.setTexture(it_button->getTexture());
		window.draw(it_button->spri);
	}
	window.display();
}