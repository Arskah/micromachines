#include "Editor.h"

Editor::Editor(sf::RenderWindow & window, const std::map<Config::BlockType, sf::Image> & blocktextures) : window(window), max_brush_size(blocktextures.find(Config::BlockType::None)->second.getSize().x - 1)
{
	this->blocktextures = &blocktextures;
	brush_size = 75;

	//Build blocks to edit map from
	for (std::size_t i = 0; i < blocktextures.size(); i++)
	{
		const sf::Image * block_to_copy_from = &blocktextures.find(static_cast<Config::BlockType>(i))->second;
		const sf::Vector2u size = block_to_copy_from->getSize();

		sf::Image temp;
		temp.create(size.x * 3, size.y * 3);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				temp.copy(*block_to_copy_from, x * size.x, y * size.y, sf::IntRect(0, 0, size.x, size.y));
			}
		}

		block_textures_enlarged.push_back(temp);
	}

	//Build circle brush masks
	for (int i = 1; i < max_brush_size + 1; i++)
	{
		sf::Image circle_mask;

		circle_mask.create(blocktextures.find(Config::BlockType::None)->second.getSize().x, blocktextures.find(Config::BlockType::None)->second.getSize().y, sf::Color::Black);

		for (int x = 0; x < i; x++)
		{
			for (int y = 0; y < i; y++)
			{
				if (std::sqrt(std::pow((i - 1) / 2 - x, 2) + std::pow((i - 1) / 2 - y, 2)) >((i - 1) / 2))
				{
					circle_mask.setPixel(x, y, sf::Color::Red);
				}
			}
		}

		circle_mask.createMaskFromColor(sf::Color::Black);

		circle_brush_masks.push_back(circle_mask);
	}
}

static void loadingScreen(sf::RenderWindow & window)
{
	sf::Font font;
	font.loadFromFile("src/resources/arial.ttf");
	sf::Text text("Loading, please wait.", font, 42);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	sf::View temp = window.getView();
	window.setView(window.getDefaultView());
	text.setPosition(window.getView().getCenter());
	window.clear();
	window.draw(text);
	window.display();
	window.setView(temp);
}

