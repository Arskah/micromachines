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

	std::pair<std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>>, bool> getFinishline() const;

	Config::BlockType getTrackMaterial();

	//Returns vector of pointers to Blocks that are on leftside of track
	//std::vector<std::pair<std::size_t, std::size_t>> getLeftsideBlocks();

private:
	//Create map image after loading from image
	void createImageFromBlockImage(const std::map<Config::BlockType, sf::Image>& blocktextures);

	//Saves map to a image file
	bool saveToImage(const std::string &filename);

	//Generates leftsideTrack vector
	void createLeftsideTrack();
	/* Functions that look for the next track block on left side of track. StartU for when start is up and StartR for right */
	//std::pair<std::size_t, std::size_t> checkNextLeftBlockStartU(std::pair<std::size_t, std::size_t> coordinates);
	//std::pair<std::size_t, std::size_t> checkNextLeftBlockStartR(std::pair<std::size_t, std::size_t> coordinates);

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

	//Finish line blocks for start and laps
	std::pair<std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>>, bool> finishLine;		// Pair of Pair of 2 coordinate pairs and starting direction :P. True for up, false for right

	// Blocks on the left side of the track. Used for standings and AI
	//std::vector<std::pair<std::size_t, std::size_t>> leftsideTrack;
	Config::BlockType TrackMaterial;
};
