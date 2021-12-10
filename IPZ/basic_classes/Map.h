#pragma once
#include <iostream>
#include "Generator.h"
#include "Road.h"
#include "Cell.h"
#include <map>
#include <vector>

class Map
{
	protected:
	std::string name;
	std::map<Road, int> roads;
	std::map<Generator, int> generators;
	std::vector<Cell*> cellsWithVehs;

	public:
	//name - nazwa nowej mapy
	Map(std::string name) {
		this->name = name;
	}

	void setCellsWithVehs(std::vector<Cell*> newCellsWithVehs) {
		this->cellsWithVehs = newCellsWithVehs;
	}

	std::vector<Cell*> getCellsWithVehs() {
		return this->cellsWithVehs;
	}

	void createXML() {
		return;
	}
};
