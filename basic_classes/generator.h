#pragma once
#include "Cell.h"
#include <iostream>

class Generator : public Cell
{
	protected:
	std::string name;
	
	public:
	Generator() {
		name = "Generator";
	}

	void create() {
		Vehicle *vehicle = new Vehicle("Nowy pojazd",4);
		std::cout << "Generated car object: " << vehicle->getName() << std::endl;
	}
};