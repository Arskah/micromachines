#include "Editor.h"

Editor::Editor(sf::RenderWindow & window, const std::map<Config::BlockType, sf::Image> * blocktextures) : window(window), map(*blocktextures)
{
	this->blocktextures = blocktextures;
}

void Editor::runEditor()
{
	//Ask what to do on init
	{
		std::string input = openTextbox("Create new or load? Type 'new' or 'load'", Editor::BoxTypes::Text);
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		//Load file
		if (input == "load")
		{
			std::string filename = openTextbox("Enter filename to load from");
			if (filename.size() != 0)
			{
				filename.insert(0, "src/resources/");
				filename.append(".png");
				//Check if load successfull
				if (!map.loadFromImage(filename, *blocktextures))
				{
					openTextbox(" Load failed. Creating new map, press ESC to continue");
					initMap();
				}
			}
			else
			{
				openTextbox("False filename, creating new...");
				initMap();
			}
		}
		//Create new
		else
			initMap();
	}

	//Variables
	bool exit = false;
	int brush_size = 25;

	//Set default_view to window default to start from
	sf::View default_view = window.getDefaultView();

	//Minimap settings
	sf::View minimap_view;
	minimap_view = window.getDefaultView();
	minimap_view.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));

	//Block Toolbar UI
	sf::Image blocks_ui_image;
	std::vector<const sf::Image *> block_images;
	for (std::size_t i = 1; i < blocktextures->size(); i++)
	{
		block_images.push_back(&(blocktextures->find(static_cast<Config::BlockType>(i))->second));
	}
	createUI(block_images, &blocks_ui_image);
	sf::Texture blocks_ui_tex;
	blocks_ui_tex.loadFromImage(blocks_ui_image);
	sf::Sprite blocks_ui;
	blocks_ui.setTexture(blocks_ui_tex);

	//Map update functions
	//void (Map::*updateImageFunc)(const std::map<Config::BlockType, sf::Image>&, const sf::Vector2u, const Config::BlockType, const int) = &Map::updateImageCircle;
	void (Map::*updateImageFunc)(const sf::Vector2i, const Config::BlockType, const int) = &Map::updateImageCircle;
	Config::BlockType block_to_draw = Config::BlockType::Ground;

	//Catch wanted draw points to these
	std::deque<sf::Vector2i> pixels_to_draw_on;
	std::deque<sf::Vector2i> captured_pixels;

	//Timer to avoid scrolling too much
	sf::Clock scroll_timer;
	const int scroll_delay = 200;

	//Start screen
	//Code
	//Code
	//Code

	//Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Temp variables
			std::string filename;

			bool test = false;

			switch (event.type)
			{
				//If window closed, close everything
			case sf::Event::Closed:
				window.close();
				break;
				//Check hotkeys
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					//From esc close leveleditor and return back
				case sf::Keyboard::Escape:
					exit = true;
					break;
					//Create New Map
				case sf::Keyboard::N:
					initMap();
					break;
					//Save file
				case sf::Keyboard::S:
					filename = openTextbox("Enter filename to save to");
					if (filename.size() != 0)
					{
						filename.insert(0, "src/resources/");
						filename.append(".png");
						//Check if save successfull
						test = map.saveToImage(filename);
					}
					break;
					//Load file
				case sf::Keyboard::L:
					filename = openTextbox("Enter filename to load from");
					if (filename.size() != 0)
					{
						filename.insert(0, "src/resources/");
						filename.append(".png");
						//Check if load successfull
						map.loadFromImage(filename, *blocktextures);
					}
					break;
					//From 'Numpad +' or 'E' increase brush size
				case sf::Keyboard::Add:
				case sf::Keyboard::E:
					//if (brush_size < 99)
					if (brush_size < 49)
						brush_size += 2;
					break;
					//From 'Numpad -' or 'Q' decrease brush size
				case sf::Keyboard::Subtract:
				case sf::Keyboard::Q:
					if (brush_size > 2)
						brush_size -= 2;
					break;
					//From 'B' change brush type to box
				case sf::Keyboard::B:
					updateImageFunc = &Map::updateImageBox;
					break;
					//From 'C' change brush type to circle
				case sf::Keyboard::C:
					updateImageFunc = &Map::updateImageCircle;
					break;
					//From numbers 1-9 pick block type
				case sf::Keyboard::Num1:
				case sf::Keyboard::Num2:
				case sf::Keyboard::Num3:
				case sf::Keyboard::Num4:
				case sf::Keyboard::Num5:
				case sf::Keyboard::Num6:
				case sf::Keyboard::Num7:
				case sf::Keyboard::Num8:
				case sf::Keyboard::Num9:
					if ((event.key.code - 26) < int(blocktextures->size()))
					{
						block_to_draw = static_cast<Config::BlockType>(event.key.code - 26);
					}
					break;
				}
				break;
				//Move view center to current mouse position by releasing scroll wheel on wanted position
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Button::Middle)
				{
					default_view.setCenter(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), default_view)));
				}
				break;
				//Change block type with scrolling up and down
			case sf::Event::MouseWheelScrolled:
				//Check time from last scroll event to avoid scrolling more than one position at a time
				if (scroll_timer.getElapsedTime().asMilliseconds() > scroll_delay)
				{
					//If up, go next
					if (event.mouseWheelScroll.delta > 0)
					{
						//Go first
						if ((static_cast<int>(block_to_draw) + 1) == (blocktextures->size()))
						{
							block_to_draw = static_cast<Config::BlockType>(1);
						}
						else
							//Go up one
							block_to_draw = static_cast<Config::BlockType>(static_cast<int>(block_to_draw) + 1);
					}
					//If down, go backwards
					else if (event.mouseWheelScroll.delta < 0)
					{
						//Go last
						if ((static_cast<int>(block_to_draw) - 1) == 0)
						{
							block_to_draw = static_cast<Config::BlockType>(blocktextures->size() - 1);
						}
						else
							//Go down one
							block_to_draw = static_cast<Config::BlockType>(static_cast<int>(block_to_draw) - 1);
					}
					//Restart timer
					scroll_timer.restart();
				}
				break;
			}
		}

		//Faster here than in event loop
		//Capture clicked position
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i location_i = sf::Mouse::getPosition(window);
			if (location_i.x >= 0 && location_i.y >= 0)
			{
				//Capture current mouse spot and convert to coords in world
				captured_pixels.push_back(sf::Vector2i(window.mapPixelToCoords(location_i, default_view)));
			}
		}
		//Mouse not clicked, clear queues to be able to draw new line without connection to the one before
		else
		{
			captured_pixels.clear();
			pixels_to_draw_on.clear();
		}

		//Track points to draw to (this is to avoid patchy drawing when moving mouse quickly)
		while (captured_pixels.size() > 1)
		{
			if (pixels_to_draw_on.size() > 0)
			{
				const float start_x = float(pixels_to_draw_on.back().x);
				const float end_x = float(captured_pixels.front().x);

				const float start_y = float(pixels_to_draw_on.back().y);
				const float end_y = float(captured_pixels.front().y);

				float k = 0;
				if ((end_x - start_x) != 0)
					k = (end_y - start_y) / (end_x - start_x);

				const float b = start_y - k * start_x;

				float current_x = start_x;
				float current_y = start_y;

				if (std::abs(k) < 1)
				{
					while ((current_x < end_x && start_x < end_x) || (current_x > end_x && start_x > end_x))
					{
						pixels_to_draw_on.push_back(sf::Vector2i(int(current_x), int(current_y)));
						if (current_x < end_x)
							current_x++;
						else
							current_x--;

						current_y = k * current_x + b;
					}
				}
				else
				{
					while ((current_y < end_y && start_y < end_y) || (current_y > end_y && start_y > end_y))
					{
						pixels_to_draw_on.push_back(sf::Vector2i(int(current_x), int(current_y)));
						if (current_y < end_y)
							current_y++;
						else
							current_y--;

						current_x = (current_y - b) / k;
					}
				}
			}
			else
				pixels_to_draw_on.push_back(captured_pixels.front());
			captured_pixels.pop_front();
		}

		//Draw on the positions calculated before this
		//If only one point clicked, then do only that
		if (pixels_to_draw_on.size() == 1)
		{
			(map.*updateImageFunc)(sf::Vector2i(pixels_to_draw_on.front()), block_to_draw, brush_size);
		}
		//Otherwise do the whole lines until empty
		else
		{
			while (pixels_to_draw_on.size() > 1)
			{
				(map.*updateImageFunc)(sf::Vector2i(pixels_to_draw_on.front()), block_to_draw, brush_size);
				pixels_to_draw_on.pop_front();
			}
		}

		//Load new image to map for displaying
		map.updateDrawable();

		//Set default view to window in case it has changed
		window.setView(default_view);

		//Clear window
		window.clear();

		//Draw Map
		window.draw((*map.getDrawable()));

		//Draw interfaces
		blocks_ui.setPosition(5.f + window.getView().getCenter().x - (window.getSize().x / 2),
			window.getView().getCenter().y + (window.getSize().y / 2) - blocks_ui.getTexture()->getSize().y - 5.f);
		window.draw(blocks_ui);

		//Selection box for blocks_ui
		//Slightly broken if using other than 1280x720 maps.
		//Will be fixed
		//window.draw(createSelected(&block_images, &blocks_ui, static_cast<int>(block_to_draw)));

		//Minimap
		window.setView(minimap_view);
		window.draw((*map.getDrawable()));

		//Display
		window.display();

		//Exit loop
		if (exit)
		{
			window.setView(window.getDefaultView());
			break;
		}
	}
}

