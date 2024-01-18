#pragma once

#include "Game.hpp"
#include "Board.hpp"
#include "Component.hpp"

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
}

void Game::initLogic() {
	this->mouseHeld = false; //For detecting if the mouse button in held for more than one frame
	this->click = false; //Stores if the mouse was pressed down this frame
	this->heldComponent = NULL; //Stores a pointer to the currently held component (NULL if not holding a component)
}

void Game::initFonts() {
	this->font.loadFromFile("Resources/Sans-Mono.ttf"); //Loads the font to be used for text
}

void Game::initText() {
	this->infoText.setCharacterSize(24.f);
	this->infoText.setFillColor(sf::Color::Black);
	this->infoText.setFont(this->font);
	this->infoText.setPosition(sf::Vector2f(1100.f, 20.f));
	this->infoText.setString("Lorem Ipsum Dolor");
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
				if (board->checkIfIntersectingNode(index, this->mousePosView)) {
					placeComp = true;
					break;
				}
			}

			if (placeComp) { //If the component is to be placed on a node
				Component* oldComp = board->getNodeComponent(index);
				board->setNodeComponent(index, this->heldComponent);

				this->heldComponent->moveTo(this->board->getNodePosition(index));

				std::cout << this->heldComponent->getSprite().getPosition().x << ", " << this->heldComponent->getSprite().getPosition().y << "\n";
				std::cout << this->board->getNodePosition(index).x << ", " << this->board->getNodePosition(index).y << "\n\n";

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

void Game::UpdatePartsMenu() {
	for (int i = 1; i < 8; i++) {
		if (this->partsMenu[i].getGlobalBounds().contains(this->mousePosView)) {
			if (this->click) {
				Component* newComp;
				switch (i) {
				case 1:
					newComp = new Ramp;
					std::cout << "Made Ramp\n";
					break;
				case 2:
					newComp = new Crossover;
					std::cout << "Made Crossover\n";
					break;
				case 3:
					newComp = new Interceptor;
					std::cout << "Made Interceptor\n";
					break;
				case 4:
					newComp = new Bit;
					std::cout << "Made Bit\n";
					break;
				case 5:
					newComp = new GearBit;
					std::cout << "Made Gear Bit\n";
					break;
				case 6:
					newComp = new Gear;
					std::cout << "Made Gear\n";
					break;
				default:
					newComp = new Ramp;
				}
				std::cout << newComp << "\n\n";
				newComp->highlight();
				this->components.push_back(newComp);
				this->heldComponent = newComp;
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
}

const bool Game::running() const {
	return this->window->isOpen(); //checks if the application window is open
}

void Game::update() {
	this->pollEvents();
	this->updateMousePos();
	this->updateComponents();
	this->UpdatePartsMenu();
}

void Game::render() {
	//Clears the window and sets a background colour
	this->window->clear(sf::Color(239, 239, 239, 255));

	this->drawObjects();
	this->drawText();

	//displays the new frame
	this->window->display();
}