void Editor::runEditor()
{
	//Go 1080p
	resolution.x = 1920;
	resolution.y = 1080;
	window.create(sf::VideoMode(unsigned int(resolution.x), unsigned int(resolution.y)), "Level Editor");

	initEditor();

	//Set editor_view to scale the whole map at once
	editor_view = window.getDefaultView();
	if (map.image.getSize().x * 9.f / 16.f > map.image.getSize().y)
		editor_view.setSize(sf::Vector2f(float(map.image.getSize().x), float(map.image.getSize().x * 9.f / 16.f)));
	else
		editor_view.setSize(sf::Vector2f(float(map.image.getSize().y * 16.f / 9.f), float(map.image.getSize().y)));
	editor_view.setCenter(float(map.image.getSize().x / 2), float(map.image.getSize().y / 2));
	window.setView(editor_view);

	//Minimap settings
	minimap_view.setCenter(float(map.image.getSize().x / 2), float(map.image.getSize().y / 2));
	minimap_view.setSize(sf::Vector2f(map.image.getSize()));
	minimap_view.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));

	//Block Toolbar UI
	sf::Image blocks_ui_image;
	std::vector<const sf::Image *> block_images;
	for (std::size_t i = 1; i < blocktextures->size(); i++)
	{
		block_images.push_back(&(blocktextures->find(static_cast<Config::BlockType>(i))->second));
	}
	createBlockUI(block_images, &blocks_ui_image);
	sf::Texture blocks_ui_tex;
	blocks_ui_tex.loadFromImage(blocks_ui_image);
	sf::Sprite blocks_ui;
	blocks_ui.setTexture(blocks_ui_tex);

	//Block Toolbar Selection Box
	sf::Image selected_image;
	sf::Texture selected_tex;
	sf::Sprite selected_sprite;

	//File Toolbar UI
	sf::Image file_ui_image;
	createFileUI(&file_ui_image);

	sf::Texture file_ui_tex;
	file_ui_tex.loadFromImage(file_ui_image);
	sf::Sprite file_ui;
	file_ui.setTexture(file_ui_tex);

	const std::string help_string =
		"F1 to open this Help menu\n"
		"F2 / N to create new Map\n"
		"F3 / S to save current Map\n"
		"F4 / L to load Map from file\n"
		"F5 / Esc to exit editor\n"
		"F6 / B to change to a box shaped brush\n"
		"F7 / C to change to a circle shaped brush\n"
		"R to reset view back to Map center\n"
		"E / Numpad+ to increase brush size\n"
		"Q / Numpad- to decrease brush size\n"
		"Number keys / mouse scroll to change block type shown in the bottom-left corner\n"
		"Middle mouse button to change view center position to current mouse position\n"
		"Left mouse button to draw\n";

	//Map update functions
	void (Editor::*updateImageFunc)(const sf::Vector2i, const Config::BlockType, const int) = &Editor::updateImageCircle;

	//What block the brush draws, set Ground to default on start
	Config::BlockType block_to_draw = Config::BlockType::Ground;

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
					//Close leveleditor and return back
				case sf::Keyboard::F5:
				case sf::Keyboard::Escape:
					//Return window back to original
					window.setView(window.getDefaultView());
					window.create(sf::VideoMode(1280, 720), "Micro Machines");
					return;
					break;
					//Show help
				case sf::Keyboard::F1:
					openTextbox("Help", BoxTypes::Display, help_string);
					break;
					//Create New Map
				case sf::Keyboard::F2:
				case sf::Keyboard::N:
					initMap();
					//Fix views
					if (map.image.getSize().x * 9.f / 16.f > map.image.getSize().y)
						editor_view.setSize(sf::Vector2f(float(map.image.getSize().x), float(map.image.getSize().x * 9.f / 16.f)));
					else
						editor_view.setSize(sf::Vector2f(float(map.image.getSize().y * 16.f / 9.f), float(map.image.getSize().y)));
					editor_view.setCenter(float(map.image.getSize().x / 2), float(map.image.getSize().y / 2));
					window.setView(editor_view);
					minimap_view.setCenter(float(map.image.getSize().x / 2), float(map.image.getSize().y / 2));
					minimap_view.setSize(sf::Vector2f(map.image.getSize()));
					break;
					//Save file
				case sf::Keyboard::F3:
				case sf::Keyboard::S:
					filename = openTextbox("Enter filename to save to");
					if (filename.size() != 0)
					{
						loadingScreen(window);
						filename.insert(0, "src/resources/");
						filename.append(".png");
						map.saveToImage(filename, *blocktextures);
					}
					break;
					//Load file
				case sf::Keyboard::F4:
				case sf::Keyboard::L:
					filename = openTextbox("Enter filename to load from");
					if (filename.size() != 0)
					{
						loadingScreen(window);
						filename.insert(0, "src/resources/");
						filename.append(".png");
						map.loadFromImage(filename, *blocktextures);
						//Fix views
						if (map.image.getSize().x * 9.f / 16.f > map.image.getSize().y)
							editor_view.setSize(sf::Vector2f(float(map.image.getSize().x), float(map.image.getSize().x * 9.f / 16.f)));
						else
							editor_view.setSize(sf::Vector2f(float(map.image.getSize().y * 16.f / 9.f), float(map.image.getSize().y)));
						editor_view.setCenter(float(map.image.getSize().x / 2), float(map.image.getSize().y / 2));
						window.setView(editor_view);
						minimap_view.setCenter(float(map.image.getSize().x / 2), float(map.image.getSize().y / 2));
						minimap_view.setSize(sf::Vector2f(map.image.getSize()));
					}
					break;
					//Reset view to original
				case sf::Keyboard::R:
					//Sets view to middle of map
					editor_view.setCenter(float(map.image.getSize().x / 2), float(map.image.getSize().y / 2));
					break;
					//From 'Numpad +' or 'E' increase brush size
				case sf::Keyboard::Add:
				case sf::Keyboard::E:
					if (brush_size < max_brush_size)
						brush_size += 2;
					break;
					//From 'Numpad -' or 'Q' decrease brush size
				case sf::Keyboard::Subtract:
				case sf::Keyboard::Q:
					if (brush_size > 2)
						brush_size -= 2;
					break;
					//From 'B' change brush type to box
				case sf::Keyboard::F6:
				case sf::Keyboard::B:
					updateImageFunc = &Editor::updateImageBox;
					break;
					//From 'C' change brush type to circle
				case sf::Keyboard::F7:
				case sf::Keyboard::C:
					updateImageFunc = &Editor::updateImageCircle;
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
					if ((event.key.code - 26) < int(blocktextures->size() - 1))
					{
						block_to_draw = static_cast<Config::BlockType>(event.key.code - 26);
					}
					break;
				default:
					break;
				}
				break;
				//Move view center to current mouse position by releasing scroll wheel on wanted position
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Button::Middle)
				{
					editor_view.setCenter(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), editor_view)));
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
						if ((static_cast<int>(block_to_draw) + 1) == int((blocktextures->size() - 1)))
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
							block_to_draw = static_cast<Config::BlockType>(blocktextures->size() - 2);
						}
						else
							//Go down one
							block_to_draw = static_cast<Config::BlockType>(static_cast<int>(block_to_draw) - 1);
					}
					//Restart timer
					scroll_timer.restart();
				}
				break;
			default:
				break;
			}
		}

		//Faster here than in event loop
		//Capture clicked position
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i location_i = sf::Mouse::getPosition(window);
			location_i = sf::Vector2i(window.mapPixelToCoords(location_i, editor_view));
			if (location_i.x >= 0 && location_i.y >= 0)
			{
				//Capture current mouse spot and convert to coords in world
				(this->*updateImageFunc)(sf::Vector2i(location_i), block_to_draw, brush_size);
			}

			//Place finish line if drawn over
			placeFinishLine();
		}

		//Load new image to map for displaying
		//Load image to texture
		map.texture.loadFromImage(map.image);
		//Load texture to sprite
		map.drawable.setTexture(map.texture);

		//Set default view to window just in case
		window.setView(editor_view);

		//Clear window
		window.clear();

		//Draw Map
		window.draw((*map.getDrawable()));

		//Draw interfaces
		//Block selection Toolbar
		blocks_ui.setScale(window.getView().getSize().x / 6000.f, window.getView().getSize().y / 3525.f);
		blocks_ui.setPosition(5.f + window.getView().getCenter().x - window.getView().getSize().x / 2,
			window.getView().getCenter().y + window.getView().getSize().y / 2 - blocks_ui_tex.getSize().y * window.getView().getSize().y / 3525.f - 5.f);
		window.draw(blocks_ui);
		//Selection box for blocks_ui
		createBlockUISelection(&selected_image, static_cast<int>(block_to_draw), blocktextures->size());
		selected_tex.loadFromImage(selected_image);
		selected_sprite.setTexture(selected_tex);
		selected_sprite.setScale(window.getView().getSize().x / 6000.f, window.getView().getSize().y / 3525.f);
		selected_sprite.setPosition(5.f + window.getView().getCenter().x - window.getView().getSize().x / 2,
			window.getView().getCenter().y + window.getView().getSize().y / 2 - blocks_ui_tex.getSize().y * window.getView().getSize().y / 3525.f - 5.f);
		window.draw(selected_sprite);
		//File operations toolbar
		file_ui.setScale(window.getView().getSize().x / 4000.f, window.getView().getSize().y / 2250.f);
		file_ui.setPosition(5.f + window.getView().getCenter().x - window.getView().getSize().x / 2,
			window.getView().getCenter().y - window.getView().getSize().y / 2 + 5.f);
		window.draw(file_ui);

		//Minimap
		//Draw minimap last because the view changes!
		//Grey Border around minimap
		sf::RectangleShape minimap_border(sf::Vector2f(window.getView().getSize().x * 0.15f + 7, window.getView().getSize().y * 0.15f + 7));
		minimap_border.setFillColor(sf::Color(sf::Uint8(63), sf::Uint8(63), sf::Uint8(63)));
		minimap_border.setPosition(window.getView().getCenter().x + window.getView().getSize().x / 2 - window.getView().getSize().x * 0.15f - 7,
			window.getView().getCenter().y - window.getView().getSize().y / 2);
		window.draw(minimap_border);

		//Minimap in itself
		sf::VertexArray boxerino = createMinimapViewBorder();
		window.setView(minimap_view);
		window.draw((*map.getDrawable()));
		//View Border to indicate position being seen
		window.draw(boxerino);

		//Display everything
		window.display();
	}
	//If we somehow get exited here, return window to normal
	window.setView(window.getDefaultView());
	window.create(sf::VideoMode(1280, 720), "Micro Machines");
}

