#include "Map.h"

Map::Map()
{
}

Map::Map(const std::map<Config::BlockType, sf::Image>& block_resources)
{
	//Build blocks to edit map from
	for (std::size_t i = 0; i < block_resources.size(); i++)
	{
		const sf::Image * block_to_copy_from = &block_resources.find(static_cast<Config::BlockType>(i))->second;
		const sf::Vector2u size = block_to_copy_from->getSize();

		sf::Image temp;
		temp.create(size.x * 2, size.y * 2);
		temp.copy(*block_to_copy_from, 0, 0, sf::IntRect(0, 0, size.x, size.y));
		temp.copy(*block_to_copy_from, 0, size.y, sf::IntRect(0, 0, size.x, size.y));
		temp.copy(*block_to_copy_from, size.x, size.y, sf::IntRect(0, 0, size.x, size.y));
		temp.copy(*block_to_copy_from, size.x, 0, sf::IntRect(0, 0, size.x, size.y));
		
		block_textures.push_back(temp);
	}

	//Build circle brush masks
	for (int i = 1; i < max_brush_size + 1; i++)
	{
		sf::Image circle_mask;

		circle_mask.create(50, 50, sf::Color::Black);
		//circle_mask.create(50, 50, sf::Color(253, 253, 253, 253));

		for (int x = 0; x < i; x++)
		{
			for (int y = 0; y < i; y++)
			{
				if (std::sqrt(std::pow((i - 1) / 2 - x, 2) + std::pow((i - 1) / 2 - y, 2)) > ((i - 1) / 2))
				{
					circle_mask.setPixel(x, y, sf::Color::Red);
					//circle_mask.setPixel(x, y, sf::Color(254, 254, 254, 254));
				}
			}
		}

		circle_mask.createMaskFromColor(sf::Color::Black);
		//circle_mask.createMaskFromColor(sf::Color(253, 253, 253, 253));

		circle_brush_masks.push_back(circle_mask);
	}
}


void Map::loadFromFile(const std::string &filename, const std::map<Config::BlockType, sf::Image> &blocktextures)
{
	int size_x = 0;
	int size_y = 0;
	int current_x = 0;
	int current_y = 0;

	std::vector<Block> row;

	std::string line;
	std::ifstream objectfile;
	objectfile.open(filename, std::ifstream::in);
	if (objectfile.is_open())
	{
		while (std::getline(objectfile, line))
		{
			if (line[0] == '!')
			{
				std::stringstream stream(line);
				std::string token;
				std::vector<int> parameters;

				//Discard '!'
				std::getline(stream, token, ' ');
				while (std::getline(stream, token, ' '))
				{
					parameters.push_back(std::stoi(token));
				}

				size_x = parameters[0];
				size_y = parameters[1];
			}
			else if (line[0] != '#')
			{
				std::stringstream stream(line);
				std::string token;
				std::vector<float> parameters;
				while (std::getline(stream, token, ' '))
				{
					parameters.push_back(std::stof(token));
				}
				
				//Push current block to row
				if (current_y < size_y)
				{
					row.push_back(Block(static_cast<Config::BlockType>(int(parameters[0])), parameters[1]));
					//Move to next
					++current_y;
				}
				//If row full, empty it
				if (current_x < size_x && current_y == size_y)
				{
					//Add column
					blocks.push_back(row);

					//Move to next
					row.clear();
					current_y = 0;
					++current_x;
				}
			}
		}
	}

	//Create image
	createImage(blocktextures);
}

bool Map::saveToImage(const std::string & filename)
{
	return block_image.saveToFile(filename);
}

static Block buildBlock(const int type_int)
{
	return Block(static_cast<Config::BlockType>(type_int), Config::BlockToFrictionMap.find(static_cast<Config::BlockType>(type_int))->second);
}

