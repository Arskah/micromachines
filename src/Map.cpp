#include "Map.h"

Map::Map() {}

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

	//Create drawable
	//createDrawable(blocktextures);
	//Create image
	createImage(blocktextures);
}

Block Map::getBlock(const std::size_t x, const std::size_t y) const
{
	if (x < blocks.size() && y < blocks.at(x).size())
		return blocks[x][y];
	else
		return Block(Config::BlockType::None, 0.f);
}

sf::Sprite * Map::getDrawable()
{
	return &(drawable);
}

void Map::createDrawable(const std::map<Config::BlockType, sf::Image> &blocktextures)
{
	render.create(blocks.size(), blocks[0].size());
	render.clear(sf::Color::White);

	sf::View view = render.getDefaultView();

	sf::RectangleShape draw_shape(sf::Vector2f(1, 1));
	for (std::size_t x = 0; x < blocks.size(); x++)
	{
		for (std::size_t y = 0; y < blocks[0].size(); y++)
		{
			draw_shape.setFillColor(blocktextures.find(blocks[x][y].getType())->second.getPixel(x % blocktextures.find(blocks[x][y].getType())->second.getSize().x, y % blocktextures.find(blocks[x][y].getType())->second.getSize().y));
			render.draw(draw_shape);

			view.move(0.f, -1.f);
			render.setView(view);
		}
		view.move(-1.f, float(blocks[0].size()));
		render.setView(view);
	}

	render.setView(render.getDefaultView());
	render.display();

	drawable.setTexture(render.getTexture());
}

void Map::updateDrawable(const std::map<Config::BlockType, sf::Image>& blocktextures, const sf::Vector2u location, const Config::BlockType type, const int brush_size)
{
	//DEPRECATED FUNCTION
	//ONLY STORED FOR POSSIBLE FUTURE REFERENCE
	sf::View view = render.getDefaultView();
	view.move(-sf::Vector2f(location));
	render.setView(view);

	//Pixel to draw
	sf::RectangleShape draw_shape(sf::Vector2f(1, 1));
	//Type to get image from
	sf::Image image = blocktextures.find(type)->second;

	/*
	//Box
	//Offset to center
	sf::Vector2f vec = sf::Vector2f(float((brush_size - 1) / 2), float((brush_size - 1) / 2));
	view.move(vec);
	render.setView(view);
	for (int x = 0; x < brush_size; x++)
	{
		for (int y = 0; y < brush_size; y++)
		{
			draw_shape.setFillColor(image.getPixel((location.x + x - (brush_size - 1) / 2) % image.getSize().x, (location.y + y - (brush_size - 1) / 2) % image.getSize().y));
			render.draw(draw_shape);
			view.move(0.f, -1.f);
			render.setView(view);
		}
		view.move(-1.f, float(brush_size));
		render.setView(view);
	}
	*/
	
	//Circle brush
	//Offset to center
	view.move(sf::Vector2f(sf::Vector2i((brush_size - 1) / 2, (brush_size - 1) / 2)));
	render.setView(view);
	//Loop over brush size
	for (int x = 0; x < brush_size; x++)
	{
		for (int y = 0; y < brush_size; y++)
		{
			//Comparison if current pixel is inside given circle
			if (std::sqrt(std::pow((brush_size - 1) / 2 - x, 2) + std::pow((brush_size - 1) / 2 - y, 2)) <= ((brush_size - 1) / 2))
			{
				//Draw pixel according to given image type
				draw_shape.setFillColor(image.getPixel((location.x + x - (brush_size - 1) / 2) % image.getSize().x, (location.y + y - (brush_size - 1) / 2) % image.getSize().y));
				render.draw(draw_shape);
			}
			//Move view to next pixel
			view.move(0.f, -1.f);
			render.setView(view);
		}
		//Move view to next column
		view.move(-1.f, float(brush_size));
		render.setView(view);
	}
	

	render.setView(render.getDefaultView());
	render.display();
	drawable.setTexture(render.getTexture());
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

void Map::loadNewImage()
{
	//Load image to texture
	texture.loadFromImage(image);
	//Load texture to sprite
	drawable.setTexture(texture);
}