void Editor::initEditor()
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
}

void Editor::initMap()
{
	//Init map
	map = Map();

	//Init sizes to ask
	sf::Vector2u size;
	size.x = 0;
	size.y = 0;

	//Ask map size from user
	std::string size_x = "";
	while (size.x < 12)
	{
		size_x = "";
		while (size_x == "")
			size_x = openTextbox("Please enter map size (min 12, max 30)", BoxTypes::Number);
		size.x = std::stoi(size_x);
	}

	//Maps are square, so copy y-value from x
	size.x *= 256;
	size.y = size.x;

	//Give map size
	map.size = size;

	//Ask for base block
	std::string base = openTextbox("Do you want a base block for the map? Write block type or leave empty.", BoxTypes::Text);

	//Show loading screen while building map
	//Editor will refresh screen when running
	loadingScreen(window);

	//Change inputted string to lowercase
	std::transform(base.begin(), base.end(), base.begin(), ::tolower);

	//Specify base block type
	Config::BlockType base_block_type = Config::BlockType::Ground;

	//If we received a desired BlockTypelai
	if (Config::StringToBlockTypeMap.find(base) != Config::StringToBlockTypeMap.end())
	{
		base_block_type = Config::StringToBlockTypeMap.find(base)->second;
	}

	map.base_block = base_block_type;

	//Create an image of the map
	//Insert base blocks to fill map
	map.blockrow.assign(size.x * size.y, base_block_type);

	//Create image to correct size
	map.image.create(size.x, size.y, sf::Color::Red);

	//Create Block Image
	map.block_image.create(size.x, size.y, sf::Color(sf::Uint32((static_cast<int>(base_block_type) << 8) + 255 + (255 << 16) + (255 << 24))));

	//Load drawable image from Block Image
	map.createImageFromBlockImage(*blocktextures);

	//Place initial finish line
	placeFinishLine();
}

