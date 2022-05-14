#pragma once

#include <algorithm>
#include <cmath>

#include "Road.h"
#include "Generator.h"
#include "Crossing.h"
#include "LaneEndsMerge.h"

using boost::property_tree::ptree;

class Map {
protected:
	std::string name;
	std::vector<Road*> roads;
	std::vector<Generator*> generators;
	std::vector<Crossing*> crossings;
	std::vector<LaneEndsMerge*> laneEndsMerges;

public:
	Map(std::string name);
	~Map();
	std::string getName();
	std::vector<Road*> getRoads();
	std::vector<Generator*> getGenerators();
	std::vector<Crossing*> getCrossings();
	std::vector<LaneEndsMerge*> getLaneEndsMerges();
	int getMapPassableCellsCnt();
	std::vector<Cell*> getCellsWithVehs();
	void addRoad(Road* road);
	void addGenerator(Generator* generator);
	void addCrossing(Crossing* crossing);
	void addLaneEndsMerge(LaneEndsMerge* laneEndsMerge);
	void fillWithVehs(double fillingDegree);
	void updateMap(std::vector<Cell*>* cellsWithVehs);
	void createJSON();
	std::string toString();
};



void linkCells(Cell* previousCell, Cell* nextCell);