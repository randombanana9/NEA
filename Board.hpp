#pragma once

#include "source.hpp"

class Node;
class Component;
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

	bool checkValidIndexNodes(int index);
public:
	//constructor and destructor
	Board();
	~Board();

	//getters and setter
	int getNodesLength();
	Component* getNodeComponent(int index);
	void setNodeComponent(int index, Component* component);
	sf::Vector2f getNodePosition(int index);


	//public functions
	bool checkIfIntersectingNode(int index, sf::Vector2f coords);
	void drawBoard(sf::RenderWindow& window);
};