std::string Editor::openTextbox(const std::string &box_name, const BoxTypes box_type, const std::string &text_to_display)
{
	sf::Vector2i size(0, 0);

	if (box_type != BoxTypes::Display)
	{
		size.x = 400;
		size.y = 24;
	}
	else
	{
		size.x = 700;
		size.y = 24 + 16 * (2 + std::count(text_to_display.begin(), text_to_display.end(), '\n'));
	}

	sf::RenderWindow window(sf::VideoMode(size.x, size.y), box_name, sf::Style::Titlebar);
	window.requestFocus();

	//Textbox
	sf::RectangleShape shape(sf::Vector2f(float(size.x - 4), float(size.y - 4)));;
	shape.setFillColor(sf::Color::White);
	shape.setPosition(2, 2);

	//Text
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text user_text;
	user_text.setFont(font);
	user_text.setColor(sf::Color::Black);
	user_text.setCharacterSize(14);
	user_text.setPosition(4, 2);

	sf::Text display_text;
	display_text.setFont(font);
	display_text.setColor(sf::Color::Black);
	display_text.setCharacterSize(14);
	display_text.setPosition(4, 2);

	std::string display_text_string = text_to_display;

	display_text_string.append("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPress Enter to continue.");

	display_text.setString(display_text_string);

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
				if (event.key.code == sf::Keyboard::Return && (user_string.size() > 0 || box_type == BoxTypes::Display))
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
				default:
					break;
				}
			default:
				break;
			}
		}

		//Display what the user has written currently
		user_text.setString(user_string);

		window.clear();
		window.draw(shape);
		if (box_type == BoxTypes::Display)
			window.draw(display_text);
		else
			window.draw(user_text);
		window.display();
	}

	//Should not get here, keep it to be safe.
	return std::string();
}

