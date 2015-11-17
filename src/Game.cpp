#include "Game.h"

Game::Game(sf::RenderWindow * window, std::vector<std::pair<const std::string, Config::ObjectType>> playerdata, std::string mapdata)
{
	this->window = window;
	initObjectTextures();
	initBlockTextures();
	initPlayers(playerdata);
	initMap(mapdata);
	initProjectiles();
}

/*
Loading all the object textures from a file into a map.
The textures are paired with the type of the object.
*/
void Game::initObjectTextures()
{
	std::string line;
	std::ifstream texturefile;
	texturefile.open("src/resources/objecttextures.txt", std::ifstream::in);
	if (texturefile.is_open())
	{
		while (std::getline(texturefile, line))
		{
			if (line[0] != '#' && line[0] != '\n')
			{
				std::stringstream stream(line);
				std::string token;
				std::vector<std::string> tokens;
				while (std::getline(stream, token, ' '))
				{
					tokens.push_back(token);
				}
				std::pair<Config::ObjectType, sf::Texture> texturepair;
				texturepair.first = static_cast<Config::ObjectType>(std::stoi(tokens[0]));
				sf::Texture texture;
				texture.loadFromFile(tokens[1]);
				texturepair.second = texture;
				objecttextures.insert(texturepair);
			}
		}
	}
}

/*
Loading all the block textures from a file into a map.
The textures are paired with the type of the block.
*/
void Game::initBlockTextures()
{
	std::string line;
	std::ifstream texturefile;
	texturefile.open("src/resources/blocktextures.txt", std::ifstream::in);
	if (texturefile.is_open())
	{
		while (std::getline(texturefile, line))
		{
			if (line[0] != '#' && line[0] != '\n')
			{
				std::stringstream stream(line);
				std::string token;
				std::vector<std::string> tokens;
				while (std::getline(stream, token, ' '))
				{
					tokens.push_back(token);
				}
				std::pair<Config::BlockType, sf::Texture> texturepair;
				texturepair.first = static_cast<Config::BlockType>(std::stoi(tokens[0]));
				sf::Texture texture;
				texture.loadFromFile(tokens[1]);
				texturepair.second = texture;
				blocktextures.insert(texturepair);
			}
		}
	}
}

/*
Creating a Vehicle object based on the given object type.
The object parameters are read from a file.
The constructed vehicle is pushed to the vehicles vector.
*/
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
					vehicles.emplace_back(&objecttextures.find(type)->second, type, parameters[1], parameters[2], parameters[3], parameters[4]);
					return &vehicles.back();
				}
			}
		}
	}
	return nullptr;
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
	// read map file here and create appropriate Blocks
	// store the blocks into the Map
	return;
}

/*
THE GAME RUNS HERE
*/
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