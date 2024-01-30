#pragma once

#include "Graph.hpp"

Graph::Graph() {
	this->children[0] = NULL;
	this->children[1] = NULL;
}

void Graph::setNodeIndex(int index) {
	this->nodeIndex = index;
}

int Graph::getNodeIndex() {
	return this->nodeIndex;
}

void Graph::setChild(int index, Graph* child) {
	this->children[index] = child;
}

Graph* Graph::getChild(int index) {
	return this->children[index];
}
