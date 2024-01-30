#pragma once

#include "source.hpp"

class Board;
class Component;
class Graph;

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
	sf::Text partsMenuText[7];
	sf::RectangleShape infoBox;

	std::vector<Component*> components;
	
	std::vector<Graph*> graph;
	Graph* leftRoot;
	Graph* rightRoot;
	
	Board* board;
	/*
	marbles
	*/

	//logic
	bool mouseHeld;
	bool click;
	Component* heldComponent;
	bool facingRight;

	//Private Functions
	void initWindow();
	void initObjects();
	void initLogic();
	void initFonts();
	void initText();

	void pollEvents();
	void updateMousePos();

	void updateComponents();
	void updatePartsMenu();

	void deleteHeldComponent();

	//render functions
	void drawObjects();
	void drawText();
	void drawHeld();

public:
	//Constructor and Destructor
	Game();
	~Game();

	const bool running() const;

	//public functions
	void update();
	void render();
};

