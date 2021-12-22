#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "Generator.h"
#include "Road.h"
#include "Cell.h"

class Map
{
protected:
	std::string name;
	std::vector<Road*> roads;
	std::vector<Generator*> generators;
	std::vector<Cell*> cellsWithVehs;

public:
	Map(std::string name) : name(name) {}

	void addRoad(Road* road) {
		roads.push_back(road);
	}

	void addGenerator(Generator* generator) {
		generators.push_back(generator);
	}

	void setcellsWithVehs(std::vector<Cell*> cellsWithVehs) {
		this->cellsWithVehs = cellsWithVehs;
	}

	std::vector<Road*> getRoads() {
		return roads;
	}

	std::vector<Generator*> getGenerators() {
		return generators;
	}

	std::vector<Cell*> getCellsWithVehs() {
		return cellsWithVehs;
	}

	void setCellsWithVehs(std::vector<Cell*> newCellsWithVehs) {
		this->cellsWithVehs = newCellsWithVehs;
	}

	void createXML() {
	}
};

void linkCells(Cell* previousCell, Cell* nextCell) {
	previousCell->setNextCell(nextCell);
	nextCell->setPreviousCell(previousCell);
}

void linkCells(Generator* previousCell, Cell* nextCell) {
	previousCell->setNextCell(nextCell);
	nextCell->setPreviousCell(previousCell);
	previousCell->setMaxSpeed(nextCell->getMaxSpeed());
}
