#include "Game.h"


Game::Game(sf::RenderWindow& window, ResourceManager * resourcemanager, std::vector<std::pair<std::pair<const std::string, Config::ObjectType>, bool>> playerdata, std::string mapdata) : 
	window(window), resourcemanager(resourcemanager)
{
	initPlayers(playerdata);
	initMap(mapdata);
	initProjectiles();
}

void Game::initVehicle(Config::ObjectType type)
{
	std::string line;
	std::ifstream objectfile;
	objectfile.open("src/resources/objects.txt", std::ifstream::in);
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
	objectfile.open("src/resources/objects.txt", std::ifstream::in);
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
					return Projectile(&(resourcemanager->getObjectTextures()->find(weapontype)->second), sf::Vector2f(0.f, 0.f), parameters[1], weapontype, parameters[2]);
				}
			}
		}
	}
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
	}
}

void Game::initProjectiles()
{
	// generate objects randomly here
	return;
}

void Game::initMap(std::string mapdata)
{
	map.loadFromImage(mapdata, *resourcemanager->getBlockTextures());
}

/*
THE GAME RUNS HERE
*/
void Game::run(bool &loading)
{
	sf::Clock clock;
	sf::Clock gametimer;
	float tickrate = 1.f / 60;
	float dt = 0.f;
	float time = 0.f;

	sf::Font font;
	font.loadFromFile("Arial.ttf");
	sf::Text gametime;
	gametime.setFont(font);
	gametime.setStyle(sf::Text::Bold);
	gametime.setScale(0.7f, 0.7f);

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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

			std::string time = std::to_string(round(gametimer.getElapsedTime().asSeconds() * 100) / 100);
			gametime.setString(time.substr(0, time.size()-4));

			//Exit the loading creen
			loading = false;
			// The engine draws the game state here
			Engine::update(window, resourcemanager, &vehicles, &projectiles, map, userinput, dt, gametime, &humanPlayers);
			userinput.clear();
		}
	}
}