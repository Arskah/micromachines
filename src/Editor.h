#pragma once

#include "SFML/Graphics.hpp"
#include "Map.h"
#include "Config.h"
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

class Editor
{
public:
	Editor(sf::RenderWindow & window, const std::map<Config::BlockType, sf::Image> &blocktextures);

	void runEditor();

private:
	enum class BoxTypes
	{
		Text,
		Number,
		Alphanumeric,
		Display
	};

	//Run when creating new map
	void initMap();
	//Run when starting editor
	void initEditor();
	//Open a new window with a small textbox for user textinput
	std::string openTextbox(const std::string &box_name, const BoxTypes box_type = BoxTypes::Alphanumeric, const std::string &text_to_display = "");
	//Create a UI element from given list of images and build it into ui_image
	void createBlockUI(const std::vector<const sf::Image *> images, sf::Image * ui_image);
	//Create red selection rectangle for blockUI
	void createBlockUISelection(sf::Image * const selected_image, const int num, const int maxnum);
	//Create File Toolbar
	void createFileUI(sf::Image * file_ui_image);
	//Creates a red border to be shown in minimap if off-center
	sf::VertexArray createMinimapViewBorder();
	//Places finish line to the Map, currently hardcoded to be at map center
	void placeFinishLine();
	//Box brush function to update Map Image
	void updateImageBox(const sf::Vector2i location, const Config::BlockType type, const int brush_size);
	//Circle brush function to update Map Image
	void updateImageCircle(sf::Vector2i location, const Config::BlockType type, const int brush_size);

	//Reference to window given in ctor
	sf::RenderWindow & window;
	//Load resolution of monitor here
	sf::Vector2i resolution;
	//The actual map
	Map map;
	//Textures from ResourceManager
	const std::map<Config::BlockType, sf::Image> * blocktextures;
	//Brush size
	int brush_size;
	//Allocate blocktextures to this in larger size for faster mask operations
	std::vector<sf::Image> block_textures_enlarged;
	//Circle brush masks
	std::vector<sf::Image> circle_brush_masks;
	//Max brush size
	const int max_brush_size;
	//Editorial view
	sf::View editor_view;
	//Minimap view
	sf::View minimap_view;
};
