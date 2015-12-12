#include "Map.h"

Map::Map()
{
	base_block = Config::BlockType::Ground;
}

bool Map::saveToImage(const std::string & filename)
{
	//Change first pixel to include data about base block
	sf::Color temp = block_image.getPixel(0, 0);
	sf::Uint32 temp_num = temp.toInteger();
	temp_num = temp_num % (1 << 24);
	temp_num = temp_num + (static_cast<int>(base_block) << 24);
	sf::Color new_color = sf::Color(temp_num);
	block_image.setPixel(0, 0, new_color);

	//Save image to filename.png
	return block_image.saveToFile(filename);
}

void Map::createLeftsideTrack()
{
	//Get starting line
	std::vector<std::pair<std::size_t, std::size_t>> finish_line_blocks;
	std::pair<std::size_t, std::size_t> coordinates;

	for (std::size_t x = 0; x < block_image.getSize().x; x++)
	{
		for (std::size_t y = 0; y < block_image.getSize().y; y++)
		{
			if (getBlock(x, y).getType() == Config::BlockType::Checkerboard)
			{
				coordinates.first = x;
				coordinates.second = y;
				finish_line_blocks.push_back(coordinates);
			}
		}
	}


	/* Get the coordinates of blocks on left side of track; coordinates pushed back to leftsideTrack vector */
	///Assuming that start happens up or right from the most wide part of finish line
	if ((finish_line_blocks.back().first - finish_line_blocks.front().first) >= (finish_line_blocks.back().second - finish_line_blocks.front().second))		// True if dx >= dy   =>   race starts towards up
	{
		coordinates.first = finish_line_blocks.front().first;
		coordinates.second = finish_line_blocks.back().second;
		finishLine.first.first = coordinates;
		coordinates.first = finish_line_blocks.back().first;
		coordinates.second = finish_line_blocks.back().second;
		finishLine.first.second = coordinates;
		finishLine.second = true;
/*
		coordinates.first = finish_line_blocks.back().first;
		coordinates.second = finish_line_blocks.back().second + 1;
		TrackMaterial = Map::getBlock(coordinates.first, coordinates.second).getType();
		leftsideTrack.push_back(coordinates);	// First block of track is one tile up from first finish line block in vector

		coordinates = Map::checkNextLeftBlockStartU(coordinates);
		while (std::find(leftsideTrack.begin(), leftsideTrack.end(), coordinates) == leftsideTrack.end())				// LOOP until back in start block
		{
			leftsideTrack.push_back(coordinates);
			coordinates = Map::checkNextLeftBlockStartU(coordinates);
		}
*/
	}
	else																																					// else going right
	{
		coordinates.first = finish_line_blocks.back().first;
		coordinates.second = finish_line_blocks.back().second;
		finishLine.first.first = coordinates;
		coordinates.first = finish_line_blocks.back().first;
		coordinates.second = finish_line_blocks.front().second;
		finishLine.first.second = coordinates;
		finishLine.second = false;
/*
		coordinates.first = finish_line_blocks.back().first + 1;
		coordinates.second = finish_line_blocks.back().second;
		TrackMaterial = Map::getBlock(coordinates.first, coordinates.second).getType();
		leftsideTrack.push_back(coordinates);	// First block of track is one tile up from first finish line block in vector

		coordinates = Map::checkNextLeftBlockStartR(coordinates);
		while (std::find(leftsideTrack.begin(), leftsideTrack.end(), coordinates) == leftsideTrack.end())				// LOOP until back in start block
		{
			leftsideTrack.push_back(coordinates);
			coordinates = Map::checkNextLeftBlockStartR(coordinates);
		}
*/
	}

	/* Now we have vector of all left side blocks of a track, now we need to figure out what to do with them */
}
/*
std::pair<std::size_t, std::size_t> Map::checkNextLeftBlockStartU(std::pair<std::size_t, std::size_t> coordinates)
{
	if (Map::getBlock(coordinates.first - 1, coordinates.second).getType() == TrackMaterial || Map::getBlock(coordinates.first - 1, coordinates.second).getType() == Config::BlockType::Checkerboard)				// x-1
		coordinates.first = coordinates.first - 1;

	else if (Map::getBlock(coordinates.first - 1, coordinates.second - 1).getType() == TrackMaterial || Map::getBlock(coordinates.first - 1, coordinates.second - 1).getType() == Config::BlockType::Checkerboard)		// y+1 x-1
	{
		coordinates.first = coordinates.first - 1;
		coordinates.second = coordinates.second + 1;
	}

	else if (Map::getBlock(coordinates.first, coordinates.second - 1).getType() == TrackMaterial || Map::getBlock(coordinates.first, coordinates.second - 1).getType() == Config::BlockType::Checkerboard)			// y+1
		coordinates.first = coordinates.second + 1;

	else if (Map::getBlock(coordinates.first + 1, coordinates.second - 1).getType() == TrackMaterial || Map::getBlock(coordinates.first + 1, coordinates.second - 1).getType() == Config::BlockType::Checkerboard)		//x+1 y+1
	{
		coordinates.first = coordinates.first + 1;
		coordinates.second = coordinates.second + 1;
	}

	else if (Map::getBlock(coordinates.first + 1, coordinates.second).getType() == TrackMaterial || Map::getBlock(coordinates.first + 1, coordinates.second).getType() == Config::BlockType::Checkerboard)			//x+1
		coordinates.first = coordinates.first + 1;

	else if (Map::getBlock(coordinates.first + 1, coordinates.second + 1).getType() == TrackMaterial || Map::getBlock(coordinates.first + 1, coordinates.second + 1).getType() == Config::BlockType::Checkerboard)		//x+1 y-1
	{
		coordinates.first = coordinates.first + 1;
		coordinates.second = coordinates.second - 1;
	}
	else																																																						// y-1
	{
		coordinates.second = coordinates.second - 1;
	}
	return coordinates;
}

std::pair<std::size_t, std::size_t> Map::checkNextLeftBlockStartR(std::pair<std::size_t, std::size_t> coordinates)
{
	if (Map::getBlock(coordinates.first, coordinates.second - 1).getType() == TrackMaterial || Map::getBlock(coordinates.first, coordinates.second - 1).getType() == Config::BlockType::Checkerboard)				// y+1
		coordinates.second = coordinates.second + 1;

	else if (Map::getBlock(coordinates.first + 1, coordinates.second + 1).getType() == TrackMaterial || Map::getBlock(coordinates.first + 1, coordinates.second - 1).getType() == Config::BlockType::Checkerboard)		// y+1 x+1
	{
		coordinates.first = coordinates.first + 1;
		coordinates.second = coordinates.second + 1;
	}
	else if (Map::getBlock(coordinates.first + 1, coordinates.second).getType() == TrackMaterial || Map::getBlock(coordinates.first + 1, coordinates.second).getType() == Config::BlockType::Checkerboard)			// x+1
		coordinates.first = coordinates.first + 1;

	else if (Map::getBlock(coordinates.first + 1, coordinates.second + 1).getType() == TrackMaterial || Map::getBlock(coordinates.first + 1, coordinates.second + 1).getType() == Config::BlockType::Checkerboard)		//y-1 x+1
	{
		coordinates.first = coordinates.first + 1;
		coordinates.second = coordinates.second - 1;
	}

	else if (Map::getBlock(coordinates.first, coordinates.second + 1).getType() == TrackMaterial || Map::getBlock(coordinates.first, coordinates.second + 1).getType() == Config::BlockType::Checkerboard)			//y-1
		coordinates.second = coordinates.second - 1;

	else if (Map::getBlock(coordinates.first - 1, coordinates.second + 1).getType() == TrackMaterial || Map::getBlock(coordinates.first - 1, coordinates.second + 1).getType() == Config::BlockType::Checkerboard)		//y-1 x-1
	{
		coordinates.first = coordinates.first - 1;
		coordinates.second = coordinates.second - 1;
	}
	else																																																					//x-1
	{
		coordinates.first = coordinates.first - 1;
	}
	return coordinates;
}
*/