bool Map::loadFromImage(const std::string & filename, const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Load image
	if (!block_image.loadFromFile(filename))
		return false;

	//Clear old
	blocks.clear();
	//Fill with empty ones first
	blocks.assign(block_image.getSize().x, std::vector<Block>(block_image.getSize().y, Block(Config::BlockType::None, Config::BlockToFrictionMap.find(Config::BlockType::None)->second)));
	
	/*
	//Raw pointer to block types, will need a conversion
	const sf::Uint8 * block_info = block_image.getPixelsPtr();
	//Right starting position to start reading from (pixel is 4x sf::Uint8)
	block_info += 2;

	//Pointer to block type information
	sf::Uint32 * ptr_u = (sf::Uint32 *)block_info;
	//Get type values from pixels
	std::vector<sf::Uint8> type_values(ptr_u, (ptr_u + block_image.getSize().x * block_image.getSize().y));
	*/

	sf::Uint8 * block_info = (sf::Uint8 *)block_image.getPixelsPtr();
	block_info += 2;
	std::vector<sf::Uint8> type_values(block_info, (block_info + block_image.getSize().x * block_image.getSize().y));

	//Count how many of certain blocks in a row
	std::vector<std::pair<Config::BlockType, int>> block_counts;
	std::size_t current = type_values[0];
	std::size_t count = 0;
	for (std::size_t i = 0; i < type_values.size(); i++, count++)
	{
		if (current != type_values[i])
		{
			block_counts.push_back(std::make_pair(static_cast<Config::BlockType>(current), count));

			current = type_values[i];
			count = 0;
		}
	}
	block_counts.push_back(std::make_pair(static_cast<Config::BlockType>(current), count));

	//Build a vector of blocks
	std::vector<Block> blockrow;
	for (std::size_t i = 0; i < block_counts.size(); i++)
	{
		blockrow.insert(blockrow.end(), std::size_t(block_counts[i].second), Block(block_counts[i].first, Config::BlockToFrictionMap.find(block_counts[i].first)->second));
	}

	//Insert built vector into class vector of blocks
	for (std::size_t i = 0; i < block_image.getSize().x; i++)
	{
		sf::Vector2u size = block_image.getSize();
		blocks[i].assign(blockrow.begin() + block_image.getSize().y * i, blockrow.begin() + block_image.getSize().y * (i + 1));
	}
	
	/*
	//Set blocks from image -- VERSION 1 -- DEPRECATED
	for (std::size_t x = 0; x < block_image.getSize().x; x++)
	{
		for (std::size_t y = 0; y < block_image.getSize().y; y++)
		{
			//blocks[x][y].type = static_cast<Config::BlockType>(*block_info);
			//blocks[x][y].friction = Config::BlockToFrictionMap.find(static_cast<Config::BlockType>(*block_info))->second;
			//Load next position to be ready
			//block_info += 4;

			blocks[x][y].type = static_cast<Config::BlockType>(static_cast<unsigned int>(block_image.getPixel(x, y).toInteger() >> 8));
			blocks[x][y].friction = Config::BlockToFrictionMap.find(static_cast<Config::BlockType>(static_cast<unsigned int>(block_image.getPixel(x, y).toInteger() >> 8)))->second;
		}
	}
	*/

	//Create new drawable image
	createImageFromBlockImage(blocktextures);

	//Went successfully
	return true;
}

Block Map::getBlock(const std::size_t x, const std::size_t y) const
{
	if (x < blocks.size() && y < blocks.at(x).size())
		return blocks[x][y];
	else
		return Block(Config::BlockType::None, Config::BlockToFrictionMap.find(Config::BlockType::None)->second);
}

sf::Sprite * Map::getDrawable()
{
	return &(drawable);
}

void Map::createImage(const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Create image to correct size
	image.create(blocks.size(), blocks[0].size(), sf::Color::Red);

	//Loop over positions and copy pixel-by-pixel the image
	for (std::size_t x = 0; x < blocks.size(); x++)
	{
		for (std::size_t y = 0; y < blocks[0].size(); y++)
		{
			image.copy(blocktextures.find(blocks[x][y].getType())->second, x, y, sf::IntRect(x % 50, y % 50, 1, 1));
		}
	}

	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTexture(texture);
}

void Map::createImage2(const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Create image to correct size
	image.create(blocks.size(), blocks[0].size(), sf::Color::Red);

	//Loop over positions and copy pixel-by-pixel the image
	for (std::size_t x = 0; x < blocks.size(); x++)
	{
		for (std::size_t y = 0; y < blocks[0].size(); y++)
		{
			image.copy(blocktextures.find(blocks[x][y].getType())->second, x, y, sf::IntRect(x % 50, y % 50, 1, 1));
		}
	}

	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTexture(texture);

	//Do the same to block_image
	block_image.create(blocks.size(), blocks[0].size());

	//Loop over positions and copy pixel-by-pixel the image
	for (std::size_t x = 0; x < blocks.size(); x++)
	{
		for (std::size_t y = 0; y < blocks[0].size(); y++)
		{
			block_image.setPixel(x, y, sf::Color((static_cast<std::uint32_t>(blocks[x][y].getType()) << 8) + 255));
		}
	}
}

