#pragma once

#include "Component.hpp"

void Component::initSprite(sf::Vector2f position) { //Initialises the sprite of the component
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(1.f / 15, 1.f / 15);

	this->offset = 0.f;
	if (!this->facingRight) {
		this->sprite.scale(sf::Vector2f(-1.f, 1.f));
		this->offset = 48.f;
	}

	this->width = this->sprite.getTexture()->getSize().x / 15;
	float xPos = position.x - this->width / 2 + this->offset;
	float yPos = position.y - this->width / 2;
	this->sprite.setPosition(sf::Vector2f(xPos, yPos));
}

void Component::initTexture(sf::Texture txtr) { //Initialises the texture to be used by the component
	this->texture = txtr;
}

void Component::initLogic(bool faceRight) { //Initialises the logic which dictates how the component behaves
	this->connectedNode = NULL;
	this->held = false;
	this->mainComponent = true;
	this->facingRight = faceRight;
	this->isAGear = false;
	this->changedOrientation = false;
}

sf::Vector2f Component::getPos() { //Returns the position of the centre of the component
	float xPos = this->sprite.getPosition().x + this->width / 2 - this->offset;
	float yPos = this->sprite.getPosition().y + this->width / 2;
	return sf::Vector2f(xPos, yPos);
}

bool Component::getHeld() { //Returns if the component is being held
	return this->held;
}

bool Component::getFacingRight() { //Return if the component is facing to the right
	return this->facingRight;
}

void Component::toggleFacingRight() { //Switches the direction faced by the component
	this->facingRight = !this->facingRight;
	this->changedOrientation = true;
}

void Component::updateOrientation() { //Changes the visual representation of the components orientation to represent the direction the component is facing
	sf::Vector2f position = this->getPos();
	if (this->changedOrientation) {
		this->sprite.scale(sf::Vector2f(-1.f, 1.f));
	}

	this->offset = 0.f;
	if (!this->facingRight) {
		this->offset = 48.f;
	}
	this->moveTo(position);
	this->changedOrientation = false;
}

void Component::moveTo(sf::Vector2f pos) { //Moves the component to a given position
	float xPos = pos.x - this->width / 2 + this->offset;
	float yPos = pos.y - this->width / 2;
	this->sprite.setPosition(sf::Vector2f(xPos, yPos));
}

sf::Sprite Component::getSprite() { //Returns the sprite object used by the component
	return this->sprite;
}

int Component::checkDropSide(int fallSide) { // Default function for a component. Used by children to return which side the marble sould be dropped to
	return 0;
}

bool Component::isGear() { //Returns whether the current component is a type of gear
	return this->isAGear;
}

bool Component::getMainComponent() { //Returns whether the component is a main component
	return this->mainComponent;
}

Ramp::Ramp(bool faceRight, sf::Texture& txtr) { //Constructor for ramp component, calls initialisation functions
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Ramp::checkDropSide(int fallSide) { //Overridden function
	if (this->facingRight) {
		return 1;
	}
	return 0;
}

Crossover::Crossover(bool faceRight, sf::Texture& txtr) { //Constructor for crossover component, calls initialisation functions
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Crossover::checkDropSide(int fallSide) { //Overridden function	
	if (fallSide == 0) {
		return 1;
	}
	return 0;
}

Interceptor::Interceptor(bool faceRight, sf::Texture& txtr) { //Constructor for interceptor component, calls initialisation functions
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Interceptor::checkDropSide(int fallSide) { //Overridden function
	return 6; //value of 6 means the marble has been intercepted
}

Bit::Bit(bool faceRight, sf::Texture& txtr) { //Constructor for bit component, calls initialisation functions
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Bit::checkDropSide(int fallSide) { //Overridden function
	this->toggleFacingRight();
	if (!this->facingRight) {
		return 3; //Means that marble is to drop on right, and this was caused by a bit
	}
	return 2; //Means the marble is to drop on the left, and this was caused by a bit
}

void GearBit::initLogic(bool faceRight) { //Overridden function
	this->connectedNode = NULL;
	this->held = false;
	this->mainComponent = true;
	this->facingRight = faceRight;
	this->isAGear = true;
}

void GearBit::flip() { //Flips the orientation of the gear bit component
	this->toggleFacingRight();
	this->updateOrientation();
}

GearBit::GearBit(bool faceRight, sf::Texture& txtr) { //Constructor for the gear bit component. Calls initialisation functions
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int GearBit::checkDropSide(int fallSide) { //Overridden function
	this->toggleFacingRight();
	if (!this->facingRight) {
		return 5; //Means the marble is to be dropped on the right, and this was caused by a gear bit
	}
	return 4; //Means the marble is to be dropped on the left, and this was caused by a gear bit
}

void Gear::initLogic(bool main, bool faceRight) { //Overridden function
	this->connectedNode = NULL;
	this->held = false;
	this->mainComponent = main;
	this->isAGear = true;
	this->facingRight = faceRight;
}

Gear::Gear(bool faceRight, sf::Texture& txtr) { //Constructor for gear component. Calls initialisation functions
	this->initLogic(this->mainComponent, faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Gear::checkDropSide(int fallSide) { //Overridden function
	return 7; //Means that the marble has fallen onto a gear, which is illegal, and the simulation should be aborted
}