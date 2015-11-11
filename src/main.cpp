#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Micro Machines");
	
	/*
	
	PASS THE WINDOW TO THE MENU HERE PLS
	
	*/
	
	while(window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
	
	return 0;
}