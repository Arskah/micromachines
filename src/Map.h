#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <fstream>
#include "Block.h"
#include "Config.h"

class Map
{
public:
	//Give editor access to class privates for editing
	friend class Editor;

	//Default constructor that does nothing currently
	Map();

	//Loads map from a image file
	bool loadFromImage(const std::string &filename, const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Create thumbnail of map efficiently and fast
	void createThumbnail(const std::string &filename, const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Get start position by number, player 1 = 0
	sf::Vector2f getStartPosition(const int player_number);

	//Returns block from position x,y
	Block getBlock(const int x, const int y) const;

	//Returns sprite of the Map that is drawable
	sf::Sprite * getDrawable();

private:
	//Create map image after loading from image
	void createImageFromBlockImage(const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Saves map to a image file
	bool saveToImage(const std::string &filename);

	//Map Blocks
	std::vector<Config::BlockType> blockrow;

	//Block image, build blocks after editing from this
	sf::Image block_image;
	//Image of map
	sf::Image image;
	//Image loaded to this texture
	sf::Texture texture;
	//Texture loaded to this sprite
	sf::Sprite drawable;
};