void Editor::initMap()
{
	sf::Vector2u size;

	std::string size_x = "", size_y = "";
	while (size_x == "")
		size_x = openTextbox("Please enter map size X", BoxTypes::Number);
	while (size_y == "")
		size_y = openTextbox("Please enter map size Y", BoxTypes::Number);

	size.x = std::stoi(size_x);
	size.y = std::stoi(size_y);
	//size.x = 30;
	//size.y = 30;

	std::string base = openTextbox("Do you want a base block for the map? Write block type or leave empty.", BoxTypes::Text);

	//DEBUG BASE
	//std::string base = "sand";

	//Change inputted string to lowercase
	std::transform(base.begin(), base.end(), base.begin(), ::tolower);
	
	//Specify base block type
	Config::BlockType base_block_type = Config::BlockType::None;

	//If we received a desired BlockType
	if (Config::StringToBlockTypeMap.find(base) != Config::StringToBlockTypeMap.end())
	{
		base_block_type = Config::StringToBlockTypeMap.find(base)->second;
	}

	//Create an image of the map
	map.createImageFromBase((*blocktextures), size, base_block_type);
}

std::string Editor::openTextbox(const std::string &box_name, const BoxTypes box_type)
{
	//Create new window
	sf::RenderWindow window(sf::VideoMode(400, 24), box_name, sf::Style::Titlebar);
	window.requestFocus();

	//Textbox
	sf::RectangleShape shape(sf::Vector2f(396, 20));;
	shape.setFillColor(sf::Color::White);
	shape.setPosition(2, 2);

	//Text
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(14);
	text.setPosition(4, 2);

	//Returnable string
	std::string user_string;

	//Loop here
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//If user presses enter and has entered text, return
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Return && user_string.size() > 0)
				{
					window.close();
					return user_string;
				}
				//Remove last letter from backspace
				else if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (user_string.size() > 0)
						user_string.pop_back();
				}
				//Abort and return empty
				else if (event.key.code == sf::Keyboard::Escape)
				{
					return std::string();
				}
				break;
				//Take input on wanted BoxType
			case sf::Event::TextEntered:
				switch (box_type)
				{
				case BoxTypes::Text:
					if ((event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 97 && event.text.unicode <= 122))
						user_string.append(std::string(1, static_cast<char>(event.text.unicode)));
					break;
				case BoxTypes::Number:
					if (event.text.unicode >= 48 && event.text.unicode <= 57)
						user_string.append(std::string(1, static_cast<char>(event.text.unicode)));
					break;
				case BoxTypes::Alphanumeric:
					if ((event.text.unicode >= 48 && event.text.unicode <= 57) || (event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 97 && event.text.unicode <= 122))
						user_string.append(std::string(1, static_cast<char>(event.text.unicode)));
					break;
				}
			}
		}

		//Display what the user has written currently
		text.setString(user_string);

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	//Should not get here, keep it to be safe.
	return std::string();
}

