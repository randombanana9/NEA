#pragma once

#include "Component.hpp"

void Component::initSprite(sf::Color colour, sf::Vector2f position) {
	this->sprite.setSize(sf::Vector2f(20.f, 20.f));
	this->sprite.setOrigin(sf::Vector2f(10.f, 10.f));
	this->sprite.setFillColor(colour);
	this->sprite.setPosition(position);
	this->sprite.setOutlineThickness(1.f);
	this->sprite.setOutlineColor(sf::Color::Black);
}

void Component::initLogic(bool faceRight) {
	this->connectedNode = NULL;
	this->onButton = true;
	this->held = false;
	this->mainComponent = true;
	this->originalFacingRight = faceRight;
	this->facingRight = faceRight;
}

sf::Vector2f Component::getPos() {
	return this->sprite.getPosition();
}

bool Component::getHeld() {
	return this->held;
}

void Component::highlight() {
	this->sprite.setOutlineThickness(2.f);
}

bool Component::getFacingRight() {
	return this->facingRight;
}

void Component::toggleFacingRight() {
	this->facingRight = !this->facingRight;
}

void Component::unhighlight() {
	this->sprite.setOutlineThickness(1.f);
}

void Component::moveTo(sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

sf::RectangleShape Component::getSprite() {
	return this->sprite;
}

int Component::checkDropSide(int fallSide) {
	return 0;
}

bool Component::getMainComponent() {
	return this->mainComponent;
}

void Gear::initLogic(bool main) {
	this->connectedNode = NULL;
	this->onButton = true;
	this->held = false;
	this->mainComponent = main;
}

Ramp::Ramp(bool faceRight) {
	this->colour = sf::Color::Green;
	this->initLogic(faceRight);
	this->initSprite(this->colour, this->position);
}

int Ramp::checkDropSide(int fallSide) {
	if (this->facingRight) {
		return 1;
	}
	return 0;
}

Crossover::Crossover(bool faceRight) {
	this->initLogic(faceRight);
	this->initSprite(this->colour, this->position);
}

int Crossover::checkDropSide(int fallSide) {
	if (fallSide == 0) {
		return 1;
	}
	return 0;
}

Interceptor::Interceptor(bool faceRight) {
	this->initLogic(faceRight);
	this->initSprite(this->colour, this->position);
}

int Interceptor::checkDropSide(int fallSide) {
	return 6;
}

Bit::Bit(bool faceRight) {
	this->initLogic(faceRight);
	this->initSprite(this->colour, this->position);
}

int Bit::checkDropSide(int fallSide) {
	this->facingRight = !this->facingRight;
	if (!this->facingRight) {
		return 3;
	}
	return 2;
}

GearBit::GearBit(bool faceRight) {
	this->initLogic(faceRight);
	this->initSprite(this->colour, this->position);
}

int GearBit::checkDropSide(int fallSide) {
	this->facingRight = !this->facingRight;
	if (!this->facingRight) {
		return 5;
	}
	return 4;
}

Gear::Gear() {
	this->initLogic(this->mainComponent);
	this->initSprite(this->colour, this->position);
}