#include "engine.hpp"

#define COOLDOWN 1

void Engine::update(sf::renderWindow* window, std::vector<Player> players, std::vector<Object> objects, Map map, std::pair<inputtype, bool> userinput)
{
	for (auto it = player.begin(); it != player.end(); it++)
	{
		playerInput(it,)
	}
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		switch (it.getType())
		{
		case projectile:
			calculatePosProjectile(it);
		case Vehicle:
			calculatePosObject(it);
		}
	}
}

/* Handles userinput before moving the object*/
void Engine::playerInput(Player player, std::pair<inputtype, bool> userinput))
{
	if (userinput.second())
	{
		switch (userinput.first())
		{
		case left:
			player.getVehicle().turn(true);
		case right:
			player.getVehicle().turn(false);
		case accelerate:
			player.getVehicle().accelerate();
		case brake:
			player.getVehicle().brake();
		case default:
			// Open menu? What other inputs we have?
		}
	}
	//calculatePosObject(player);
}

void Engine::calculatePosObject(Object object)
{
	if (object.speed != 0)
	{
		object.move();
	}
}
/*
void Engine::calculatePosProjectile(Object projectile)
{
	while (projectile.getLocation())
}
*/
void Engine::draw_map()
{

}

void Engine::draw_objects()
{

}

void Engine::draw_vehicles()
{

}

void Engine::draw(sf::renderWindow* window)
{
	window.clear(sf::Color::Black);			// Clear previous frame
	/*Draw current frame: base first (blocks), objects, players last*/
	window.draw_map();
	window.draw_objects();
	window.draw_vehicles();
	window.display();						// Update drawings
}
