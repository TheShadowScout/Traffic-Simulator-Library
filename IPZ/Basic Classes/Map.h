#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "Generator.h"
#include "Road.h"
#include "Cell.h"

#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

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
	/*
	std::vector<Cell*> getCellsWithVehs() {
		return this->cellsWithVehs;
	}
	*/
	std::string getName() {
		return name;
	}

	void createJSON() {
		ptree mapTree;
		mapTree.put("Map.Name", getName());
		
		for (int i = 0; i < roads.capacity(); i++) {
			//mapTree.put("Map.Road", roads[i]->createJSON());
			std::string nameTree = "Map.Road" + std::to_string(roads[i]->getID());
			mapTree.put(nameTree + ".Name", roads[i]->getName());
			mapTree.put(nameTree + ".ID", roads[i]->getID());
			mapTree.put(nameTree + ".Length", roads[i]->getLength());
			mapTree.put(nameTree + ".Height", roads[i]->getHeight());
		}
		for (int i = 0; i < cellsWithVehs.size(); i++) {
			std::string nameTree = "Map.Cell";
			mapTree.put(nameTree + ".MaxSpeed", cellsWithVehs[i]->getMaxSpeed());
			nameTree = "Map.Cell.Vechicle" + std::to_string(cellsWithVehs[i]->getVehicle()->getID());
			mapTree.put(nameTree + ".Name", cellsWithVehs[i]->getVehicle()->getName());
			mapTree.put(nameTree + ".Speed", std::to_string(cellsWithVehs[i]->getVehicle()->getSpeed()));
		}

		std::ostringstream oss;
		boost::property_tree::write_json(oss, mapTree);
		//std::cout << oss.str();
		std::ofstream jsonFile("JSON.txt");
		jsonFile << oss.str();
		jsonFile.close();
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
