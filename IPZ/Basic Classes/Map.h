#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
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

	~Map() {
		for (Road* road : roads) {
			delete road;
		}
		for (Generator* generator : generators) {
			delete generator;
		}
	}

	std::string getName() {
		return name;
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

	int getMapPassableCellsCnt() {
		int passableCellsCnt = 0;
		for (Road* road : roads) {
			for (std::vector<Cell*> lane : road->getRoad()) {
				for (Cell* roadCell : lane) {
					Vehicle* cellVeh = roadCell->getVehicle();
					if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
						continue;
					}
					passableCellsCnt++;
				}
			}
		}
		for (Generator* generator : generators) {
			Vehicle* cellVeh = generator->getVehicle();
			if (cellVeh != nullptr && cellVeh->getIsObstacle() == true) {
				continue;
			}
			passableCellsCnt++;
		}
		return passableCellsCnt;
	}

	void setCellsWithVehs(std::vector<Cell*> CellsWithVehs) {
		this->cellsWithVehs = CellsWithVehs;
	}

	void addRoad(Road* road) {
		roads.push_back(road);
	}

	void addGenerator(Generator* generator) {
		generators.push_back(generator);
	}

	void fillWithVehs(double fillingDegree) {
		int passableCellsCnt = getMapPassableCellsCnt();
		int vehsToGenerateCnt = std::min((int)(std::round(fillingDegree * passableCellsCnt)), passableCellsCnt);
		int generatedVehsCnt = 0;
		while (generatedVehsCnt < vehsToGenerateCnt) {
			for (Road* road : roads) {
				for (std::vector<Cell*> lane : road->getRoad()) {
					for (Cell* roadCell : lane) {
						if (roadCell->getVehicle() == nullptr) {
							if (1.0 * std::rand() / RAND_MAX <= fillingDegree) {
								roadCell->setVehicle(new Vehicle(0));
								cellsWithVehs.push_back(roadCell);
								generatedVehsCnt++;
								if (generatedVehsCnt >= vehsToGenerateCnt) {
									return;
								}
							}
						}
					}
				}
			}
			for (Generator* generator : generators) {
				if (generator->getVehicle() == nullptr) {
					if (1.0 * std::rand() / RAND_MAX <= fillingDegree) {
						generator->setVehicle(new Vehicle(0));
						cellsWithVehs.push_back(generator);
						generatedVehsCnt++;
						if (generatedVehsCnt >= vehsToGenerateCnt) {
							return;
						}
					}
				}
			}
		}
	}

	void createJSON() {
		ptree mapTree;
		mapTree.put("Map.Name", getName());
		
		for (int i = 0; i < roads.size(); i++) {
			//mapTree.put("Map.Road", roads[i]->createJSON());
			std::string nameTree = "Map.Road" + std::to_string(roads[i]->getID());
			mapTree.put(nameTree + ".Name", roads[i]->getName());
			mapTree.put(nameTree + ".ID", roads[i]->getID());
			mapTree.put(nameTree + ".Length", roads[i]->getLength());
			mapTree.put(nameTree + ".Height", roads[i]->getHeight());
		}
		std::ostringstream oss;
		boost::property_tree::write_json(oss, mapTree);
		std::cout << oss.str();
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
