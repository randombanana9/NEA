#pragma once

#include "Node.hpp"

void Node::initVars(bool main, sf::Vector2f position) { //Initialises the variables used by the node object
	this->mainNode = main;
	this->pos = position;
}

void Node::initSprite() { //Initialises the rectangle used as a graphical representation of the node.
	this->sprite.setSize(sf::Vector2f(52.f, 52.f));
	this->sprite.setOrigin(sf::Vector2f(26.f, 26.f));
	this->sprite.setPosition(this->pos);
	if (this->mainNode) {
		this->sprite.setFillColor(sf::Color(180, 180, 180, 255));
	}
	else {
		this->sprite.setFillColor(sf::Color::White);
	}
	this->sprite.setOutlineColor(sf::Color::Black);
	this->sprite.setOutlineThickness(1.f);
}

Node::Node(bool main, sf::Vector2f position) { //Constructor, calls initialisation function
	this->initVars(main, position);
	this->initSprite();
}

sf::RectangleShape Node::getSprite() { //Returns the sprite for the node
	return this->sprite;
}

Component* Node::getComponent() { //Returns the component connected to the node
	return this->component;
}

bool Node::getMainNode() { //Returns if the node is a main node
	return this->mainNode;
}

void Node::setComponent(Component* newComp) { //Sets the component stored on this node
	this->component = newComp;
}


