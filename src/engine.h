#pragma once

namespace Engine
{
	void update(sf::renderWindow* window, std::vector<Player> players, std::vector<Object> objects, Map map, std::pair<inputtype, bool> userinput);
	void calculatePosObjects(std::vector<Object> objects);
	void calculatePosPlayers(std::vector<Player> players, std::pair<inputtype, bool> userinput));
	void draw(sf::renderWindow* window);
};