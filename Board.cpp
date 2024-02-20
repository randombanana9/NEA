#pragma once

#include "Board.hpp"
#include "Node.hpp"

void Board::initObjects() {
	board = new bool[this->boardSize*this->boardSize];
	//Set every other node in the board to a main node
	for (int i = 0; i < this->boardSize * this->boardSize; i++) {
		if (i % 2) {
			board[i] = true;
		}
		else {
			board[i] = false;
		}
	}

	this->marble.setRadius(6.f);
	this->marble.setOrigin(sf::Vector2f(6.f, 6.f));
	this->marble.setFillColor(sf::Color::Black);
	this->marble.setOutlineColor(sf::Color::Black);
	this->marble.setOutlineThickness(1.f);
	this->marble.setPosition(sf::Vector2f(375.f, 260.f));
}

void Board::initBorder() {
	this->border.setFillColor(sf::Color::White);
	this->border.setSize(sf::Vector2f(this->width, this->height));
	this->border.setPosition(sf::Vector2f(this->xPos, this->yPos));
	this->border.setOutlineColor(sf::Color::Black);
	this->border.setOutlineThickness(2.f);
}

void Board::initLevers() {
	this->leftLever.setFillColor(sf::Color::Blue);
	this->leftLever.setOutlineColor(sf::Color::Black);
	this->leftLever.setOutlineThickness(1.f);
	this->leftLever.setSize(sf::Vector2f(this->width/2 - 20.f, 10.f));
	this->leftLever.setPosition(sf::Vector2f(this->xPos + 5.f, this->yPos + this->height - 100.f));
	this->leftLever.setRotation(2.f);


	this->rightLever.setFillColor(sf::Color::Red);
	this->rightLever.setOutlineColor(sf::Color::Black);
	this->rightLever.setOutlineThickness(1.f);
	this->rightLever.setSize(sf::Vector2f(this->width / 2 - 20.f, 10.f));
	this->rightLever.setOrigin(sf::Vector2f(this->width / 2 - 20.f, 0.f));
	this->rightLever.setPosition(sf::Vector2f(this->xPos + this->width - 5.f, this->yPos + this->height - 100.f));
	this->rightLever.setRotation(-2.f);
}

void Board::initNodes() {
	for (int i = 0; i < (this->boardSize * this->boardSize); i++) {
		sf::Vector2f pos = sf::Vector2f(this->xPos + 130.f + 55.f*(i%this->boardSize),
										this->yPos + 150.f + 55.f*(i/this->boardSize));
		this->node = new Node(this->board[i], pos);
		this->nodes.push_back(this->node);
	}
	this->node = NULL;
}

void Board::drawBorder(sf::RenderWindow& window) {
	window.draw(this->border);
}

void Board::drawLevers(sf::RenderWindow& window) {
	window.draw(this->leftLever);
	window.draw(this->rightLever);
}

void Board::drawNodes(sf::RenderWindow& window) {
	for (auto& e : this->nodes) {
		window.draw(e->getSprite());
	}
}

Board::Board() {
	this->initObjects();
	this->initBorder();
	this->initLevers();
	this->initNodes();
}

Board::~Board() {
	for (auto& e : this->nodes) {
		delete e;
	}
	delete[] board;
}

int Board::getNodesLength() {
	return this->nodes.size();
}

Component* Board::getNodeComponent(int index) {
	return this->nodes[index]->getComponent();
}

sf::Vector2f Board::getNodePosition(int index) {
	return this->nodes[index]->getSprite().getPosition();
}

sf::FloatRect Board::getLeftLeverBounds() {
	return this->leftLever.getGlobalBounds();
}

sf::FloatRect Board::getRightLeverBounds() {
	return this->rightLever.getGlobalBounds();
}

bool Board::getNodeMainNode(int index) {
	return this->nodes[index]->getMainNode();
}

sf::CircleShape Board::getMarble() {
	return this->marble;
}

sf::CircleShape Board::getFallenMarbles(int index) {
	return this->fallenMarbles[index];
}

void Board::setNodeComponent(int index, Component* component) {
	this->nodes[index]->setComponent(component);
}

void Board::setMarbleColour(sf::Color col) {
	this->marble.setFillColor(col);
}

void Board::setMarblePosition(sf::Vector2f pos) {
	this->marble.setPosition(pos);
}

void Board::pushFallen() {
	this->fallenMarbles.push_back(this->marble);
}

bool Board::checkIfIntersectingNode(int index, sf::Vector2f coords) {
	return this->nodes[index]->getSprite().getGlobalBounds().contains(coords);
}

void Board::drawBoard(sf::RenderWindow& window) {
	this->drawBorder(window);
	this->drawLevers(window);
	this->drawNodes(window);
}
