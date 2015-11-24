#include "Game.h"


Game::Game(sf::RenderWindow& window, ResourceManager * resourcemanager, std::vector<std::pair<const std::string, Config::ObjectType>> playerdata, std::string mapdata) : 
	window(window), resourcemanager(resourcemanager)
{
	initPlayers(playerdata);
	initMap(mapdata);
	initProjectiles();
}

Vehicle * Game::initVehicle(Config::ObjectType type)
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
					return &vehicles.back();
				}
			}
		}
	}
	return nullptr;
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
	for (auto it = playerdata.begin(); it != playerdata.end(); it++)
	{
		const std::string name = it->first;
		Vehicle * vehicle = initVehicle(it->second);
		// The new player is added to the players -vector here
		players.emplace_back(name, vehicle);
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
void Game::run()
{
	sf::Clock clock;
	float tickrate = 1.f / 60;
	float dt = 0.f;

	/*
	sf::Music music;
	music.setLoop(true);
	music.setVolume(50);
	if (music.openFromFile("src/resources/sounds/themesong.wav"))
		music.play();
	*/

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players.front();
				pair.second = Config::InputType::Accelerate;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players.front();
				pair.second = Config::InputType::TurnLeft;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players.front();
				pair.second = Config::InputType::TurnRight;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players.front();
				pair.second = Config::InputType::Brake;
				userinput.push_back(pair);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				std::pair<Player *, Config::InputType> pair;
				pair.first = &players.front();
				pair.second = Config::InputType::Shoot;
				userinput.push_back(pair);
			}
			
			// The engine draws the game state here
			Engine::update(window, resourcemanager, &vehicles, &projectiles, map, userinput, dt);
			userinput.clear();
			clock.restart();
		}
	}
}