#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadObjectTextures();
	loadBlockTextures();
}

void ResourceManager::loadObjectTextures()
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

void ResourceManager::loadBlockTextures()
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
				std::pair<Config::BlockType, sf::Image> texturepair;
				texturepair.first = static_cast<Config::BlockType>(std::stoi(tokens[0]));
				sf::Image texture;
				texture.loadFromFile(tokens[1]);
				texturepair.second = texture;
				blocktextures.insert(texturepair);
			}
		}
	}
}

std::map<Config::ObjectType, sf::Texture> * ResourceManager::getObjectTextures()
{
	return &objecttextures;
}

std::map<Config::BlockType, sf::Image> * ResourceManager::getBlockTextures()
{
	return &blocktextures;
}