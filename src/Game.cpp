#include "Game.h"


Game::Game(sf::RenderWindow& window, ResourceManager * resourcemanager, std::vector<std::pair<const std::string, Config::ObjectType>> playerdata, std::string mapdata) : 
	window(window), resourcemanager(resourcemanager)
{
	initMap(mapdata);
	initPlayers(playerdata);
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

void Game::initPlayers(std::vector<std::pair<const std::string, Config::ObjectType>> playerdata)
{
	vehicles.clear();
	for (auto it = playerdata.begin(); it != playerdata.end(); it++)
	{
		const std::string name = it->first;
		initVehicle(it->second);
	}
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		players.emplace_back(playerdata[i].first, &vehicles[i]);
		//Set to correct starting position on the map
		vehicles[i].setPosition(map.getStartPosition(i));
		//Rotate to face East / Right aka racing direction -- Can be subject to change if wanted
		vehicles[i].setRotation(270);
	}
}

void Game::initProjectiles()
{
	srand(time(NULL));
	int amount = rand() % 20 + 5; //The amount of objects to be generated
	int count = 0; //The counter

	while (count < amount)
	{
		int x = rand() % int(map.getDrawable()->getGlobalBounds().width);
		int y = rand() % int(map.getDrawable()->getGlobalBounds().height);
		if (map.getBlock(x, y).getType() == Config::BlockType::Ground)
		{
			Projectile oilspill = createProjectile(Config::ObjectType::Oilspill);
			oilspill.setPosition(x, y);
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players[0];
				pair.second = Config::InputType::Accelerate;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players[0];
				pair.second = Config::InputType::TurnLeft;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players[0];
				pair.second = Config::InputType::TurnRight;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players[0];
				pair.second = Config::InputType::Brake;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players[0];
				pair.second = Config::InputType::Shoot;
				userinput.push_back(pair);
			}

			if (players.size() > 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					std::pair<Player *, Config::InputType> pair;
					pair.first = &players[1];
					pair.second = Config::InputType::Accelerate;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					std::pair<Player *, Config::InputType> pair;
					pair.first = &players[1];
					pair.second = Config::InputType::TurnLeft;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					std::pair<Player *, Config::InputType> pair;
					pair.first = &players[1];
					pair.second = Config::InputType::TurnRight;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					std::pair<Player *, Config::InputType> pair;
					pair.first = &players[1];
					pair.second = Config::InputType::Brake;
					userinput.push_back(pair);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				{
					std::pair<Player *, Config::InputType> pair;
					pair.first = &players[1];
					pair.second = Config::InputType::Shoot;
					userinput.push_back(pair);
				}
			}

			std::string time = std::to_string(round(gametimer.getElapsedTime().asSeconds() * 100) / 100);
			gametime.setString(time.substr(0, time.size()-4));

			//Exit the loading creen
			loading = false;
			// The engine draws the game state here
			Engine::update(window, resourcemanager, &vehicles, &projectiles, map, userinput, dt, gametime);
			userinput.clear();
		}
	}
}