void Editor::createBlockUI(const std::vector<const sf::Image*> images, sf::Image * ui_image)
{
	//Don't take empty vectors
	if (images.empty())
		return;

	int imageSize = images.size() - 1;

	//Create ui_image to be big enough
	ui_image->create(images[0]->getSize().x * imageSize + 5 * (imageSize + 1), images[0]->getSize().y + 10, sf::Color(sf::Uint8(63), sf::Uint8(63), sf::Uint8(63)));
	sf::Image temp;
	temp.create(images[0]->getSize().x * imageSize + 5 * (imageSize + 1), images[0]->getSize().y + 10, sf::Color(sf::Uint8(128), sf::Uint8(128), sf::Uint8(128)));
	ui_image->copy(temp, 2, 2, sf::IntRect(0, 0,
		images[0]->getSize().x * imageSize + 5 * (imageSize + 1) - 4,
		images[0]->getSize().y + 6));

	//Copy images to ui
	for (int i = 0; i < imageSize; i++)
	{
		ui_image->copy(*images[i], 5 * (i + 1) + i * images[0]->getSize().x, 5, sf::IntRect(0, 0, images[0]->getSize().x, images[0]->getSize().y));
	}
}

void Editor::createBlockUISelection(sf::Image * const selected_image, const int num, const int maxnum)
{
	selected_image->create(256 * maxnum + 5 * (maxnum + 1), 256 + 10, sf::Color::Black);
	selected_image->createMaskFromColor(sf::Color::Black);

	sf::Image red;
	red.create(256, 256, sf::Color::Red);

	sf::Image black;
	black.create(250, 250, sf::Color::Black);

	red.copy(black, 3, 3, sf::IntRect(0, 0, 250, 250));
	red.createMaskFromColor(sf::Color::Black);

	selected_image->copy(red, 5 * num + (num - 1) * 256, 5, sf::IntRect(0, 0, 256, 256), true);
}

void Editor::createFileUI(sf::Image * file_ui_image)
{
	file_ui_image->create(7 * (100 + 5) + 5, 100 + 10, sf::Color(sf::Uint8(63), sf::Uint8(63), sf::Uint8(63)));
	sf::Image new_icon;
	new_icon.loadFromFile("src/resources/editor/new_icon.png");
	sf::Image close_icon;
	close_icon.loadFromFile("src/resources/editor/close_icon.png");
	sf::Image save_icon;
	save_icon.loadFromFile("src/resources/editor/save_icon.png");
	sf::Image open_icon;
	open_icon.loadFromFile("src/resources/editor/open_icon.png");
	sf::Image help_icon;
	help_icon.loadFromFile("src/resources/editor/help_icon.png");
	sf::Image box_icon;
	box_icon.loadFromFile("src/resources/editor/box_icon.png");
	sf::Image circle_icon;
	circle_icon.loadFromFile("src/resources/editor/circle_icon.png");

	file_ui_image->copy(help_icon, 5, 5, sf::IntRect(0, 0, 100, 100));
	file_ui_image->copy(new_icon, 110, 5, sf::IntRect(0, 0, 100, 100));
	file_ui_image->copy(save_icon, 215, 5, sf::IntRect(0, 0, 100, 100));
	file_ui_image->copy(open_icon, 320, 5, sf::IntRect(0, 0, 100, 100));
	file_ui_image->copy(close_icon, 425, 5, sf::IntRect(0, 0, 100, 100));
	file_ui_image->copy(box_icon, 530, 5, sf::IntRect(0, 0, 100, 100));
	file_ui_image->copy(circle_icon, 635, 5, sf::IntRect(0, 0, 100, 100));
}

