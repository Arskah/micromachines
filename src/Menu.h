#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow& window);
	~Menu() {}

protected:
	void eventLoop(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	void moveUp();
	void moveDown();
	virtual void select() = 0;

	int getAmountItems() const;
	sf::Text getSelected() const;

	int selectedItem = 0;

	sf::RenderWindow window;
	int width;
	int height;
private:
	sf::Image* backgroundImage;
	sf::Font font;
	std::vector<std::pair<sf::Text, std::string>> items;
};

class MainMenu : public Menu
{
	MainMenu(sf::RenderWindow& window) : Menu(window)
	{

	}
protected:
	virtual void select();
private:
	sf::Image* backgroundImage;
	//sf::Font font = ;
	std::vector<std::pair<sf::Text, std::string>> items;
};

class SettingsMenu : public Menu
{
	SettingsMenu(sf::RenderWindow& window) : Menu(window)
	{

	}
protected:
	virtual void select();
private:
	sf::Image* backgroundImage;
	//sf::Font font = ;
	std::vector<std::pair<sf::Text, std::string>> items;
};

class SinglePlayerMenu : public Menu
{
	SinglePlayerMenu(sf::RenderWindow& window) : Menu(window)
	{

	}
protected:
	virtual void select();
private:
	sf::Image* backgroundImage;
	//sf::Font font = ;
	std::vector<std::pair<sf::Text, std::string>> items;
};

class MultiPlayerMenu : public Menu
{
	MultiPlayerMenu(sf::RenderWindow& window) : Menu(window)
	{

	}
protected:
	virtual void select();
private:
	sf::Image* backgroundImage;
	//sf::Font font = ;
	std::vector<std::pair<sf::Text, std::string>> items;
};

class PauseMenu : public Menu
{
	PauseMenu(sf::RenderWindow& window) : Menu(window)
	{

	}
protected:
	virtual void select();
private:
	sf::Image* backgroundImage;
	//sf::Font font = ;
	std::vector<std::pair<sf::Text, std::string>> items;
};
