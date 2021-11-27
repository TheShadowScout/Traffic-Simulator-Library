#pragma once
#include "Cell.h"
#include <iostream>

class Destructor : public Cell
{
	protected:
	std::string name;
	
	public:
	Destructor() {
		name = "Destructor";
	}

	void remove() {
		delete this->vehicle;
		this->vehicle = nullptr;
		std::cout << "Deleted car object" << std::endl;
	}
};