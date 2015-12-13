#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	loadObjectTextures();
	loadBlockTextures();
	loadSoundBuffers();
}

void ResourceManager::loadObjectTextures()
{
	std::string line;
	std::ifstream texturefile;
	texturefile.open("resources/objecttextures.txt", std::ifstream::in);
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
	texturefile.open("resources/blocktextures.txt", std::ifstream::in);
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

void ResourceManager::loadSoundBuffers()
{
	std::string line;
	std::ifstream soundfile;
	soundfile.open("resources/sounds.txt", std::ifstream::in);
	if (soundfile.is_open())
	{
		while (std::getline(soundfile, line))
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
				soundbuffers[tokens[0]].loadFromFile(tokens[1]);
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

void ResourceManager::playSound(std::string name)
{
	if (sounds.size() == 0)
	{
		sounds.push_back(sf::Sound());
		sounds[0].setBuffer(soundbuffers[name]);
		sounds[0].setVolume(50);
		sounds[0].play();
	}
	else
	{
		int index = -1;
		for (size_t i = 0; i < sounds.size(); i++)
		{
			if (sounds[i].getStatus() != sf::Sound::Playing && index == -1)
			{
				index = i;
			}
		}

		if (index != -1)
		{
			sounds[index].setBuffer(soundbuffers[name]);
			sounds[index].setVolume(50);
			sounds[index].play();
		}
		else
		{
			sounds.push_back(sf::Sound());
			sounds[sounds.size() - 1].setBuffer(soundbuffers[name]);
			sounds[sounds.size() - 1].setVolume(50);
			sounds[sounds.size() - 1].play();
		}
	}

}