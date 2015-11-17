#include "Block.h"

Block::Block(const Config::BlockType type, const float friction)
{
	this->type = type;
	this->friction = friction;
}

Config::BlockType Block::getType() const
{
	return type;
}

float Block::getFriction() const
{
	return friction;
}
