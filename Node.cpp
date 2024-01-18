#pragma once

#include "Node.hpp"

void Node::initVars(bool main, sf::Vector2f position) {
	this->mainNode = main;
	this->pos = position;
}

void Node::initSprite() {
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

Node::Node(bool main, sf::Vector2f position) {
	this->initVars(main, position);
	this->initSprite();
}

sf::RectangleShape Node::getSprite() {
	return this->sprite;
}

Component* Node::getComponent() {
	return this->component;
}

void Node::setComponent(Component* newComp) {
	this->component = newComp;
	std::cout << "Placed component" << this->component << "\n";
}


