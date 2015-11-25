#pragma once

#include <SFML/Graphics.hpp>
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


	std::map<Config::ObjectType, sf::Texture> objecttextures;
	std::map<Config::BlockType, sf::Image> blocktextures;
};