#pragma once

#include "Config.h"

class Block
{
public:
	//Give map access to be able to update blocks while under editing
	friend class Map;

	//Default Constructor
	Block(const Config::BlockType type, const float friction);

	//Returns type from Block.
	Config::BlockType getType() const;

	//Returns friction from Block.
	float getFriction() const;
private:
	Config::BlockType type;
	float friction;
};
