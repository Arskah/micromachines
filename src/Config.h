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
		Boat
	};

	enum class BlockType
	{
		None,
		Ground,
		Grass,
		Sand,
		Water,
		Barrier
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

	extern const float FrameCap;
}
