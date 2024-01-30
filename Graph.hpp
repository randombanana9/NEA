#pragma once

#include "source.hpp"

class Node;

class Graph {
private:
	Graph* children[2];
	int nodeIndex;

public:
	Graph();

	void setNodeIndex(int index);
	int getNodeIndex();
	void setChild(int index, Graph* child);
	Graph* getChild(int index);
};