void Editor::createUI(const std::vector<const sf::Image*> images, sf::Image * ui_image)
{
	//Don't take empty vectors
	if (images.empty())
		return;

	//Create ui_image to be big enough
	ui_image->create(images[0]->getSize().x * images.size() + 5 * (images.size() + 1), images[0]->getSize().y + 10, sf::Color(128, 128, 128));
	
	//Copy images to ui
	for (std::size_t i = 0; i < images.size(); i++)
	{
		ui_image->copy(*images[i], 5 * (i + 1) + i * images[0]->getSize().x, 5, sf::IntRect(0, 0, images[0]->getSize().x, images[0]->getSize().y));
	}
}

sf::VertexArray Editor::createSelected(std::vector<const sf::Image *> * block_images, const sf::Sprite * blocks_ui, const int num)
{
	//Create a red selection box
	//Mainly intended for block_ui
	sf::VertexArray selected(sf::LinesStrip);

	selected.append(sf::Vertex(sf::Vector2f(float(10 + (num - 1) * ((*block_images)[0]->getSize().x + 5) + window.getView().getCenter().x - (window.getSize().x / 2)),
		float(map.blocks[0].size() - blocks_ui->getTexture()->getSize().y) + window.getView().getCenter().y - (window.getSize().y / 2)), sf::Color::Red));
	selected.append(sf::Vertex(sf::Vector2f(float(10 + (num - 1) * ((*block_images)[0]->getSize().x + 5) + (*block_images)[0]->getSize().x + window.getView().getCenter().x - (window.getSize().x / 2)),
		float(map.blocks[0].size() - blocks_ui->getTexture()->getSize().y) + window.getView().getCenter().y - (window.getSize().y / 2)), sf::Color::Red));
	selected.append(sf::Vertex(sf::Vector2f(float(10 + (num - 1) * ((*block_images)[0]->getSize().x + 5) + (*block_images)[0]->getSize().x + window.getView().getCenter().x - (window.getSize().x / 2)),
		float((*block_images)[0]->getSize().y + map.blocks[0].size() - blocks_ui->getTexture()->getSize().y) + window.getView().getCenter().y - (window.getSize().y / 2)), sf::Color::Red));
	selected.append(sf::Vertex(sf::Vector2f(float(10 + (num - 1) * ((*block_images)[0]->getSize().x + 5) + window.getView().getCenter().x - (window.getSize().x / 2)),
		float((*block_images)[0]->getSize().y + map.blocks[0].size() - blocks_ui->getTexture()->getSize().y) + window.getView().getCenter().y - (window.getSize().y / 2)), sf::Color::Red));
	selected.append(sf::Vertex(sf::Vector2f(float(10 + (num - 1) * ((*block_images)[0]->getSize().x + 5) + window.getView().getCenter().x - (window.getSize().x / 2)),
		float(map.blocks[0].size() - blocks_ui->getTexture()->getSize().y) + window.getView().getCenter().y - (window.getSize().y / 2)), sf::Color::Red));

	return selected;
}


