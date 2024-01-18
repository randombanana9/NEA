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

void Component::initLogic() {
	connectedNode = NULL;
	onButton = true;
	held = false;
	mainComponent = true;
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

void Component::unhighlight() {
	this->sprite.setOutlineThickness(1.f);
}

void Component::moveTo(sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

sf::RectangleShape Component::getSprite() {
	return this->sprite;
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

Ramp::Ramp() {
	this->colour = sf::Color::Green;
	this->initLogic();
	this->initSprite(this->colour, this->position);
}

Crossover::Crossover() {
	this->initLogic();
	this->initSprite(this->colour, this->position);
}

Interceptor::Interceptor() {
	this->initLogic();
	this->initSprite(this->colour, this->position);
}

Bit::Bit() {
	this->initLogic();
	this->initSprite(this->colour, this->position);
}

GearBit::GearBit() {
	this->initLogic();
	this->initSprite(this->colour, this->position);
}

Gear::Gear() {
	this->initLogic(this->mainComponent);
	this->initSprite(this->colour, this->position);
}