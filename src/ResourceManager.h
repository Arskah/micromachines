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

	// Returns a pointer to the objecttextures map
	std::map<Config::ObjectType, sf::Texture> * getObjectTextures();
	// Returns a pointer to the blocktextures map
	std::map<Config::BlockType, sf::Image> * getBlockTextures();
	// Finds a sound corresponding to the name and plays it. For example: resourcemanager.playSound('collision')
	void playSound(std::string name);

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

	/*
	Loading the sound files into the soundbuffers map.
	The sound file filepaths are defined in the sounds.txt -file.
	*/
	void loadSoundBuffers();

	// Map containing the object textures connected to their respective ObjectTypes.
	std::map<Config::ObjectType, sf::Texture> objecttextures;
	// Map containing the block textures connected to their respective BlockTypes.
	std::map<Config::BlockType, sf::Image> blocktextures;
	// Sound files loaded into soundbuffers. The key is a string that can be found in the sounds.txt
	std::map<std::string, sf::SoundBuffer> soundbuffers;
	// Active sound objects.
	std::vector<sf::Sound> sounds;
};