sf::VertexArray Editor::createMinimapViewBorder()
{
	//Create a red box to be viewed on minimap
	//Mainly intended for block_ui
	sf::VertexArray box(sf::Quads);

	//box.append(window.getView().getCenter());

	//UP LEFT - RIGHT
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));


	//UP RIGHT - DOWN RIGHT
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));


	//DOWN RIGHT - LEFT
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x + window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));

	//DOWN LEFT - UP LEFT
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 - 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y - window.getView().getSize().y / 2 - 12)),
		sf::Color::Red));
	box.append(sf::Vertex(sf::Vector2f(
		float(window.getView().getCenter().x - window.getView().getSize().x / 2 + 12),
		float(window.getView().getCenter().y + window.getView().getSize().y / 2 + 12)),
		sf::Color::Red));

	return box;
}

void Editor::placeFinishLine()
{
	sf::Vector2i location;
	location.x = map.size.x / 2;
	location.y = map.size.y / 2;
	updateImageBox(location - sf::Vector2i(0, 255) + sf::Vector2i(0, 127), Config::BlockType::Checkerboard, 255);
	updateImageBox(location + sf::Vector2i(0, 127), Config::BlockType::Checkerboard, 255);
}

void Editor::updateImageBox(const sf::Vector2i location, const Config::BlockType type, const int brush_size)
{
	//If fully out do nothing
	if (location.x + brush_size / 2 <= 0)
		return;
	if (location.y + brush_size / 2 <= 0)
		return;

	sf::Vector2u size = block_textures_enlarged[static_cast<int>(type)].getSize();

	//Copy wanted piece properly to the map image
	map.image.copy(block_textures_enlarged[static_cast<int>(type)],
		(location.x - (brush_size - 1) / 2 < 0) ? (0) : (location.x - (brush_size - 1) / 2),
		(location.y - (brush_size - 1) / 2 < 0) ? (0) : (location.y - (brush_size - 1) / 2),
		sf::IntRect(
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? ((size.x / 2) + brush_size / 2) : (brush_size / 2)) : (location.x % (size.x / 2)),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? ((size.y / 2) + brush_size / 2) : (brush_size / 2)) : (location.y % (size.y / 2)),
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (brush_size / 2 - std::abs(location.x)) : (brush_size / 2 + location.x)) : (brush_size),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (brush_size / 2 - std::abs(location.y)) : (brush_size / 2 + location.y)) : (brush_size)));


	//Change wanted blocks to the block image
	sf::Image temp_block;
	temp_block.create(size.x, size.y, sf::Color(sf::Uint32((static_cast<int>(type) << 8) + 255 + (255 << 16) + (255 << 24))));

	map.block_image.copy(temp_block,
		(location.x - (brush_size - 1) / 2 < 0) ? (0) : (location.x - (brush_size - 1) / 2),
		(location.y - (brush_size - 1) / 2 < 0) ? (0) : (location.y - (brush_size - 1) / 2),
		sf::IntRect(
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? ((size.x / 2) + brush_size / 2) : (brush_size / 2)) : (location.x % (size.x / 2)),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? ((size.y / 2) + brush_size / 2) : (brush_size / 2)) : (location.y % (size.y / 2)),
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (brush_size / 2 - std::abs(location.x)) : (brush_size / 2 + location.x)) : (brush_size),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (brush_size / 2 - std::abs(location.y)) : (brush_size / 2 + location.y)) : (brush_size)));
}

