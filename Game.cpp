#pragma once

#include "Game.hpp"
#include "Board.hpp"
#include "Component.hpp"
#include "Graph.hpp"


void Game::initWindow() {
	this->settings.antialiasingLevel = 8;
	this->videoMode.width = 1600; //These two lines set the width and height of the window.
	this->videoMode.height = 900;
	this->window = new sf::RenderWindow(this->videoMode, "Turing Tumble Simulator", sf::Style::Close, this->settings);
	this->window->setFramerateLimit(60);
}

void Game::initObjects() {
	this->partsMenu[0].setSize(sf::Vector2f(116, 896.f));
	this->partsMenu[0].setPosition(sf::Vector2f(2.f, 2.f));
	this->partsMenu[0].setFillColor(sf::Color::White);
	this->partsMenu[0].setOutlineColor(sf::Color::Black);
	this->partsMenu[0].setOutlineThickness(2.f);
	for (int i = 1; i < 8; i++) {
		this->partsMenu[i].setSize(sf::Vector2f(100.f, 100.f));
		this->partsMenu[i].setPosition(10.f, -100.f + 125.f * i);
		this->partsMenu[i].setFillColor(sf::Color(207, 226, 243));
		this->partsMenu[i].setOutlineColor(sf::Color::Black);
		this->partsMenu[i].setOutlineThickness(1.f);
	}

	this->infoBox.setSize(sf::Vector2f(520.f, 400.f));
	this->infoBox.setPosition(sf::Vector2f(1078.f, 2.f));
	this->infoBox.setFillColor(sf::Color(252, 229, 205, 255));
	this->infoBox.setOutlineColor(sf::Color::Black);
	this->infoBox.setOutlineThickness(2.f);

	this->board = new Board();

	Graph* newGraph;
	int width = sqrt(this->board->getNodesLength());
	for (int i = 0; i < this->board->getNodesLength(); i++) {
		newGraph = new Graph;
		if (i == ((width + 5) / 4) - 1) {
			this->leftRoot = newGraph;
		}else if(i == width - (width + 5) / 4){
			this->rightRoot = newGraph;
		}
		this->graph.push_back(newGraph);
	}

	for (int i = 0; i < this->board->getNodesLength(); i++) {
		if (i <= this->board->getNodesLength() - width) {
			if (i % 11) {
				this->graph[i]->setChild(0, this->graph[i + 10]);
			}
			if ((i + 1) % 11 && i + 12 < this->board->getNodesLength()) {
				this->graph[i]->setChild(1, this->graph[i + 12]);
			}
		}
		this->graph[i]->setNodeIndex(i);
	}
}

void Game::initLogic() {
	this->mouseHeld = false; //For detecting if the mouse button in held for more than one frame
	this->click = false; //Stores if the mouse was pressed down this frame
	this->heldComponent = NULL; //Stores a pointer to the currently held component (NULL if not holding a component)
	this->facingRight = true; //Stores if components to be placed are facing right or not
}

void Game::initFonts() {
	this->font.loadFromFile("Resources/Sans-Mono.ttf"); //Loads the font to be used for text
}

void Game::initText() {
	this->infoText.setCharacterSize(24);
	this->infoText.setFillColor(sf::Color::Black);
	this->infoText.setFont(this->font);
	this->infoText.setPosition(sf::Vector2f(1100.f, 20.f));
	this->infoText.setString("Lorem Ipsum Dolor");

	this->partsMenuText[0].setString("Ramp\n(R)");
	this->partsMenuText[1].setString("Crossover\n(R)");
	this->partsMenuText[2].setString("Interceptor\n(R)");
	this->partsMenuText[3].setString("Bit\n(R)");
	this->partsMenuText[4].setString("Gear Bit\n(R)");
	this->partsMenuText[5].setString("Gear\n(R)");
	this->partsMenuText[6].setString("Flip\n(R)");

	for (int i = 0; i < 7; i++) {
		this->partsMenuText[i].setCharacterSize(14);
		this->partsMenuText[i].setFillColor(sf::Color::Black);
		this->partsMenuText[i].setFont(this->font);
		this->partsMenuText[i].setOrigin(sf::Vector2f(this->partsMenuText[i].getLocalBounds().getSize().x / 2, this->partsMenuText[i].getLocalBounds().getSize().y / 2));
		this->partsMenuText[i].setPosition(sf::Vector2f(55.f, 65.f + 125.f * i));
	}
}

