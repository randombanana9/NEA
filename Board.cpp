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

void Board::initHoppers() {
	for (int i = 0; i < 3; i++) {
		this->blueHopper[i].setFillColor(sf::Color::Blue);
		this->blueHopper[i].setOutlineColor(sf::Color::Black);
		this->blueHopper[i].setOutlineThickness(1.f);
		this->blueHopper[i].setSize(sf::Vector2f(30.f, 10.f));
		this->blueHopper[i].setPosition(sf::Vector2f(this->xPos + 10.f, this->yPos + 20.f + i*20));

		this->redHopper[i].setFillColor(sf::Color::Red);
		this->redHopper[i].setOutlineColor(sf::Color::Black);
		this->redHopper[i].setOutlineThickness(1.f);
		this->redHopper[i].setSize(sf::Vector2f(30.f, 10.f));
		this->redHopper[i].setPosition(sf::Vector2f(this->xPos + this->width - 40.f, this->yPos + 20.f + i * 20));
	}

	//first ramps
	this->blueHopper[0].setSize(sf::Vector2f(this->width/2 - 80.f, 10.f));
	this->blueHopper[0].setPosition(this->xPos + 20.f, this->yPos + 30.f);
	this->blueHopper[0].setRotation(1.5);

	this->redHopper[0].setSize(sf::Vector2f(this->width / 2 - 80.f, 10.f));
	this->redHopper->setOrigin(this->redHopper->getSize().x, 0.f);
	this->redHopper[0].setPosition(this->xPos + this->width - 20.f, this->yPos + 30.f);
	this->redHopper[0].setRotation(-1.5);

	//second ramps
	this->blueHopper[1].setSize(sf::Vector2f(this->width / 4 - 100.f, 10.f));
	this->blueHopper[1].setPosition(this->xPos + this->width / 2 - 105.f, this->yPos + 90.f);
	this->blueHopper[1].setRotation(-20);

	this->redHopper[1].setSize(sf::Vector2f(this->width / 4 - 100.f, 10.f));
	this->redHopper[1].setOrigin(this->redHopper[1].getSize().x, 0.f);
	this->redHopper[1].setPosition(this->xPos + this->width / 2 + 105.f, this->yPos + 90.f);
	this->redHopper[1].setRotation(20);

	//gates
	this->blueHopper[2].setSize(sf::Vector2f(40.f, 10.f));
	this->blueHopper[2].setPosition(this->blueHopper[1].getPosition());
	this->blueHopper[2].move(sf::Vector2f(-6.f, -20.f));
	this->blueHopper[2].setRotation(70.f);

	this->redHopper[2].setSize(sf::Vector2f(40.f, 10.f));
	this->redHopper[2].setOrigin(this->redHopper[2].getSize().x, 0.f);
	this->redHopper[2].setPosition(this->redHopper[1].getPosition());
	this->redHopper[2].move(sf::Vector2f(6.f, -20.f));
	this->redHopper[2].setRotation(-70.f);
}

void Board::initNodes() {
	for (int i = 0; i < (this->boardSize * this->boardSize); i++) {
		sf::Vector2f pos = sf::Vector2f(this->xPos + 125.f + 55.f*(i/this->boardSize),
										this->yPos + 150.f + 55.f*(i%this->boardSize));
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

void Board::drawHoppers(sf::RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		window.draw(this->blueHopper[i]);
		window.draw(this->redHopper[i]);
	}
}

void Board::drawNodes(sf::RenderWindow& window) {
	for (auto& e : this->nodes) {
		window.draw(e->getSprite());
	}
}

Board::Board() {
	this->initObjects();
	this->initBorder();
	this->initHoppers();
	this->initLevers();
	this->initNodes();
}

Board::~Board() {
	for (auto& e : this->nodes) {
		delete e;
	}
	delete[] board;
}

void Board::drawBoard(sf::RenderWindow& window) {
	this->drawBorder(window);
	this->drawLevers(window);
	this->drawHoppers(window);
	this->drawNodes(window);
}
