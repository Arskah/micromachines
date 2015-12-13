#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game(sf::RenderWindow& window, ResourceManager * resourcemanager, std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> playerdata, std::string mapdata) : 
	window(window), resourcemanager(resourcemanager)
{
	initMap(mapdata);
	initPlayers(playerdata);
	initProjectiles();
	this->MaxLaps = 3;
}

void Game::initVehicle(Config::ObjectType type)
{
	std::string line;
	std::ifstream objectfile;
	objectfile.open("resources/objects.txt", std::ifstream::in);
	if (objectfile.is_open())
	{
		while (std::getline(objectfile, line))
		{
			if (line[0] != '#')
			{
				if (static_cast<int>(type) == int(line[0]) - 48)
				{
					std::stringstream stream(line);
					std::string token;
					std::vector<float> parameters;
					while (std::getline(stream, token, ' '))
					{
						parameters.push_back(std::stof(token));
					}
					// The loaded vehicle is added to the vehicles -vector here
					vehicles.emplace_back(&(resourcemanager->getObjectTextures()->find(type)->second), type, parameters[1], parameters[2], parameters[3], parameters[4], createProjectile(type));
				}
			}
		}
	}
}

Projectile Game::createProjectile(Config::ObjectType type)
{
	Config::ObjectType weapontype = Config::VehicleToProjectileMap.find(type)->second;
	std::string line;
	std::ifstream objectfile;
	objectfile.open("resources/objects.txt", std::ifstream::in);
	if (objectfile.is_open())
	{
		while (std::getline(objectfile, line))
		{
			if (line[0] != '#')
			{
				if (static_cast<int>(type) == int(line[0]) - 48)
				{
					std::stringstream stream(line);
					std::string token;
					std::vector<float> parameters;
					while (std::getline(stream, token, ' '))
					{
						parameters.push_back(std::stof(token));
					}
					return Projectile(&(resourcemanager->getObjectTextures()->find(weapontype)->second), parameters[1], weapontype, parameters[2]);
				}
			}
		}
	}
	throw std::runtime_error("Projectile not found from file! Please check game data integrity or reinstall.");
}

void Game::initPlayers(std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> playerdata)
{
	vehicles.clear();
	for (auto it = playerdata.begin(); it != playerdata.end(); it++)
	{
		const std::string name = it->first.first;
		initVehicle(it->first.second);
	}
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		players.emplace_back(playerdata[i].first.first, &vehicles[i], playerdata[i].second);
		//Set to correct starting position on the map
		vehicles[i].setPosition(map.getStartPosition(i));
		//Rotate to face East / Right aka racing direction -- Can be subject to change if wanted
		vehicles[i].setRotation(270);
	}
}

void Game::initProjectiles()
{
	srand((unsigned int) time(NULL));
	int amount = rand() % 10 + 5; //The amount of objects to be generated
	int count = 0; //The counter

	while (count < amount)
	{
		int x = rand() % int(map.getDrawable()->getGlobalBounds().width);
		int y = rand() % int(map.getDrawable()->getGlobalBounds().height);
		if (map.getBlock(x, y).getType() == Config::BlockType::Ground)
		{
			Projectile oilspill = createProjectile(Config::ObjectType::Oilspill);
			oilspill.setPosition((float) x, (float) y);
			oilspill.setScale(1.5f, 1.5f);
			this->projectiles.emplace_back(oilspill);
			count++;
		}
	}
}

void Game::initMap(std::string mapdata)
{
	map.loadFromImage(mapdata, *resourcemanager->getBlockTextures());
}

