#pragma once

#include "Map.h"
	
Map::Map(std::string name) : name(name) {
	if(name == "")
		throw std::invalid_argument("Map must have a name");
}

Map::~Map() {
		for (Road* road : roads) {
			delete road;
		}
		for (Generator* generator : generators) {
			delete generator;
		}
		for (Crossing* crossing : crossings) {
			delete crossing;
		}
	}

std::string Map::getName() {
		return name;
	}

std::vector<Road*> Map::getRoads() {
	return roads;
}

std::vector<Generator*> Map::getGenerators() {
	return generators;
}

std::vector<Crossing*> Map::getCrossings() {
	return crossings;
}

int Map::getMapPassableCellsCnt() {
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

void Map::addRoad(Road* road) {
	roads.push_back(road);
}

void Map::addGenerator(Generator* generator) {
	generators.push_back(generator);
}

void Map::addCrossing(Crossing* crossing) {
	crossings.push_back(crossing);
}

void Map::fillWithVehs(double fillingDegree) {
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
					generatedVehsCnt++;
					if (generatedVehsCnt >= vehsToGenerateCnt) {
						return;
					}
				}
			}
		}
	}
}

std::vector<Cell*> Map::getCellsWithVehs() {
	std::vector<Cell*> cellsWithVehs;
	for (Road* roads : roads) {
		for (std::vector<Cell*> roadLane : roads->getRoad()) {
			for (Cell* roadCell : roadLane) {
				Vehicle* cellVeh = roadCell->getVehicle();
				if (cellVeh != nullptr && cellVeh->getIsObstacle() == false) {
					cellsWithVehs.push_back(roadCell);
				}
			}
		}
	}
	for (Generator* generator : generators) {
		if (generator->getVehicle() != nullptr) {
			cellsWithVehs.push_back(generator);
		}
	}
	return cellsWithVehs;
}

void Map::updateMap(std::vector<Cell*>* cellsWithVehs) {
	for (Generator* generator : generators) {
		if (generator->createVeh() == true) {
			cellsWithVehs->push_back(generator);
		}
	}
	for (Crossing* crossing : crossings) {
		crossing->updateCrossing();
		std::vector<TrafficLights*> crossingLights = crossing->getTrafficLights();
		for (TrafficLights* crossingLight : crossingLights) {
			crossingLight->updateTrafficLights();
		}
	}
	for (Road* road : roads) {
		std::vector<TrafficLights*> roadLights = road->getTrafficLights();
		for (TrafficLights* roadLight : roadLights) {
			roadLight->updateTrafficLights();
		}
	}
}

//void Map::createJSON() {
//	ptree mapTree;
//	mapTree.put("Map.Name", getName());
//
//	for (int i = 0; i < roads.size(); i++) {
//		//mapTree.put("Map.Road", roads[i]->createJSON());
//		std::string nameTree = "Map.Road" + std::to_string(roads[i]->getID());
//		mapTree.put(nameTree + ".Name", roads[i]->getName());
//		mapTree.put(nameTree + ".ID", roads[i]->getID());
//		mapTree.put(nameTree + ".Length", roads[i]->getLength());
//		mapTree.put(nameTree + ".Height", roads[i]->getHeight());
//	}
//	std::ostringstream oss;
//	boost::property_tree::write_json(oss, mapTree);
//	std::cout << oss.str();
//}

void Map::createJSON() {
	ptree mapTree;
	mapTree.put("Map.Name", getName());

	for (unsigned int i = 0; i < roads.size(); i++) {
		//mapTree.put("Map.Road", roads[i]->createJSON());
		std::string nameTree = "Map.Road" + std::to_string(roads[i]->getID());
		mapTree.put(nameTree + ".Name", roads[i]->getName());
		mapTree.put(nameTree + ".ID", roads[i]->getID());
		mapTree.put(nameTree + ".Length", roads[i]->getLength());
		mapTree.put(nameTree + ".Height", roads[i]->getHeight());
	}
	std::vector<Cell*> cellsWithVehs = getCellsWithVehs();
	for (unsigned int i = 0; i < cellsWithVehs.size(); i++) {
		std::string nameTree = "Map.Cell";
		mapTree.put(nameTree + ".MaxSpeed", cellsWithVehs[i]->getMaxSpeed());
		nameTree = "Map.Cell.Vechicle" + std::to_string(cellsWithVehs[i]->getVehicle()->getID());
		mapTree.put(nameTree + ".Name", cellsWithVehs[i]->getVehicle()->getName());
		mapTree.put(nameTree + ".Speed", std::to_string(cellsWithVehs[i]->getVehicle()->getSpeed()));
	}

	std::ostringstream oss;
	boost::property_tree::write_json(oss, mapTree);
	//std::cout << oss.str();
	std::ofstream jsonFile("Map.json");
	jsonFile << oss.str();
	jsonFile.close();
}



void linkCells(Cell* previousCell, Cell* nextCell) {
	previousCell->setNextCell(nextCell);
	nextCell->setPreviousCell(previousCell);
}
