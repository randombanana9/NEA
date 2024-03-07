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

	this->runButton.setSize(sf::Vector2f(250.f, 100.f));
	this->runButton.setPosition(sf::Vector2f(1078.f, 475.f));
	this->runButton.setFillColor(sf::Color(207, 226, 243));
	this->runButton.setOutlineColor(sf::Color::Black);
	this->runButton.setOutlineThickness(2.f);

	this->board = new Board(this->font);

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
	this->placementMode = true; //For whether the current mode is for placing components, or for simulating the board
	this->startedSimulation = false; //For whether the simulation is currently being run
	this->currentNode = NULL; //For the current node that the simulated marble is at
	this->framesSinceSimUpdate = 0; //For storing how long since the last simulation update
	this->dropSide = 0; //For storing which side the marble is dropping from, or to (0 is left, 1 is right, 2 is left and update bit, 3 is right and update bit, 4 is left and update all connected gear bits, 5 is right and update all connected gear bits, and 6 is intercepted)
	this->intercepted = false; //For storing if the marble has been intercepted
	this->stopped = false; //For stroing if the simulation has ended, similar to intercepted, but will also stop displaying the marble
	this->steps = 0; //For storing how many steps the marble has taken
	this->leftHopperStoredPreRun = this->hopperStoredOriginal; //For storing how many marbles were stored in the left hopper before the simulation was run
	this->rightHopperStoredPreRun = this->hopperStoredOriginal; //For storing how many marbles were stored in the right hopper before the simulation was run
	this->leftHopperStored = this->hopperStoredOriginal; //For storing how many marbles are stored in the left hopper during the simulation
	this->rightHopperStored = this->hopperStoredOriginal; //For storing how many marbles are stored in the right hopper during the simulation
	this->updateGears = false; //Used to store if gears need to be updated next tick of the simulation.
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

	this->partsMenuText[0].setString("Ramp");
	this->partsMenuText[1].setString("Crossover");
	this->partsMenuText[2].setString("Interceptor");
	this->partsMenuText[3].setString("Bit");
	this->partsMenuText[4].setString("Gear Bit");
	this->partsMenuText[5].setString("Gear");
	this->partsMenuText[6].setString("Flip\n(R)");

	for (int i = 0; i < 7; i++) {
		this->partsMenuText[i].setCharacterSize(14);
		this->partsMenuText[i].setFillColor(sf::Color::Black);
		this->partsMenuText[i].setFont(this->font);
		this->partsMenuText[i].setOrigin(sf::Vector2f(this->partsMenuText[i].getLocalBounds().getSize().x / 2, this->partsMenuText[i].getLocalBounds().getSize().y / 2)); //Sets the origin of the text to the centre of the text
		this->partsMenuText[i].setPosition(sf::Vector2f(55.f, 65.f + 125.f * i));
	}

	this->runButtonText.setString("Run");
	this->runButtonText.setCharacterSize(24);
	this->runButtonText.setFillColor(sf::Color::Black);
	this->runButtonText.setFont(this->font);
	this->runButtonText.setOrigin(sf::Vector2f(this->runButtonText.getLocalBounds().getSize().x / 2, this->runButtonText.getLocalBounds().getSize().y / 2)); //Sets the origin of the text to the centre of the text
	this->runButtonText.setPosition(sf::Vector2f(1203.f, 515.f));
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

				placeComponent(index);

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
					newComp = new Ramp(this->facingRight); //Dyanmic OOP Here!!!!
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
					newComp = new Gear(this->facingRight);
					break;
				default:
					this->facingRight = !this->facingRight;

					if (this->facingRight) {
						this->partsMenuText[6].setString("Flip\n(R)");
					}else{
						this->partsMenuText[6].setString("Flip\n(L)");
					}
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

void Game::updateButtons() {
	if (this->click && this->runButton.getGlobalBounds().contains(this->mousePosView)) {
		this->placementMode = !this->placementMode;
		if (this->placementMode) {
			this->endSim();
		}
		else {
			this->runButtonText.setString("Stop");
			this->runButtonText.setOrigin(sf::Vector2f(this->runButtonText.getLocalBounds().getSize().x / 2, this->runButtonText.getLocalBounds().getSize().y / 2)); //Sets the origin of the text to the centre of the text
			this->runButtonText.setPosition(sf::Vector2f(1203.f, 515.f));
		}
	}
	if (this->click) {
		if (this->placementMode) {
			for (int i = 0; i < 3; i += 2) {
				if (this->board->checkIfIntersectingButton(true, i, this->mousePosView)) {
					this->rightHopperStoredPreRun += i - 1;
					if (0 > this->rightHopperStoredPreRun) {
						this->rightHopperStoredPreRun = 0;
					}
					else if (99 < this->rightHopperStoredPreRun) {
						this->rightHopperStoredPreRun = 99;
					}
					this->board->setRightHopperTxt(std::to_string(this->rightHopperStoredPreRun));
				}
				else if (this->board->checkIfIntersectingButton(false, i, this->mousePosView)) {
					this->leftHopperStoredPreRun += i - 1;
					if (0 > this->leftHopperStoredPreRun) {
						this->leftHopperStoredPreRun = 0;
					}
					else if (99 < this->leftHopperStoredPreRun) {
						this->leftHopperStoredPreRun = 99;
					}
					this->board->setLeftHopperTxt(std::to_string(this->leftHopperStoredPreRun));
				}
			}
		}
	}
}

