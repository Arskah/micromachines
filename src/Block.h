#pragma once

#include "Config.h"

class Block
{
public:
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
