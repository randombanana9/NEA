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


void Board::initFont(sf::Font& font) {
	this->font = font;
}

void Board::initHoppers() {
	this->leftHopper[1].setFillColor(sf::Color::White);
	this->leftHopper[1].setOutlineColor(sf::Color::Black);
	this->leftHopper[1].setOutlineThickness(1.f);
	this->leftHopper[1].setSize(sf::Vector2f(40.f, 40.f));
	this->leftHopper[1].setOrigin(sf::Vector2f(20.f, 20.f));
	this->leftHopper[1].setPosition(sf::Vector2f(485.f, 75.f));

	this->rightHopper[1].setFillColor(sf::Color::White);
	this->rightHopper[1].setOutlineColor(sf::Color::Black);
	this->rightHopper[1].setOutlineThickness(1.f);
	this->rightHopper[1].setSize(sf::Vector2f(40.f, 40.f));
	this->rightHopper[1].setOrigin(sf::Vector2f(20.f, 20.f));
	this->rightHopper[1].setPosition(sf::Vector2f(725.f, 75.f));

	for (int i = 0; i < 3; i += 2) {
		this->leftHopper[i].setFillColor(sf::Color(209, 237, 242));
		this->leftHopper[i].setOutlineColor(sf::Color::Black);
		this->leftHopper[i].setOutlineThickness(1.f);
		this->leftHopper[i].setSize(sf::Vector2f(30.f, 30.f));
		this->leftHopper[i].setOrigin(sf::Vector2f(15.f, 15.f));
		this->leftHopper[i].setPosition(sf::Vector2f(485.f + (i-1) * 45, 75.f));

		this->rightHopper[i].setFillColor(sf::Color(209, 237, 242));
		this->rightHopper[i].setOutlineColor(sf::Color::Black);
		this->rightHopper[i].setOutlineThickness(1.f);
		this->rightHopper[i].setSize(sf::Vector2f(30.f, 30.f));
		this->rightHopper[i].setOrigin(sf::Vector2f(15.f, 15.f));
		this->rightHopper[i].setPosition(sf::Vector2f(725.f + (i - 1) * 45, 75.f));
	}

	for (int i = 0; i < 3; i++) {
		this->leftHopperTxt[i].setFont(this->font);
		this->leftHopperTxt[i].setCharacterSize(24);
		this->leftHopperTxt[i].setFillColor(sf::Color::Black);

		this->rightHopperTxt[i].setFont(this->font);
		this->rightHopperTxt[i].setCharacterSize(24);
		this->rightHopperTxt[i].setFillColor(sf::Color::Black);

		if (i == 0) {
			this->leftHopperTxt[i].setString("-");
			this->rightHopperTxt[i].setString("-");
		}
		else if (i == 1) {
			this->leftHopperTxt[i].setString("8");
			this->rightHopperTxt[i].setString("8");
		}else{
			this->leftHopperTxt[i].setString("+");
			this->rightHopperTxt[i].setString("+");
		}
		this->leftHopperTxt[i].setOrigin(sf::Vector2f(this->leftHopperTxt[i].getLocalBounds().getSize().x / 2, this->leftHopperTxt[i].getLocalBounds().getSize().y / 2));
		this->leftHopperTxt[i].setPosition(sf::Vector2f(this->leftHopper[i].getPosition().x - 8.f, this->leftHopper[i].getPosition().y - 15.f));

		this->rightHopperTxt[i].setOrigin(sf::Vector2f(this->rightHopperTxt[i].getLocalBounds().getSize().x / 2, this->rightHopperTxt[i].getLocalBounds().getSize().y / 2));
		this->rightHopperTxt[i].setPosition(sf::Vector2f(this->rightHopper[i].getPosition().x - 8.f, this->rightHopper[i].getPosition().y - 15.f));
	}
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

void Board::drawHoppers(sf::RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		window.draw(this->leftHopper[i]);
		window.draw(this->rightHopper[i]);
		
		window.draw(this->leftHopperTxt[i]);
		window.draw(this->rightHopperTxt[i]);
	}
}

void Board::drawNodes(sf::RenderWindow& window) {
	for (auto& e : this->nodes) {
		window.draw(e->getSprite());
	}
}

Board::Board(sf::Font& font) : font(font) {
	this->initObjects();
	this->initBorder();
	this->initLevers();
	this->initFont(font);
	this->initHoppers();
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

void Board::setLeftHopperTxt(std::string newStr) {
	int oldLength = this->leftHopperTxt[1].getString().getSize();
	int newLength = newStr.length();

	if (oldLength < newLength) {
		this->leftHopperTxt[1].move(sf::Vector2f(-2.f, 0));
	}
	else if (oldLength > newLength) {
		this->leftHopperTxt[1].move(sf::Vector2f(2.f, 0));
	}

	this->leftHopperTxt[1].setString(newStr);
}

void Board::setRightHopperTxt(std::string newStr) {
	int oldLength = this->rightHopperTxt[1].getString().getSize();
	int newLength = newStr.length();

	if (oldLength < newLength) {
		this->rightHopperTxt[1].move(sf::Vector2f(-8.f, 0));
	}
	else if (oldLength > newLength) {
		this->rightHopperTxt[1].move(sf::Vector2f(8.f, 0));
	}

	this->rightHopperTxt[1].setString(newStr);
}

void Board::pushFallen() {
	this->fallenMarbles.push_back(this->marble);
}

bool Board::checkIfIntersectingNode(int index, sf::Vector2f coords) {
	return this->nodes[index]->getSprite().getGlobalBounds().contains(coords);
}

bool Board::checkIfIntersectingButton(bool right, int index, sf::Vector2f coords) {
	if (right) {
		if (this->rightHopper[index].getGlobalBounds().contains(coords)) {
			return true;
		}
	}
	else {
		if (this->leftHopper[index].getGlobalBounds().contains(coords)) {
			return true;
		}
	}
	return false;
}

void Board::drawBoard(sf::RenderWindow& window) {
	this->drawBorder(window);
	this->drawLevers(window);
	this->drawHoppers(window);
	this->drawNodes(window);
}
