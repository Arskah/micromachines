#include "Config.h"

/*
Global default values specified
*/
namespace Config
{
	extern const std::map<std::string, Config::BlockType> StringToBlockTypeMap = {
		{ "", BlockType::None },
		{ "none", BlockType::None },
		{ "ground", BlockType::Ground },
		{ "grass", BlockType::Grass },
		{ "sand", BlockType::Sand },
		{ "water", BlockType::Water },
		{ "rockwall", BlockType::RockWall } };

	extern const std::map<Config::ObjectType, Config::ObjectType> VehicleToProjectileMap = {
		{ ObjectType::Car1, ObjectType::Mine },
		{ ObjectType::Car2, ObjectType::Mine }
	};

	extern const std::map<BlockType, float> BlockToFrictionMap = {
		{ BlockType::None, 0.f },
		{ BlockType::Ground, 1.f },
		{ BlockType::Grass, 2.f },
		{ BlockType::Sand, 3.f },
		{ BlockType::Water, 1.f },
		{ BlockType::RockWall, 100.f },
		{ BlockType::Checkerboard, 1.f } };

	extern const float FrameCap = 60.0f;
}