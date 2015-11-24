#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Config.h"
#include <fstream>
#include <sstream>

/*
This class loads all the needed textures from files when the program starts.
*/
class ResourceManager
{
public:
	/*
	The default constructor.
	*/
	ResourceManager();

	std::map<Config::ObjectType, sf::Texture> * getObjectTextures();
	std::map<Config::BlockType, sf::Image> * getBlockTextures();
	std::map<std::string, sf::SoundBuffer> * getSounds();

private:
	/*
	Loading the Object textures into the objecttextures map.
	Textures are defined by ObjectType in the objecttextures.txt -file.
	*/
	void loadObjectTextures();

	/*
	Loading the Block textures into the blocktextures map.
	Textures are defined by BlockType in the blocktextures.txt -file.
	*/
	void loadBlockTextures();

	void loadSounds();


	std::map<Config::ObjectType, sf::Texture> objecttextures;
	std::map<Config::BlockType, sf::Image> blocktextures;
	std::map<std::string, sf::SoundBuffer> sounds;
};