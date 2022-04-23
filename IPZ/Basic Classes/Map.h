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
#include "Crossing.h"
#include "Cell.h"

using boost::property_tree::ptree;

class Map
{
protected:
	std::string name;
	std::vector<Road*> roads;
	std::vector<Generator*> generators;
	std::vector<Crossing*> crossings;

public:
	Map(std::string name);
	~Map();
	std::string getName();
	std::vector<Road*> getRoads();
	std::vector<Generator*> getGenerators();
	std::vector<Crossing*> getCrossings();
	int getMapPassableCellsCnt();
	void addRoad(Road* road);
	void addGenerator(Generator* generator);
	void addCrossing(Crossing* crossing);
	void fillWithVehs(double fillingDegree);
	std::vector<Cell*> getCellsWithVehs();
	void updateMap(std::vector<Cell*>* cellsWithVehs);
	void createJSON();
};



void linkCells(Cell* previousCell, Cell* nextCell);