#pragma once

#include "source.hpp"

class Node;
//class Graph;

class Board {
private:
	//graphical components
	sf::RectangleShape border;
	sf::RectangleShape leftLever;
	sf::RectangleShape rightLever;
	sf::RectangleShape blueHopper[3];
	sf::RectangleShape redHopper[3];

	Node* node;
	std::vector<Node*> nodes;

	const float width = 800.f;
	const float height = 860.f;

	const float xPos = 200.f;
	const float yPos = 10.f;

	int boardSize = 11;
	bool* board;

	//private functions
	void initObjects();
	void initBorder();
	void initLevers();
	void initHoppers();
	void initNodes();

	void drawBorder(sf::RenderWindow& window);
	void drawLevers(sf::RenderWindow& window);
	void drawHoppers(sf::RenderWindow& window);
	void drawNodes(sf::RenderWindow& window);

public:
	//constructor and destructor
	Board();
	~Board();

	//public functions
	void drawBoard(sf::RenderWindow& window);
};

