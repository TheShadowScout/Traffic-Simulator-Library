#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Generator.h"
#include "Road.h"
#include "Cell.h"

using boost::property_tree::ptree;

class Map
{
protected:
	std::string name;
	std::vector<Road*> roads;
	std::vector<Generator*> generators;
	std::vector<Cell*> cellsWithVehs;

public:
	Map(std::string name);
	~Map();
	std::string getName();
	std::vector<Road*> getRoads();
	std::vector<Generator*> getGenerators();
	std::vector<Cell*> getCellsWithVehs();
	int getMapPassableCellsCnt();
	void setCellsWithVehs(std::vector<Cell*> CellsWithVehs);
	void addRoad(Road* road);
	void addGenerator(Generator* generator);
	void addCellsWithVehs(std::vector<Cell*> newCellsWithVehs);
	void fillWithVehs(double fillingDegree);
	void updateObstacleAheadWarnings(int stepsBackCnt);
	void createJSON();
};



void linkCells(Cell* previousCell, Cell* nextCell);
void linkCells(Generator* previousCell, Cell* nextCell);