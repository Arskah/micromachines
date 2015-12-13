#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
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

	std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>> getFinishline() const;

	Config::BlockType getTrackMaterial();

	//Draws map to window
	void drawMap(sf::RenderWindow &window);

private:
	//Create map image after loading from image
	void createImageFromBlockImage(const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Saves map to a image file
	bool saveToImage(const std::string & filename, const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Splits map image to smaller pieces 256 x 256px (same as textures).
	void splitImages(const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Map Blocks
	std::vector<Config::BlockType> blockrow;

	//Base block
	Config::BlockType base_block;

	//Map size
	sf::Vector2u size;

	//Block image, build blocks after editing from this
	sf::Image block_image;
	//Image of map
	sf::Image image;
	//Image loaded to this texture
	sf::Texture texture;
	//Texture loaded to this sprite
	sf::Sprite drawable;

	//Finish line blocks for start and laps
	std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>> finishLine;

	//Map image split into smaller textures
	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> drawables;

	//Background block
	sf::Texture background_texture;
	std::vector<sf::Sprite> background_sprites;
};
