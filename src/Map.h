#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Block.h"

class Map
{
public:
	//Give editor access to class privates
	friend class Editor;

	//Default constructor that does nothing currently
	Map();
	
	//Loads map from .txt file
	void loadFromFile(const std::string &filename, const std::map<Config::BlockType, sf::Image> &blocktextures);

	//Returns block from position x,y
	Block getBlock(const std::size_t x, const std::size_t y) const;

	//Returns sprite of the Map that is drawable
	sf::Sprite * getDrawable();

private:
	//Creates a Drawable picture from the Map --- DEPRECATED DO NOT USE --- SAVED FOR REFERENCE
	void createDrawable(const std::map<Config::BlockType, sf::Image> &blocktextures);
	//Updates a Drawwable picture from the Map --- DEPRECATED DO NOT USE --- SAVED FOR REFERENCE
	void updateDrawable(const std::map<Config::BlockType, sf::Image>& blocktextures, const sf::Vector2u location, const Config::BlockType type, const int brush_size);

	//Create a Image from the Map
	void createImage(const std::map<Config::BlockType, sf::Image> &blocktextures);
	//Box brush function to update Map Image
	void updateImageBox(const std::map<Config::BlockType, sf::Image>& blocktextures, const sf::Vector2u location, const Config::BlockType type, const int brush_size);
	//Circle brush function to update Map Image
	void updateImageCircle(const std::map<Config::BlockType, sf::Image>& blocktextures, const sf::Vector2u location, const Config::BlockType type, const int brush_size);
	//Load new image after updating
	void loadNewImage();

	std::vector<std::vector<Block>> blocks;
	//RENDER --- PART OF DEPRECATED
	sf::RenderTexture render;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite drawable;
};