void Game::pollEvents() {
	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed) { //checks if the close button at the top right of the window has been pressed
			this->window->close();
		}
		if (this->ev.type == sf::Event::KeyPressed) {
			if (this->ev.key.code == sf::Keyboard::Escape) { //checks if the escape key has been pressed
				this->window->close();
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->click = !this->mouseHeld;
		this->mouseHeld = true;
	}
	else {
		this->mouseHeld = false;
		this->click = false;
	}
}

void Game::updateMousePos() {
	//takes the current mouse position and stores it in these variables
	this->mousePosWindow = sf::Mouse::getPosition(*this->window); //pixel position of the mouse
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow); //coordinate position of the mouse
}

void Game::updateComponents() {
	if (this->heldComponent != NULL) { //Checks if there is a component being held
		for (auto& e : this->components) {
			if (e == this->heldComponent) {
				e->moveTo(this->mousePosView);
			}
		}
		if (!this->mouseHeld) {
			bool placeComp = false;
			int index = 0;

			for (index; index < board->getNodesLength(); index++) {
				if (this->board->checkIfIntersectingNode(index, this->mousePosView)) {
					if (this->board->getNodeMainNode(index) || !this->heldComponent->getMainComponent()) {
						placeComp = true;
						break;
					}
				}
			}

			if (placeComp) { //If the component is to be placed on a node
				Component* oldComp = board->getNodeComponent(index);
				board->setNodeComponent(index, this->heldComponent);

				this->heldComponent->moveTo(this->board->getNodePosition(index));

				this->heldComponent = oldComp;
			}
			deleteHeldComponent();
		}
	}
	else {
		for (auto& e : this->components) {
			if (abs(e->getPos().x - this->mousePosView.x) <= 25.f && abs(e->getPos().y - this->mousePosView.y) <= 25.f) { //Checks if the mouse is within a square around the component
				e->highlight();
				if (this->mouseHeld && !e->getHeld()) {
					this->heldComponent = e;
					for (int i = 0; i < this->board->getNodesLength(); i++) {
						if (e == this->board->getNodeComponent(i)) {
							this->board->setNodeComponent(i, NULL);
						}
					}
				}
			}
			else {
				e->unhighlight();
			}
		}
	}
}

void Game::updatePartsMenu() {
	for (int i = 1; i < 8; i++) {
		if (this->partsMenu[i].getGlobalBounds().contains(this->mousePosView)) {
			if (this->click) {
				Component* newComp = NULL;
				switch (i) {
				case 1:
					newComp = new Ramp(this->facingRight);
					break;
				case 2:
					newComp = new Crossover(this->facingRight);
					break;
				case 3:
					newComp = new Interceptor(this->facingRight);
					break;
				case 4:
					newComp = new Bit(this->facingRight);
					break;
				case 5:
					newComp = new GearBit(this->facingRight);
					break;
				case 6:
					newComp = new Gear;
					break;
				default:
					this->facingRight = !this->facingRight;
				}
				if (newComp != NULL) {
					newComp->highlight();
					newComp->moveTo(this->mousePosView);
					this->components.push_back(newComp);
					this->heldComponent = newComp;
				}
			}
		}
	}
}

void Game::deleteHeldComponent() {
	for (int i = 0; i < this->components.size(); i++) {
		if (this->components[i] == this->heldComponent) {
			delete this->components[i];
			this->components.erase(this->components.begin() + i);
			this->heldComponent = NULL;
		}
	}
}

void Game::drawObjects() {
	for (int i = 0; i < 8; i++) {
		this->window->draw(this->partsMenu[i]);
	}
	this->window->draw(this->infoBox);
	this->board->drawBoard(*this->window);

	for (auto& e : this->components) {
		this->window->draw(e->getSprite());
	}
}

void Game::drawText() {
	this->window->draw(this->infoText);

	for (int i = 0; i < 7; i++) {
		this->window->draw(this->partsMenuText[i]);
	}
}

void Game::drawHeld() {
	if (this->heldComponent != NULL) {
		this->window->draw(this->heldComponent->getSprite());
	}
}

Game::Game() {
	this->initWindow();
	this->initObjects();
	this->initFonts();
	this->initText();
	this->initLogic();
}

Game::~Game() {
	delete this->window;
	delete this->board;
	for (auto& e : this->components) {
		delete e;
	}
	for (auto& e : this->graph) {
		delete e;
	}
}

const bool Game::running() const {
	return this->window->isOpen(); //checks if the application window is open
}

void Game::update() {
	this->pollEvents();
	this->updateMousePos();
	this->updateComponents();
	this->updatePartsMenu();
}

void Game::render() {
	//Clears the window and sets a background colour
	this->window->clear(sf::Color(239, 239, 239, 255));

	this->drawObjects();
	this->drawText();

	this->drawHeld();

	//displays the new frame
	this->window->display();
}
