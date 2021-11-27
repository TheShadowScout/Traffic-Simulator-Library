#pragma once
#include <iostream>
#include "Generator.h"
#include "Destructor.h"
#include "Teleporter.h"
#include "Road.h"
#include "Cell.h"
#include <map>
#include <list>

using namespace std;

class Map
{
	protected:
	string name;
	map<Road, int> roads;
	map<Generator, int> generators;
	map<Destructor, int> destructors;
	map<Teleporter, int> teleporters;
	list<Cell> cellsWithCars;

	public:
	//name - nazwa nowej mapy
	Map(string name) {
		this->name = name;
	}

	void createXML() {
		return;
	}
};
