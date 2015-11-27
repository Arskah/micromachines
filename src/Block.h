#pragma once

#include "Config.h"

class Block
{
public:
	//Give Editor access to be able to update blocks while under editing
	friend class Editor;

	//Alternative that initializes with values
	Block(const Config::BlockType type, const float friction);

	//Returns type from Block.
	Config::BlockType getType() const;

	//Returns friction from Block.
	float getFriction() const;
private:
	//Default Constructor, builds an empty Block
	Block();

	Config::BlockType type;
	float friction;
};
