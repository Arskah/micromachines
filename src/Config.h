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
		OilSpill,
		Car,
		Boat,
		Mine
	};

	enum class BlockType
	{
		None,
		Ground,
		Grass,
		Sand,
		Water,
		RockWall
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

	extern const float FrameCap;
}
