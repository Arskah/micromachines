#include "Game.h"

Game::Game(sf::RenderWindow *window, std::vector<std::pair<std::string, int>> playerdata, std::string mapdata)
{
	this->window = window;
	initPlayers(playerdata);
	initMap(mapdata);
	initObjects();
}

void Game::run()
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			}
		}
	}
}

void Game::initPlayers(std::vector<std::pair<std::string, int>> playerdata)
{
	for (auto it = playerdata.begin(); it != playerdata.end(); it++)
	{
		Player player = Player(it->first, it->second);
		players.push_back(player);
	}
}

void Game::initObjects()
{
	// generate objects randomly here
	return;
}

void Game::initMap(std::string mapdata)
{
	// read map file here and create appropriate Blocks
	// store the blocks into the Map
	return;
}