#pragma once

#include "source.hpp"

class Component;

class Node {
private:
	sf::RectangleShape sprite; 
	bool mainNode; //for whether all components can be placed on the node, or just gears
	sf::Vector2f pos;

	Component* component;

	void initVars(bool main, sf::Vector2f position);
	void initSprite();
public:
	//constructor
	Node(bool main, sf::Vector2f position);

	//getters
	sf::RectangleShape getSprite();
	Component* getComponent();
	bool getMainNode();

	//setters
	void setComponent(Component* newComp);
};

