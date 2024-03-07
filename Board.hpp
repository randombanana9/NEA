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

	sf::RectangleShape leftHopper[3]; //Decrement button, counter, increment button
	sf::RectangleShape rightHopper[3]; //Decrement button, counter, increment button

	sf::Text leftHopperTxt[3];
	sf::Text rightHopperTxt[3];

	sf::CircleShape leftHopperMarble;
	sf::CircleShape rightHopperMarble;

	sf::CircleShape marble;
	std::vector<sf::CircleShape> fallenMarbles;

	Node* node;
	std::vector<Node*> nodes;

	sf::Font& font;

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
	void initFont(sf::Font& font);
	void initHoppers();
	void initNodes();

	void drawBorder(sf::RenderWindow& window);
	void drawLevers(sf::RenderWindow& window);
	void drawHoppers(sf::RenderWindow& window);
	void drawNodes(sf::RenderWindow& window);
	void drawFallen(sf::RenderWindow& window);

public:
	//constructor and destructor
	Board(sf::Font& font);
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

	void setLeftHopperTxt(std::string newStr);
	void setRightHopperTxt(std::string newStr);

	void clearFallen();
	void pushFallen();

	bool checkIfIntersectingNode(int index, sf::Vector2f coords);
	bool checkIfIntersectingButton(bool right, int index, sf::Vector2f coords);

	void drawBoard(sf::RenderWindow& window);
};

