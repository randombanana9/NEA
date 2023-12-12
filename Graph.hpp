#pragma once

#include "source.hpp"

class Node;

class Graph {
	std::vector<Graph*> parents;
	std::vector<Graph*> children;
	bool isOrphan;
	bool isLeaf;
};