void Map::splitImages(const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Make textures
	for (std::size_t x = 0; x < std::size_t(image.getSize().x / 256); x++)
	{
		for (std::size_t y = 0; y < std::size_t(image.getSize().y / 256); y++)
		{
			sf::Image temp_image;
			temp_image.create(256, 256, sf::Color::Cyan);
			temp_image.copy(image, 0, 0, sf::IntRect(x * 256, y * 256, 256, 256));

			sf::Texture temp_texture;
			textures.push_back(temp_texture);
			textures.back().loadFromImage(temp_image);
		}
	}

	//Apply textures to sprites
	for (std::size_t x = 0; x < std::size_t(image.getSize().x / 256); x++)
	{
		for (std::size_t y = 0; y < std::size_t(image.getSize().y / 256); y++)
		{
			drawables.emplace_back(textures[x * std::size_t(image.getSize().y / 256) + y]);
			drawables.back().setPosition(x * 256, y * 256);
		}
	}

	//Background
	background_texture.loadFromImage(blocktextures.find(base_block)->second);
	
	//Top
	for (int x = -4; x < int(image.getSize().x / 256) + 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			background_sprites.emplace_back(background_texture);
			background_sprites.back().setPosition((256 * x), (256 * (y + 1)) * -1);
		}
	}

	//Bot
	for (int x = -4; x < int(image.getSize().x / 256) + 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			background_sprites.emplace_back(background_texture);
			background_sprites.back().setPosition((256 * x), 256 * y + image.getSize().y);
		}
	}

	//Left
	for (int y = 0; y < int(image.getSize().y / 256); y++)
	{
		for (int x = 0; x < 4; x++)
		{
			background_sprites.emplace_back(background_texture);
			background_sprites.back().setPosition((256 * (x + 1)) * -1, y * 256);
		}
	}

	//Right
	for (int y = 0; y < int(image.getSize().y / 256); y++)
	{
		for (int x = 0; x < 4; x++)
		{
			background_sprites.emplace_back(background_texture);
			background_sprites.back().setPosition((256 * x) + image.getSize().x, y * 256);
		}
	}
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
	blockrow.clear();

	//Read base block
	base_block = static_cast<Config::BlockType>(block_image.getPixel(0, 0).toInteger() >> 24);

	//Raw pointer to block types, will need a conversion
	const sf::Uint8 * block_info = block_image.getPixelsPtr();
	//Right starting position to start reading from (pixel is 4x sf::Uint8)
	block_info += 2;

	//Pointer to block type information
	sf::Uint32 * ptr_u = (sf::Uint32 *)block_info;
	//Get type values from pixels
	std::vector<sf::Uint8> type_values((const sf::Uint32 *)ptr_u, ((const sf::Uint32 *)ptr_u + block_image.getSize().x * block_image.getSize().y));


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
	for (std::size_t i = 0; i < block_counts.size(); i++)
	{
		blockrow.insert(blockrow.end(), std::size_t(block_counts[i].second), block_counts[i].first);
	}

	//Create new drawable image
	createImageFromBlockImage(blocktextures);


	//Save coordinates of all blocks on left side of track and save in map object
	createLeftsideTrack();

	splitImages(blocktextures);


	//Went successfully
	return true;
}

