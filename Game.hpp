#pragma once

#include "source.hpp"

class Board;
class Component;
class Graph;

class Game {
private:
	sf::Sprite test;

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

	//Textures
	sf::Texture rampTexture;
	sf::Texture crossoverTexture;
	sf::Texture interceptorTexture;
	sf::Texture bitTexture;
	sf::Texture gearBitTexture;
	sf::Texture gearTexture;

	//Game objects
	sf::RectangleShape partsMenu[8];
	sf::Text partsMenuText[7];
	sf::RectangleShape infoBox;
	sf::RectangleShape runButton;
	sf::Text runButtonText;

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
	bool placementMode;
	bool startedSimulation;
	Graph* currentNode;
	int framesSinceSimUpdate;
	int dropSide;
	bool intercepted;
	bool stopped;
	int steps;
	const int hopperStoredOriginal = 8; //The original amount of marbles to be stored in each hopper
	int leftHopperStoredPreRun;
	int rightHopperStoredPreRun;
	int leftHopperStored;
	int rightHopperStored;
	bool updateGears;
	std::vector<int> searchedNodes;

	//Private Functions
	void initWindow();
	void initObjects();
	void initLogic();
	void initTextures();
	void initFonts();
	void initText();

	void pollEvents();
	void updateMousePos();

	void updateComponents();
	void updatePartsMenu();

	void updateButtons();
	void updateLevers();

	void updateSimulation();
	void endSim();

	void placeComponent(int index);
	void deleteHeldComponent();
	void updateConnectedGears(Component* currentComp, bool newFacingRight);

	void setInfo(std::string newString);

	//render functions
	void drawObjects();
	void drawText();
	void drawHeld();

	void drawMarbles();

public:
	//Constructor and Destructor
	Game();
	~Game();

	const bool running() const;

	//public functions
	void update();
	void render();
};

