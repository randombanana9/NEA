#pragma once

#include "source.hpp"

class Node;

class Component {
protected: //private members cannot be inherited so protected members are used in the parent class
	sf::RectangleShape sprite;

	Node* connectedNode;
	bool onButton;
	bool held;
	bool mainComponent;
	bool facingRight;

	void virtual initSprite(sf::Color colour, sf::Vector2f position);
	void virtual initLogic(bool faceRight);
public:
	//getters
	sf::Vector2f getPos();
	bool getHeld();
	bool getMainComponent();
	bool getFacingRight();

	virtual sf::RectangleShape getSprite();


	void highlight();
	void unhighlight();
	void moveTo(sf::Vector2f pos);
	void toggleFacingRight();
};

class Ramp : public Component {
	sf::Color colour = sf::Color::Green;

	sf::Vector2f position;

public:
	Ramp(bool faceRight);
};

class Crossover : public Component {
	sf::Color colour = sf::Color::Yellow;

	sf::Vector2f position;

public:
	Crossover(bool faceRight);
};

class Interceptor : public Component {
	sf::Color colour = sf::Color::Black;

	sf::Vector2f position;

public:
	Interceptor(bool faceRight);
};

class Bit : public Component {
	sf::Color colour = sf::Color::Blue;

	sf::Vector2f position;

public:
	Bit(bool faceRight);
};

class GearBit : public Component {
	sf::Color colour = sf::Color::Magenta;

	sf::Vector2f position;

public:
	GearBit(bool faceRight);
};

class Gear : public Component {
	sf::Color colour = sf::Color::Red;

	sf::Vector2f position;

	bool mainComponent = false;

	void virtual initLogic(bool main);
public:
	Gear();
};