void Game::updateLevers() {
	if (this->click && !this->startedSimulation) {
		if (this->board->getLeftLeverBounds().contains(this->mousePosView)) {
			this->currentNode = this->leftRoot;
			this->startedSimulation = true;
			this->board->setMarbleColour(sf::Color::Blue);
			this->dropSide = 0;
			this->board->setMarblePosition(sf::Vector2f(485.f, 120.f));
			this->leftHopperStored = this->leftHopperStoredPreRun - 1;
			this->board->setLeftHopperTxt(std::to_string(this->leftHopperStored));
		}
		else if (this->board->getRightLeverBounds().contains(this->mousePosView)) {
			this->currentNode = this->rightRoot;
			this->startedSimulation = true;
			this->board->setMarbleColour(sf::Color::Red);
			this->dropSide = 1;
			this->board->setMarblePosition(sf::Vector2f(725.f, 120.f));
			this->rightHopperStored = this->rightHopperStoredPreRun - 1;
			this->board->setRightHopperTxt(std::to_string(this->rightHopperStored));
		}
	}
}

void Game::updateSimulation() {
	if (!this->intercepted) {
		int nodeIndex;
		Component* currentComp;
		if (!this->stopped && !this->intercepted) {
			if (this->framesSinceSimUpdate >= 40) {
				this->framesSinceSimUpdate = 0;

				nodeIndex = this->currentNode->getNodeIndex();
				currentComp = this->board->getNodeComponent(nodeIndex);

				if (this->board->getNodeComponent(nodeIndex) == NULL) { //If there is no component at the current node
					this->endSim();
					return;
				}

				//NEWCODE
				if (this->updateGears) {
					this->updateConnectedGears(currentComp, currentComp->getFacingRight());
					this->searchedNodes.clear();
					this->updateGears = false;
				}
				this->updateComponentOrientation(currentComp); //Last 3 lines are for updating the previous node before moving onto the next node

				if (this->steps != 0) {//Stops the simulation from skipping the first node
					this->currentNode = this->currentNode->getChild(this->dropSide);
				}

				if (this->currentNode == NULL) { //If the new node is NULL (i.e. off the side of the board or a lever)
					if (steps == 11) { //If the marble has reached a lever
						this->board->pushFallen();
						this->steps = 0;
						int lastNodeIndex = this->board->getNodesLength() - 1;
						if (nodeIndex == lastNodeIndex - 1 || nodeIndex == lastNodeIndex - 3) {
							this->currentNode = this->rightRoot;
						}
						else if (nodeIndex == lastNodeIndex - 7 || nodeIndex == lastNodeIndex - 9) {
							this->currentNode = this->leftRoot;
						}
						else {
							if (this->dropSide == 1) {
								this->currentNode = this->rightRoot;
							}
							else {
								this->currentNode = this->leftRoot;
							}
						}
						if (this->currentNode == this->rightRoot) {
							this->board->setMarbleColour(sf::Color::Red);
							if (this->rightHopperStored > 0) {
								this->rightHopperStored--;
								this->board->setRightHopperTxt(std::to_string(this->rightHopperStored));
							}
							else {
								this->stopped = true;
							}
						}
						else if (this->currentNode == this->leftRoot) {
							this->board->setMarbleColour(sf::Color::Blue);
							if (this->leftHopperStored > 0) {
								this->leftHopperStored--;
								this->board->setLeftHopperTxt(std::to_string(this->leftHopperStored));
							}
							else {
								this->stopped = true;
							}
						}
					}
					else { //If the marble has gone off the side
						this->endSim();
						return;
					}
				}
				if (this->board->getNodeComponent(nodeIndex) == NULL) { //If there is no component at the current node
					this->endSim();
					return;
				}

				nodeIndex = this->currentNode->getNodeIndex();
				currentComp = this->board->getNodeComponent(nodeIndex);

				if (currentComp == NULL) { //if the component is NULL (The node is empty) the game will go back to placement mode
					this->endSim();
					return;
				}

				this->board->setMarblePosition(this->board->getNodePosition(nodeIndex));
				this->dropSide = currentComp->checkDropSide(1 - this->dropSide); //the 'drop side' is opposite to the 'fall side' so this->dropSide is subtracted from 1 to get fallSide


				if (this->dropSide == 6) {
					this->intercepted = true;
				}
				if (this->dropSide == 4 || this->dropSide == 5) {
					this->updateGears = true;
				}
				this->dropSide %= 2;

				this->steps++;
			}
		}
		this->framesSinceSimUpdate++;
	}
}

