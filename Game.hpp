#pragma once

#include "source.hpp"

class Board;

class Game {
private:
	//private variables related to the window
	sf::ContextSettings settings;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow; //position of the mouse relative to the window
	sf::Vector2f mousePosView; //position of the mouse relative to the view

	//Resources
	sf::Font font;

	//Text
	sf::Text infoText;

	//Game objects
	sf::RectangleShape partsMenu[8];
	sf::RectangleShape infoBox;
	/*
	buttons
	components
	the graph?
	info box
	*/
	Board* board;
	/*
	marbles
	*/

	//logic
	bool mouseHeld;

	//Private Functions
	void initWindow();
	void initObjects();
	void initLogic();
	void initFonts();
	void initText();

	void pollEvents();
	void updateMousePos();



	//render functions
	void drawObjects();
	void drawText();

public:
	//Constructor and Destructor
	Game();
	~Game();

	const bool running() const;

	//public functions
	void update();
	void render();
};

