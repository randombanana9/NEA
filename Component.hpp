#pragma once

#include "source.hpp"

class Component {
protected: //private members cannot be inherited so protected members are used in the parent class

public:
	Component();
	~Component();
};

class Ramp : Component {

};