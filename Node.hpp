#pragma once

#include "source.hpp"

class Node {
private:
	sf::RectangleShape sprite; //TEMP - will be a sprite type later
	bool mainNode; //for whether all components can be placed on the node, or just gears
	sf::Vector2f pos;

	void initVars(bool main, sf::Vector2f position);
	void initSprite();
public:
	//constructor
	Node(bool main, sf::Vector2f position);

	//getter
	sf::RectangleShape getSprite();
};