void Editor::updateImageCircle(sf::Vector2i location, const Config::BlockType type, const int brush_size)
{
	//If fully out do nothing
	if (location.x + brush_size / 2 <= 0)
		return;
	if (location.y + brush_size / 2 <= 0)
		return;

	//If partly out draw partly
	//If inside draw normally --- combined with above condition inside image copy function with conditionals

	sf::Vector2u size = block_textures_enlarged[static_cast<int>(type)].getSize();

	//Establish a medium to copy correctly from
	sf::Image temp;
	temp.create(size.x, size.y);
	temp.copy(block_textures_enlarged[static_cast<int>(type)], 0, 0, sf::IntRect(0, 0, size.x, size.y));
	temp.copy(circle_brush_masks[brush_size - 1], ((location.x >= 0) ? (location.x % (size.x / 2)) : ((size.x / 2) - std::abs(location.x))),
		((location.y >= 0) ? (location.y % (size.y / 2)) : ((size.y / 2) - std::abs(location.y))), sf::IntRect(0, 0, brush_size, brush_size), true);
	temp.createMaskFromColor(sf::Color::Red);

	//Copy wanted piece properly to the map image
	map.image.copy(temp,
		(location.x - (brush_size - 1) / 2 < 0) ? (0) : (location.x - (brush_size - 1) / 2),
		(location.y - (brush_size - 1) / 2 < 0) ? (0) : (location.y - (brush_size - 1) / 2),
		sf::IntRect(
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? ((size.x / 2) + brush_size / 2) : (brush_size / 2)) : (location.x % (size.x / 2)),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? ((size.y / 2) + brush_size / 2) : (brush_size / 2)) : (location.y % (size.y / 2)),
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (brush_size / 2 - std::abs(location.x)) : (brush_size / 2 + location.x)) : (brush_size),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (brush_size / 2 - std::abs(location.y)) : (brush_size / 2 + location.y)) : (brush_size)),
		true);

	//Change blocks using the same type of function as above
	sf::Image temp_block;
	temp_block.create(size.x, size.y, sf::Color(sf::Uint32((static_cast<int>(type) << 8) + 255 + (255 << 16) + (255 << 24))));
	temp_block.copy(circle_brush_masks[brush_size - 1], ((location.x >= 0) ? (location.x % (size.x / 2)) : ((size.x / 2) - std::abs(location.x))),
		((location.y >= 0) ? (location.y % (size.y / 2)) : ((size.y / 2) - std::abs(location.y))), sf::IntRect(0, 0, brush_size, brush_size), true);
	temp_block.createMaskFromColor(sf::Color::Red);

	//Change wanted blocks to the block image
	map.block_image.copy(temp_block,
		(location.x - (brush_size - 1) / 2 < 0) ? (0) : (location.x - (brush_size - 1) / 2),
		(location.y - (brush_size - 1) / 2 < 0) ? (0) : (location.y - (brush_size - 1) / 2),
		sf::IntRect(
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? ((size.x / 2) + brush_size / 2) : (brush_size / 2)) : (location.x % (size.x / 2)),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? ((size.y / 2) + brush_size / 2) : (brush_size / 2)) : (location.y % (size.y / 2)),
			(location.x - (brush_size - 1) / 2 < 0) ? ((location.x < 0) ? (brush_size / 2 - std::abs(location.x)) : (brush_size / 2 + location.x)) : (brush_size),
			(location.y - (brush_size - 1) / 2 < 0) ? ((location.y < 0) ? (brush_size / 2 - std::abs(location.y)) : (brush_size / 2 + location.y)) : (brush_size)),
		true);
}