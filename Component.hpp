#pragma once

#include "source.hpp"

class Node;

class Component { 
protected: //private members cannot be inherited so protected members are used in the parent class
	sf::RectangleShape sprite;

	Node* connectedNode; //Attribute used to store which node the component is connected to, also doubles as a check for whether the component is connected to a node
	//bool onButton; TODO: Attribute used to store whether the component is on the button
	bool held; //Attribute used to store whether the component is beinghekd by the user
	bool mainComponent; //Attribute used when placing a component to see if it can only go on main nodes
	//bool originalFacingRight; TODO: used when resetting the board, to put component back in original state
	bool facingRight; //Attribute used with certain gears for deciding which side the marble gets dropped on
	bool isAGear; //Atribute used in the gear update search, means only GearBit and Bit get updated.

	void virtual initSprite(sf::Color colour, sf::Vector2f position);
	void virtual initLogic(bool faceRight);
public:

	//getters
	sf::Vector2f getPos();
	bool getHeld();
	bool getMainComponent();
	bool getFacingRight();
	bool isGear();

	sf::RectangleShape getSprite();

	virtual int checkDropSide(int fallSide);

	void highlight();
	void unhighlight();
	void moveTo(sf::Vector2f pos);
	void toggleFacingRight();
};

class Ramp : public Component { //Inheritance here!!!!
	sf::Color colour = sf::Color::Green;

	sf::Vector2f position;

public:
	Ramp(bool faceRight);

	virtual int checkDropSide(int fallSide);
};

class Crossover : public Component { //Inheritance here!!!!
	sf::Color colour = sf::Color::Yellow;

	sf::Vector2f position;

public:
	Crossover(bool faceRight);

	virtual int checkDropSide(int fallSide);
};

class Interceptor : public Component { //Inheritance here!!!!
	sf::Color colour = sf::Color::Black;

	sf::Vector2f position;

public:
	Interceptor(bool faceRight);

	virtual int checkDropSide(int fallSide);
};

class Bit : public Component { //Inheritance here!!!!
	sf::Color colour = sf::Color::Blue;

	sf::Vector2f position;

public:
	Bit(bool faceRight);

	virtual int checkDropSide(int fallSide);
};

class GearBit : public Component { //Inheritance here!!!!
	sf::Color colour = sf::Color::Magenta;

	sf::Vector2f position;

	void virtual initLogic(bool main);
public:

	GearBit(bool faceRight);

	virtual int checkDropSide(int fallSide);
	void flip();
};

class Gear : public Component { //Inheritance here!!!!
	sf::Color colour = sf::Color::Red;

	sf::Vector2f position;

	bool mainComponent = false;

	void virtual initLogic(bool main, bool faceRight);
public:

	Gear(bool faceRight);
};