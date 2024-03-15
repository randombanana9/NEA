#pragma once

#include "Graph.hpp"

Graph::Graph() { //Initialisation function, sets both children to NULL
	this->children[0] = NULL;
	this->children[1] = NULL;
}

void Graph::setNodeIndex(int index) { //set which board node this graph node corresponds to
	this->nodeIndex = index;
}

int Graph::getNodeIndex() { //Returns the board node which this graph node corresponds to
	return this->nodeIndex;
}

void Graph::setChild(int index, Graph* child) { //Sets the value of one of the child pointers
	this->children[index] = child;
}

Graph* Graph::getChild(int index) { //Returns a pointer of one of the children
	return this->children[index];
}