void Map::createNewImage(const std::map<Config::BlockType, sf::Image>& blocktextures, const sf::Vector2u size, const Config::BlockType base_block_type)
{
	//Insert base blocks to fill map
	blocks.assign(size.x, std::vector<Block>(size.y, Block(base_block_type, Config::BlockToFrictionMap.find(base_block_type)->second)));

	//Create image to correct size
	image.create(blocks.size(), blocks[0].size(), sf::Color::Red);

	//Loop over positions and copy image
	sf::Vector2u block_texture_size = blocktextures.find(base_block_type)->second.getSize();
	for (std::size_t x = 0; x < image.getSize().x; x += block_texture_size.x)
	{
		for (std::size_t y = 0; y < image.getSize().y; y += block_texture_size.y)
		{
			image.copy(blocktextures.find(base_block_type)->second, x, y, sf::IntRect(0, 0,
				(x + block_texture_size.x < image.getSize().x) ? (block_texture_size.x) : (x % block_texture_size.x),
				(y + block_texture_size.y < image.getSize().y) ? (block_texture_size.y) : (y % block_texture_size.y)));
		}
	}

	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTextureRect(sf::IntRect(0, 0, image.getSize().x, image.getSize().y));
	drawable.setTexture(texture);

	//Do the same to block_image
	block_image.create(blocks.size(), blocks[0].size(), sf::Color((static_cast<std::uint32_t>(base_block_type) << 8) + 255));
}

void Map::createImageFromBlockImage(const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Empty old image
	image.create(block_image.getSize().x, block_image.getSize().y);
	//Copy new one
	//Loop over positions and copy pixel-by-pixel the image
	for (std::size_t x = 0; x < blocks.size(); x++)
	{
		for (std::size_t y = 0; y < blocks[0].size(); y++)
		{
			image.copy(blocktextures.find(static_cast<Config::BlockType>(block_image.getPixel(x, y).toInteger() >> 8))->second, x, y, sf::IntRect(x % 50, y % 50, 1, 1));
		}
	}

	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTextureRect(sf::IntRect(0, 0, image.getSize().x, image.getSize().y));
	drawable.setTexture(texture);
}

void Map::updateImageBox(const std::map<Config::BlockType, sf::Image>& blocktextures, const sf::Vector2u location, const Config::BlockType type, const int brush_size)
{
	//Image of block type to draw
	const sf::Image * temp_image = &(blocktextures.find(type)->second);
	
	//Box brush
	//Loop over brush size
	for (int x = 0; x < brush_size; x++)
	{
		for (int y = 0; y < brush_size; y++)
		{
			//Check that we are in bounds of the image
			if (((location.x + x - (brush_size - 1) / 2) >= 0 && (location.x + x - (brush_size - 1) / 2) < image.getSize().x)
				&& ((location.y + y - (brush_size - 1) / 2) >= 0 && (location.y + y - (brush_size - 1) / 2) < image.getSize().y))
			{
				//Check if given pixel is already of desired type to avoid unnecessary processing
				if (blocks[x + location.x - (brush_size - 1) / 2][y + location.y - (brush_size - 1) / 2].getType() == type)
					continue;

				//Change pixel to desired color
				image.setPixel(x + location.x - (brush_size - 1) / 2, y + location.y - (brush_size - 1) / 2,
					temp_image->getPixel((location.x + x - (brush_size - 1) / 2) % temp_image->getSize().x, (location.y + y - (brush_size - 1) / 2) % temp_image->getSize().y));

				//Also change block
				blocks[x + location.x - (brush_size - 1) / 2][y + location.y - (brush_size - 1) / 2].type = type;
				blocks[x + location.x - (brush_size - 1) / 2][y + location.y - (brush_size - 1) / 2].friction = Config::BlockToFrictionMap.find(type)->second;
			}
		}
	}
}

