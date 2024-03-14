#pragma once

#include "Component.hpp"

void Component::initSprite(sf::Vector2f position) {
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

void Component::initTexture(sf::Texture txtr) {
	this->texture = txtr;
}

void Component::initLogic(bool faceRight) {
	this->connectedNode = NULL;
	this->held = false;
	this->mainComponent = true;
	this->facingRight = faceRight;
	this->isAGear = false;
	this->changedOrientation = false;
}

sf::Vector2f Component::getPos() {
	float xPos = this->sprite.getPosition().x + this->width / 2 - this->offset;
	float yPos = this->sprite.getPosition().y + this->width / 2;
	return sf::Vector2f(xPos, yPos);
}

bool Component::getHeld() {
	return this->held;
}

bool Component::getFacingRight() {
	return this->facingRight;
}

void Component::toggleFacingRight() {
	this->facingRight = !this->facingRight;
	this->changedOrientation = true;
}

void Component::updateOrientation() {
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

void Component::moveTo(sf::Vector2f pos) {
	float xPos = pos.x - this->width / 2 + this->offset;
	float yPos = pos.y - this->width / 2;
	this->sprite.setPosition(sf::Vector2f(xPos, yPos));
}

sf::Sprite Component::getSprite() {
	return this->sprite;
}

int Component::checkDropSide(int fallSide) {
	return 0;
}

bool Component::isGear() {
	return this->isAGear;
}

bool Component::getMainComponent() {
	return this->mainComponent;
}

Ramp::Ramp(bool faceRight, sf::Texture& txtr) {
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Ramp::checkDropSide(int fallSide) {
	if (this->facingRight) {
		return 1;
	}
	return 0;
}

Crossover::Crossover(bool faceRight, sf::Texture& txtr) {
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Crossover::checkDropSide(int fallSide) {
	if (fallSide == 0) {
		return 1;
	}
	return 0;
}

Interceptor::Interceptor(bool faceRight, sf::Texture& txtr) {
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Interceptor::checkDropSide(int fallSide) {
	return 6;
}

Bit::Bit(bool faceRight, sf::Texture& txtr) {
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Bit::checkDropSide(int fallSide) {
	this->toggleFacingRight();
	if (!this->facingRight) {
		return 3;
	}
	return 2;
}

void GearBit::initLogic(bool faceRight) {
	this->connectedNode = NULL;
	this->held = false;
	this->mainComponent = true;
	this->facingRight = faceRight;
	this->isAGear = true;
}

void GearBit::flip() {
	this->toggleFacingRight();
	this->updateOrientation();
}

GearBit::GearBit(bool faceRight, sf::Texture& txtr) {
	this->initLogic(faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int GearBit::checkDropSide(int fallSide) {
	this->toggleFacingRight();
	if (!this->facingRight) {
		return 5;
	}
	return 4;
}

void Gear::initLogic(bool main, bool faceRight) {
	this->connectedNode = NULL;
	this->held = false;
	this->mainComponent = main;
	this->isAGear = true;
	this->facingRight = faceRight;
}

Gear::Gear(bool faceRight, sf::Texture& txtr) {
	this->initLogic(this->mainComponent, faceRight);
	this->initTexture(txtr);
	this->initSprite(this->position);
}

int Gear::checkDropSide(int fallSide) {
	return 7;
}