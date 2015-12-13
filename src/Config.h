#pragma once


#include <SFML/Graphics.hpp>

/*
Declare global default values here and declare them in the .cpp to avoid linker errors
*/
namespace Config
{
	enum class ObjectType
	{
		None,
		Car1,
		Car2,
		Car3,
		Car4,
		Boat,
		Oilspill,
		Mine,
		Explosion
	};

	enum class BlockType
	{
		None,
		Ground,
		Grass,
		Sand,
		Water,
		RockWall,
		Checkerboard
	};

	enum class InputType
	{
		None,
		Accelerate,
		TurnLeft,
		TurnRight,
		Brake,
		Shoot
	};

	extern const std::map<std::string, Config::BlockType> StringToBlockTypeMap;
	extern const std::map<BlockType, float> BlockToFrictionMap;
	extern const std::map<BlockType, sf::Color> BlockToColorMap;
	extern const std::map<ObjectType, ObjectType> VehicleToProjectileMap;

	extern const float FrameCap;
}
