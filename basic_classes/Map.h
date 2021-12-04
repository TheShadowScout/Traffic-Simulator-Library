#pragma once
#include <iostream>
#include "Generator.h"
#include "Destructor.h"
#include "Teleporter.h"
#include "Road.h"
#include "Cell.h"
#include <map>
#include <list>

class Map
{
	protected:
	std::string name;
	std::map<Road, int> roads;
	std::map<Generator, int> generators;
	std::map<Destructor, int> destructors;
	std::map<Teleporter, int> teleporters;
	std::list<Cell> cellsWithCars;

	public:
	//name - nazwa nowej mapy
	Map(std::string name) {
		this->name = name;
	}

	void createXML() {
		return;
	}
};
