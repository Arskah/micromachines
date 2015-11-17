#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Block.h"

class Map
{
public:
	Map();
	void loadFromFile(const std::string &filename);
	
private:
	std::vector<std::vector<Block>> blocks;
};