Block Map::getBlock(const int x, const int y) const
{
	if (x >= 0 && y >= 0 && x < int(block_image.getSize().x) && y < int(block_image.getSize().y))
		return Block(blockrow[x + (y * block_image.getSize().x)], Config::BlockToFrictionMap.find(blockrow[x + (y * block_image.getSize().x)])->second);
	else
		return Block(Config::BlockType::None, Config::BlockToFrictionMap.find(Config::BlockType::None)->second);
}

sf::Sprite * Map::getDrawable()
{
	return &(drawable);
}


std::pair<std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>>, bool> Map::getFinishline() const
{
	return finishLine;
}

Config::BlockType Map::getTrackMaterial()
{
	return TrackMaterial;
}
/*
std::vector<std::pair<std::size_t, std::size_t>> Map::getLeftsideBlocks()
{
	return leftsideTrack;
}
*/

void Map::drawMap(sf::RenderWindow & window)
{
	//Draw map
	for (int i = 0; i < drawables.size(); i++)
	{
		window.draw(drawables[i]);
	}

	//Draw outside of map with block background
	for (int i = 0; i < background_sprites.size(); i++)
	{
		window.draw(background_sprites[i]);
	}
}


void Map::createThumbnail(const std::string &filename, const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Load image
	if (!block_image.loadFromFile(filename))
		return;

	//Make temp smaller image
	sf::Image thumbnail_block_image;
	thumbnail_block_image.create(100, 100, sf::Color::Red);

	//Copy certain spots with scaling to 100x100 to the temp image
	std::size_t count_x = 0, count_y = 0;

	for (float x = 0; x < block_image.getSize().x; x += (block_image.getSize().x / 100.f))
	{
		for (float y = 0; y < block_image.getSize().y; y += (block_image.getSize().y / 100.f))
		{
			thumbnail_block_image.copy(block_image, count_x, count_y, sf::IntRect(int(x), int(y), 1, 1));
			count_y++;
		}
		count_y = 0;
		count_x++;
	}

	//Copy thumbnail_block_image to be block_image now
	block_image = thumbnail_block_image;

	//Create drawable image from current small block image

	//Empty old image
	image.create(block_image.getSize().x, block_image.getSize().y);
	//Copy new one
	//Loop over positions and copy pixel-by-pixel the image
	for (std::size_t x = 0; x < block_image.getSize().x; x++)
	{
		for (std::size_t y = 0; y < block_image.getSize().y; y++)
		{
			image.copy(blocktextures.find(static_cast<Config::BlockType>(block_image.getPixel(x, y).toInteger() >> 8))->second, x, y,
				sf::IntRect(x % blocktextures.find(Config::BlockType::None)->second.getSize().x, y % blocktextures.find(Config::BlockType::None)->second.getSize().y, 1, 1));
		}
	}

	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTextureRect(sf::IntRect(0, 0, image.getSize().x, image.getSize().y));
	drawable.setTexture(texture);
}

