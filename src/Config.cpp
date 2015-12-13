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
		{ ObjectType::Car2, ObjectType::Mine },
		{ ObjectType::Car3, ObjectType::Mine },
		{ ObjectType::Car4, ObjectType::Mine },
		{ ObjectType::Oilspill, ObjectType::Oilspill }
	};

	extern const std::map<BlockType, float> BlockToFrictionMap = {
		{ BlockType::None, 0.f },
		{ BlockType::Ground, 1.f },
		{ BlockType::Grass, 2.f },
		{ BlockType::Sand, 3.f },
		{ BlockType::Water, 1.f },
		{ BlockType::RockWall, 100.f },
		{ BlockType::Checkerboard, 1.f } };

	extern const std::map<BlockType, sf::Color> BlockToColorMap = {
		{ BlockType::None, sf::Color::White },
		{ BlockType::Ground, sf::Color(46, 46, 46) },
		{ BlockType::Grass, sf::Color(0, 111, 0) },
		{ BlockType::Sand, sf::Color(223, 217, 149) },
		{ BlockType::Water, sf::Color(26, 178, 210) },
		{ BlockType::RockWall, sf::Color(62, 62, 62) },
		{ BlockType::Checkerboard, sf::Color::White }
	};

	extern const float FrameCap = 60.0f;
}