void Game::endSim() { //Puts the game back into placement mode, and resets the required variables;
	this->framesSinceSimUpdate = 0;
	this->runButtonText.setString("Run");
	this->runButtonText.setOrigin(sf::Vector2f(this->runButtonText.getLocalBounds().getSize().x / 2, this->runButtonText.getLocalBounds().getSize().y / 2)); //Sets the origin of the text to the centre of the text
	this->runButtonText.setPosition(sf::Vector2f(1203.f, 515.f));
	this->startedSimulation = false;
	this->intercepted = false;
	this->stopped = false;
	this->steps = 0;
	this->placementMode = true;
	this->leftHopperStored = this->leftHopperStoredPreRun;
	this->rightHopperStored = this->rightHopperStoredPreRun;
	this->board->setLeftHopperTxt(std::to_string(this->leftHopperStored));
	this->board->setRightHopperTxt(std::to_string(this->rightHopperStored));
	this->board->clearFallen();
}

void Game::placeComponent(int index) {
	Component* oldComp = board->getNodeComponent(index);
	board->setNodeComponent(index, this->heldComponent);

	if (this->heldComponent->getFacingRight()) {
		this->heldComponent->moveTo(sf::Vector2f(this->board->getNodePosition(index).x + 5.f, this->board->getNodePosition(index).y));
	}
	else {
		this->heldComponent->moveTo(sf::Vector2f(this->board->getNodePosition(index).x - 5.f, this->board->getNodePosition(index).y));
	}
	if (this->heldComponent->isGear()) {
		this->updateConnectedGears(this->heldComponent, this->heldComponent->getFacingRight());
		this->searchedNodes.clear();
	}

	this->heldComponent = oldComp;
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

void Game::updateComponentOrientation(Component* component) {
	int index;
	for (int i = 0; i < this->board->getNodesLength(); i++) {
		if (this->board->getNodeComponent(i) == component) {
			index = i;
			break;
		}
	}
	if (component->getFacingRight()) {
		component->moveTo(sf::Vector2f(this->board->getNodePosition(index).x + 5.f, this->board->getNodePosition(index).y));
	}
	else {
		component->moveTo(sf::Vector2f(this->board->getNodePosition(index).x - 5.f, this->board->getNodePosition(index).y));
	}
}

void Game::updateConnectedGears(Component* currentComp, bool newFacingRight) {
	int index;
	for (int i = 0; i < this->board->getNodesLength(); i++) {
		if (this->board->getNodeComponent(i) == currentComp) {
			index = i;
			break;
		}
	}
	std::cout << index << "\n";
	for (auto& e : this->searchedNodes) { //Stops this branch if the current node has already been visited
		if (e == index) {
			return;
		}
	}
	this->searchedNodes.push_back(index); //Adds the current node to the searched nodes.
	if (currentComp->getFacingRight() == !newFacingRight) {
		currentComp->toggleFacingRight();
		this->updateComponentOrientation(currentComp);
	}
	for (int i = 0; i < 4; i++) { //Will search all adjacent nodes
		int sign = (i % 2) * 2 - 1; //sign will be -1 if i is even, and 1 if i is odd
		int num = i / 2 * 10 + 1; //will be 1 if i if 0 or 1, and 11 if i is 2 or 3
		int next = index + sign * num;

		if (i == 0) {
			if (index % 11 == 0) { //stops from searching off the side of the board
				continue;
			}
		}if (i == 1) {
			if (index / 11 == 0) {
				continue;
			}
		}if (i == 2) {
			if (index % 11 == 10) {
				continue;
			}
		}if (i == 3) {
			if (index / 11 == 10) {
				continue;
			}
		}
		Component* nextComponent = this->board->getNodeComponent(next);
		if (nextComponent == NULL) {
			continue;
		}
		else if (!nextComponent->isGear()) {
			continue;
		}
		this->updateConnectedGears(nextComponent, newFacingRight);
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
	this->window->draw(this->runButton);
}

void Game::drawText() {
	this->window->draw(this->infoText);

	for (int i = 0; i < 7; i++) {
		this->window->draw(this->partsMenuText[i]);
	}

	this->window->draw(this->runButtonText);
}

void Game::drawHeld() {
	if (this->heldComponent != NULL) {
		this->window->draw(this->heldComponent->getSprite());
	}
}

void Game::drawMarbles() {
	if (!this->stopped) {
		this->window->draw(this->board->getMarble());
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
	if (this->placementMode) {
		this->updateComponents();
		this->updatePartsMenu();
	}
	else {
		this->updateLevers();
		if (this->startedSimulation) {
			this->updateSimulation();
		}
	}
	this->updateButtons();
}

void Game::render() {
	//Clears the window and sets a background colour
	this->window->clear(sf::Color(239, 239, 239, 255));

	this->drawObjects();
	this->drawText();

	this->drawHeld();

	if (startedSimulation) {
		this->drawMarbles();
	}

	//displays the new frame
	this->window->display();
}
