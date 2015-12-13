#include "Map.h"

Map::Map()
{
	size = sf::Vector2u(0, 0);
	base_block = Config::BlockType::Ground;
	finishLine.first.first = 128;
	finishLine.first.second = 255;
	finishLine.second.first = 128;
	finishLine.second.second = -255;
}

bool Map::saveToImage(const std::string & filename, const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Change first pixel to include data about base block
	sf::Color temp = block_image.getPixel(0, 0);
	sf::Uint32 temp_num = temp.toInteger();
	temp_num = temp_num % (1 << 24);
	temp_num = temp_num + (static_cast<int>(base_block) << 24);
	sf::Color new_color = sf::Color(temp_num);
	block_image.setPixel(0, 0, new_color);

	//Save image to filename.png
	if (!block_image.saveToFile(filename))
		return false;

	//Pre-render image
	loadFromImage(filename, blocktextures);

	//Add postfix "_render" to map image file
	std::string rendered_image_str = filename.substr(0, filename.size() - 4);
	rendered_image_str.append("_render.png");

	//Save rendered image
	if (!image.saveToFile(rendered_image_str))
		return false;

	//All good
	return true;
}

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
			drawables.back().setPosition(float(x * 256), float(y * 256));
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
			background_sprites.back().setPosition(float((256 * x)), float((256 * (y + 1)) * -1));
		}
	}

	//Bot
	for (int x = -4; x < int(image.getSize().x / 256) + 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			background_sprites.emplace_back(background_texture);
			background_sprites.back().setPosition(float((256 * x)), float(256 * y + image.getSize().y));
		}
	}

	//Left
	for (int y = 0; y < int(image.getSize().y / 256); y++)
	{
		for (int x = 0; x < 4; x++)
		{
			background_sprites.emplace_back(background_texture);
			background_sprites.back().setPosition(float((256 * (x + 1)) * -1), float(y * 256));
		}
	}

	//Right
	for (int y = 0; y < int(image.getSize().y / 256); y++)
	{
		for (int x = 0; x < 4; x++)
		{
			background_sprites.emplace_back(background_texture);
			background_sprites.back().setPosition(float((256 * x) + image.getSize().x), float(y * 256));
		}
	}
}

bool Map::loadFromImage(const std::string & filename, const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Load image
	if (!block_image.loadFromFile(filename))
		return false;

	//Get map size from block_image
	size = block_image.getSize();

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
	std::vector<sf::Uint8> type_values((const sf::Uint32 *)ptr_u, ((const sf::Uint32 *)ptr_u + size.x * size.y));


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

	//Check if we have a pre-rendered image saved on disk
	std::string rendered_image_str = filename.substr(0, filename.size() - 4);
	rendered_image_str.append("_render.png");
	if (image.loadFromFile(rendered_image_str))
	{
		//Load image to texture
		texture.loadFromImage(image);
		//Load texture to sprite
		drawable.setTextureRect(sf::IntRect(0, 0, image.getSize().x, image.getSize().y));
		drawable.setTexture(texture);
	}
	else
	{
		//We did not find one, render one now
		//Create new drawable image
		createImageFromBlockImage(blocktextures);
	}

	//Split created image into 256 x 256px pieces for rendering in Engine
	splitImages(blocktextures);


	//Went successfully
	return true;
}

Block Map::getBlock(const int x, const int y) const
{
	//Check bounds that we indeed are inside the map
	if (x >= 0 && y >= 0 && x < int(size.x) && y < int(size.y))
		return Block(blockrow[x + (y * size.x)], Config::BlockToFrictionMap.find(blockrow[x + (y * size.x)])->second);
	else
		//Something is wrong, but avoid program crash
		return Block(Config::BlockType::None, Config::BlockToFrictionMap.find(Config::BlockType::None)->second);
}

sf::Sprite * Map::getDrawable()
{
	return &(drawable);
}


std::pair<std::pair<std::size_t, std::size_t>, std::pair<std::size_t, std::size_t>> Map::getFinishline() const
{
	 return finishLine;
}

Config::BlockType Map::getTrackMaterial()
{
	return blockrow[(size.x / 2 + 128) + ((size.y / 2) * size.x)];
}

void Map::drawMap(sf::RenderWindow & window)
{
	//Draw all pieces of map and background 1-by-1
	//Draw map
	for (std::size_t i = 0; i < drawables.size(); i++)
	{
		window.draw(drawables[i]);
	}

	//Draw outside of map with block background
	for (std::size_t i = 0; i < background_sprites.size(); i++)
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
			image.setPixel(x, y, Config::BlockToColorMap.find(static_cast<Config::BlockType>((block_image.getPixel(x, y).toInteger() >> 8) & 255))->second);
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
	location.x = float(size.x / 2);
	location.y = float(size.y / 2 - 255 + (player_number + 1) * 102);
	return location;
}

void Map::createImageFromBlockImage(const std::map<Config::BlockType, sf::Image>& blocktextures)
{
	//Empty old image
	image.create(size.x, size.y, sf::Color::Red);

	//Build new image
	for (std::size_t i = 0; i < blocktextures.size(); i++)
	{
		sf::Image temp;
		//Create image of each blockType to the size of the Map for usage later
		temp.create(size.x, size.y, sf::Color::Red);
		//Sizes
		sf::Vector2u block_texture_size = blocktextures.find(static_cast<Config::BlockType>(i))->second.getSize();
		for (std::size_t x = 0; x < size.x; x += block_texture_size.x)
		{
			for (std::size_t y = 0; y < size.y; y += block_texture_size.y)
			{
				temp.copy(blocktextures.find(static_cast<Config::BlockType>(i))->second, x, y, sf::IntRect(0, 0,
					(x + block_texture_size.x < size.x) ? (block_texture_size.x) : (x % block_texture_size.x),
					(y + block_texture_size.y < size.y) ? (block_texture_size.y) : (y % block_texture_size.y)));
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
		image.copy(temp, 0, 0, sf::IntRect(0, 0, size.x, size.y), true);
	}

	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTextureRect(sf::IntRect(0, 0, image.getSize().x, image.getSize().y));
	drawable.setTexture(texture);
}