/*
THE GAME RUNS HERE
*/
void Game::run(sf::Music &music)
{
	//create pausemenu
	PauseMenu pausemenu(window);
	//integer for in menu 
	bool in_pause_menu = true;

	sf::Clock clock;
	sf::Clock gametimer;
	float tickrate = 1.f / 60;
	float dt = 0.f;
	float time = 0.f;

	sf::Font font;
	font.loadFromFile("resources/arial.ttf");
	sf::Text gametime;
	gametime.setFont(font);
	gametime.setStyle(sf::Text::Bold);
	gametime.setScale(0.7f, 0.7f);

	sf::Text lapText;
	lapText.setFont(font);
	lapText.setStyle(sf::Text::Bold);
	lapText.setScale(0.7f, 0.7f);

	// Save human players in a vector for input handling
	std::vector<Player*> humanPlayers;
	for (auto it = players.begin(); it != players.end(); it++)
	{
		if (it->getHuman())
			humanPlayers.push_back( &(*it) );
	}

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
			default:
				break;
			}
		}

		dt = clock.getElapsedTime().asSeconds();

		// Once enough time (always the same) has passed, process the events of the 'tick'
		if (dt >= tickrate)
		{
			clock.restart();
			std::pair<Player *, Config::InputType> pair;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				pair.first = humanPlayers[0];
				pair.second = Config::InputType::Accelerate;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				pair.first = humanPlayers[0];
				pair.second = Config::InputType::TurnLeft;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				pair.first = humanPlayers[0];
				pair.second = Config::InputType::TurnRight;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				pair.first = humanPlayers[0];
				pair.second = Config::InputType::Brake;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				pair.first = humanPlayers[0];
				pair.second = Config::InputType::Shoot;
				userinput.push_back(pair);
			}

			if (humanPlayers.size() > 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					pair.first = humanPlayers[1];
					pair.second = Config::InputType::Accelerate;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					pair.first = humanPlayers[1];
					pair.second = Config::InputType::TurnLeft;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					pair.first = humanPlayers[1];
					pair.second = Config::InputType::TurnRight;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					pair.first = humanPlayers[1];
					pair.second = Config::InputType::Brake;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				{
					pair.first = humanPlayers[1];
					pair.second = Config::InputType::Shoot;
					userinput.push_back(pair);
				}
				if (humanPlayers.size() > 2)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
					{
						pair.first = humanPlayers[2];
						pair.second = Config::InputType::Accelerate;
						userinput.push_back(pair);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
					{
						pair.first = humanPlayers[2];
						pair.second = Config::InputType::TurnLeft;
						userinput.push_back(pair);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
					{
						pair.first = humanPlayers[2];
						pair.second = Config::InputType::TurnRight;
						userinput.push_back(pair);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
					{
						pair.first = humanPlayers[2];
						pair.second = Config::InputType::Brake;
						userinput.push_back(pair);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
					{
						pair.first = humanPlayers[2];
						pair.second = Config::InputType::Shoot;
						userinput.push_back(pair);
					}
					if (humanPlayers.size() > 3)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
						{
							pair.first = humanPlayers[3];
							pair.second = Config::InputType::Accelerate;
							userinput.push_back(pair);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
						{
							pair.first = humanPlayers[3];
							pair.second = Config::InputType::TurnLeft;
							userinput.push_back(pair);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
						{
							pair.first = humanPlayers[3];
							pair.second = Config::InputType::TurnRight;
							userinput.push_back(pair);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
						{
							pair.first = humanPlayers[3];
							pair.second = Config::InputType::Brake;
							userinput.push_back(pair);
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							pair.first = humanPlayers[3];
							pair.second = Config::InputType::Shoot;
							userinput.push_back(pair);
						}
					}
				}
			}

			/* Empty input for AI. AI input calculated in Engine */
			for (auto it = players.begin(); it != players.end(); it++)
			{
				if (!it->getHuman())
				{
					pair.first = &(*it);
					pair.second = Config::InputType::None;
					userinput.push_back(pair);
				}
			}

			// Draw lap count
			int lapCount = 0;
			for (auto it : players)
			{

				if (lapCount < it.getVehicle()->getLaps())
					lapCount = it.getVehicle()->getLaps();
				if (lapCount == MaxLaps)
				{
					window.setView(window.getDefaultView());

					sf::Text winner;
					std::string name = it.getName() + " won!";
					winner.setFont(font);
					winner.setString(name);
					winner.setCharacterSize(50);
					winner.setStyle(sf::Text::Bold);
					winner.setPosition(float(window.getSize().x/2 - winner.getGlobalBounds().width / 2), float(window.getSize().y / 4));

					sf::Text exit;
					exit.setFont(font);
					exit.setString("Press escape to return to menu.\n        Thank you for playing!");
					exit.setCharacterSize(40);
					exit.setPosition(float(window.getSize().x / 2 - exit.getGlobalBounds().width / 2), float(window.getSize().y / 2));

					resourcemanager->playSound("win");
					while (window.isOpen())
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							return;
						}
						window.clear();
						window.draw(winner);
						window.draw(exit);
						window.display();
					}
				}
			}

			std::string lap = "LAPS:" + std::to_string(lapCount+1) + "/" + std::to_string(MaxLaps);
			lapText.setString(lap);

			std::string time = std::to_string(round(gametimer.getElapsedTime().asSeconds() * 100) / 100);
			gametime.setString(time.substr(0, time.size()-4));


			//go to pause menu if Esc is pressed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				in_pause_menu = pausemenu.runMenu(window, music);
				if (in_pause_menu == false)
					return;
				else
				{
					// The engine draws the game state here
					Engine::update(window, resourcemanager, &vehicles, &projectiles, map, userinput, dt, gametime, lapText, &humanPlayers);
					userinput.clear();
				}
			}
			else
			{
				// The engine draws the game state here
				Engine::update(window, resourcemanager, &vehicles, &projectiles, map, userinput, dt, gametime, lapText, &humanPlayers);
				userinput.clear();
			}
			
		}
	}
}