#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include "Block.h"

class Map
{
public:
	//Give editor access to class privates for editing
	friend class Editor;

	//Default constructor that does nothing currently
	Map();

	//Loads map from a image file
	bool loadFromImage(const std::string &filename, const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Returns block from position x,y
	Block getBlock(const std::size_t x, const std::size_t y) const;

	//Returns sprite of the Map that is drawable
	sf::Sprite * getDrawable();

private:
	//Secondary constructor, meant for Editor
	Map(const std::map<Config::BlockType, sf::Image>& block_resources);

	//Creates a new image with base blocks
	void createImageFromBase(const std::map<Config::BlockType, sf::Image> &blocktextures, const sf::Vector2u size, const Config::BlockType base_type);
	//Create map image after loading from image
	void createImageFromBlockImage(const std::map<Config::BlockType, sf::Image>& blocktextures);
	//Box brush function to update Map Image
	void updateImageBox(const sf::Vector2i location, const Config::BlockType type, const int brush_size);
	//Circle brush function to update Map Image
	void updateImageCircle(sf::Vector2i location, const Config::BlockType type, const int brush_size);
	//Load new image after updating
	void updateDrawable();

	//Saves map to a image file
	bool saveToImage(const std::string &filename);

	//Map Blocks
	std::vector<std::vector<Block>> blocks;

	//Circle brush masks
	std::vector<sf::Image> circle_brush_masks;

	//TEMPORARY own block_textures with 2x size than normals for brush masks to work properly.
	//Will be removed with higher resolution textures
	std::vector<sf::Image> block_textures;

	//Block image, build blocks after editing from this
	sf::Image block_image;
	//Image of map
	sf::Image image;
	//Image loaded to this texture
	sf::Texture texture;
	//Texture loaded to this sprite
	sf::Sprite drawable;

	//Determine later dynamically
	//Max brush size
	const int max_brush_size = 49;
};
