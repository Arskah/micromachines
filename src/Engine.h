#pragma once

namespace Engine
{
	void update(sf::renderWindow* window, std::vector<Player> players, std::vector<Object> objects, Map map, std::pair<inputtype, bool> userinput);
	void playerInput(std::vector<Player> players, std::pair<inputtype, bool> userinput));
	void calculatePosObjects(std::vector<Object> objects);
	//void calculatePosProjectile();
	void draw_map(sf::renderWindow* window);
	void draw_objects(sf::renderWindow* window);
	void draw(sf::renderWindow* window);
};