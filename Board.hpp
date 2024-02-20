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

	sf::CircleShape marble;
	std::vector<sf::CircleShape> fallenMarbles;

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
	void initNodes();

	void drawBorder(sf::RenderWindow& window);
	void drawLevers(sf::RenderWindow& window);
	void drawNodes(sf::RenderWindow& window);

public:
	//constructor and destructor
	Board();
	~Board();

	//getters and setter
	int getNodesLength();

	Component* getNodeComponent(int index);

	sf::Vector2f getNodePosition(int index);

	sf::FloatRect getLeftLeverBounds();
	sf::FloatRect getRightLeverBounds();

	bool getNodeMainNode(int index);

	sf::CircleShape getMarble();
	sf::CircleShape getFallenMarbles(int index);

	void setNodeComponent(int index, Component* component);

	void setMarbleColour(sf::Color col);
	void setMarblePosition(sf::Vector2f pos);

	//public functions
	bool checkIfIntersectingNode(int index, sf::Vector2f coords);

	void drawBoard(sf::RenderWindow& window);
};