sf::Vector2f Map::getStartPosition(const int player_number)
{
	sf::Vector2f location;
	location.x = float(block_image.getSize().x / 2);
	location.y = float(block_image.getSize().y / 2 - 255 + (player_number + 1) * 102);
	return location;
}

void Map::createImageFromBlockImage(const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Empty old image
	image.create(block_image.getSize().x, block_image.getSize().y, sf::Color::Red);

	//Build new image
	for (std::size_t i = 0; i < blocktextures.size(); i++)
	{
		sf::Image temp;
		//Create image of each blockType to the size of the Map for usage later
		temp.create(block_image.getSize().x, block_image.getSize().y, sf::Color::Red);
		//Sizes
		sf::Vector2u block_texture_size = blocktextures.find(static_cast<Config::BlockType>(i))->second.getSize();
		for (std::size_t x = 0; x < block_image.getSize().x; x += block_texture_size.x)
		{
			for (std::size_t y = 0; y < block_image.getSize().y; y += block_texture_size.y)
			{
				temp.copy(blocktextures.find(static_cast<Config::BlockType>(i))->second, x, y, sf::IntRect(0, 0,
					(x + block_texture_size.x < block_image.getSize().x) ? (block_texture_size.x) : (x % block_texture_size.x),
					(y + block_texture_size.y < block_image.getSize().y) ? (block_texture_size.y) : (y % block_texture_size.y)));
			}
		}

		//Use map sized base image as a mask
		sf::Image block_temp = block_image;
		block_temp.createMaskFromColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(i), sf::Uint8(255)));
		temp.copy(block_temp, 0, 0, sf::IntRect(0, 0, block_temp.getSize().x, block_temp.getSize().y), true);
		//Filter every block color away.
		for (std::size_t j = 0; j < blocktextures.size(); j++)
			temp.createMaskFromColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(j), sf::Uint8(255)));

		//Copy temp to Map image
		image.copy(temp, 0, 0, sf::IntRect(0, 0, block_image.getSize().x, block_image.getSize().y), true);
	}

	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTextureRect(sf::IntRect(0, 0, image.getSize().x, image.getSize().y));
	drawable.setTexture(texture);
}