void Map::updateImageCircle(const std::map<Config::BlockType, sf::Image>& blocktextures, const sf::Vector2u location, const Config::BlockType type, const int brush_size)
{
	//Image of block type to draw
	const sf::Image * temp_image = &(blocktextures.find(type)->second);

	//Circle brush
	//Loop over brush size
	for (int x = 0; x < brush_size; x++)
	{
		for (int y = 0; y < brush_size; y++)
		{
			//Check that we are in bounds of the image
			if (((location.x + x - (brush_size - 1) / 2) >= 0 && (location.x + x - (brush_size - 1) / 2) < image.getSize().x)
				&& ((location.y + y - (brush_size - 1) / 2) >= 0 && (location.y + y - (brush_size - 1) / 2) < image.getSize().y))
			{
				//Check if given pixel is already of desired type to avoid unnecessary processing
				if (blocks[x + location.x - (brush_size - 1) / 2][y + location.y - (brush_size - 1) / 2].getType() == type)
					continue;

				//Comparison if current pixel is inside given circle
				if (std::sqrt(std::pow((brush_size - 1) / 2 - x, 2) + std::pow((brush_size - 1) / 2 - y, 2)) <= ((brush_size - 1) / 2))
				{
					//Change pixel to desired color
					image.setPixel(x + location.x - (brush_size - 1) / 2, y + location.y - (brush_size - 1) / 2,
						temp_image->getPixel((location.x + x - (brush_size - 1) / 2) % temp_image->getSize().x, (location.y + y - (brush_size - 1) / 2) % temp_image->getSize().y));

					//Also change Block
					blocks[x + location.x - (brush_size - 1) / 2][y + location.y - (brush_size - 1) / 2].type = type;
					blocks[x + location.x - (brush_size - 1) / 2][y + location.y - (brush_size - 1) / 2].friction = Config::BlockToFrictionMap.find(type)->second;
				}
			}
		}
	}
}

void Map::updateImageCircle2(sf::Vector2i location, const Config::BlockType type, const int brush_size)
{
	//If fully out do nothing
	if (location.x + brush_size / 2 <= 0)
		return;
	if (location.y + brush_size / 2 <= 0)
		return;

	//If partly out draw partly -- combined with below
	//If inside draw normally

	//Establish a medium to copy correctly from
	sf::Image temp;
	temp.create(100, 100);
	temp.copy(block_textures[static_cast<int>(type)], 0, 0, sf::IntRect(0, 0, 100, 100));
	temp.copy(circle_brush_masks[brush_size - 1], ((location.x >= 0) ? (location.x % 50) : (50 - std::abs(location.x))),
		((location.y >= 0) ? (location.y % 50) : (50 - std::abs(location.y))), sf::IntRect(0, 0, brush_size, brush_size), true);
	temp.createMaskFromColor(sf::Color::Red);
	//temp.createMaskFromColor(sf::Color(254, 254, 254, 254));

	//Copy wanted piece properly to the map image
	image.copy(temp,
		(location.x - (brush_size - 1) / 2 < 0) ? (0) : (location.x - (brush_size - 1) / 2),
		(location.y - (brush_size - 1) / 2 < 0) ? (0) : (location.y - (brush_size - 1) / 2),
		sf::IntRect(
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (50 + brush_size / 2) : (brush_size / 2)) : (location.x % 50),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (50 + brush_size / 2) : (brush_size / 2)) : (location.y % 50),
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (brush_size / 2 - std::abs(location.x)) : (brush_size / 2 + location.x)) : (brush_size),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (brush_size / 2 - std::abs(location.y)) : (brush_size / 2 + location.y)) : (brush_size)),
		true);

	//Change blocks using the same type of function as above
	sf::Image temp_block;
	//temp_block.create(100, 100, sf::Color(static_cast<unsigned int>(type));
	temp_block.create(100, 100, sf::Color(static_cast<std::uint32_t>((static_cast<unsigned int>(type) << 8) + 255)));
	temp_block.copy(circle_brush_masks[brush_size - 1], ((location.x >= 0) ? (location.x % 50) : (50 - std::abs(location.x))),
		((location.y >= 0) ? (location.y % 50) : (50 - std::abs(location.y))), sf::IntRect(0, 0, brush_size, brush_size), true);
	temp_block.createMaskFromColor(sf::Color::Red);
	//temp_block.createMaskFromColor(sf::Color(254, 254, 254, 254));

	//Change wanted blocks to the block image
	block_image.copy(temp_block,
		(location.x - (brush_size - 1) / 2 < 0) ? (0) : (location.x - (brush_size - 1) / 2),
		(location.y - (brush_size - 1) / 2 < 0) ? (0) : (location.y - (brush_size - 1) / 2),
		sf::IntRect(
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (50 + brush_size / 2) : (brush_size / 2)) : (location.x % 50),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (50 + brush_size / 2) : (brush_size / 2)) : (location.y % 50),
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (brush_size / 2 - std::abs(location.x)) : (brush_size / 2 + location.x)) : (brush_size),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (brush_size / 2 - std::abs(location.y)) : (brush_size / 2 + location.y)) : (brush_size)),
		true);
}

void Map::updateDrawable()
{
	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTexture(texture);
}