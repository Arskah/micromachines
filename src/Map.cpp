#include "Map.h"

Map::Map() {}

void Map::loadFromFile(const std::string &filename)
{
	int size_x = 0;
	int size_y = 0;
	int current_x = 0;
	int current_y = 0;

	std::vector<Block> row;

	std::string line;
	std::ifstream objectfile;
	objectfile.open("src/resources/map_example1.txt", std::ifstream::in);
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
}