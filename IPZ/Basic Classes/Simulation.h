#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>

#include "Map.h"
#include "Cell.h"
#include "Vehicle.h"
#include "Statistics.h"
#include "Observer.h"

struct SpeedData {
	int newVehSpeed;
	Cell* destinationCell;
};

struct MoveData {
	SpeedData speedData;
	int newVehLane;
};

bool cmpMoveData(MoveData lhs, MoveData rhs);




class Simulation {
protected:
	std::vector<Cell*> cellsWithVehs;
	double randEventProb;
	Map* simMap;
	Statistics* simStats;
	std::vector<Observer*> observers;
	int seed;
	std::default_random_engine randomEngine;
	int minSafeSpace;
	bool shuffleIfCompetition;

public:
	Simulation(Map* simMap, double randEventProb, int minSafeSpace, int seed = NULL, bool shuffleIfCompetition = true);
	Map* getSimulationMap();
	Statistics* getSimulationStatistics();
	Observer* getSimulationObserver();
	std::string toString();
	void addObserver(Observer* observer);
	void saveStatisticsToFile(std::string outFolder = "StatisticsHistory/");
	void initiateSimulation();
	void transitionFunc();

protected:
	MoveData evalVehMove(Cell* vehCell);
	SpeedData evalNewVehSpeed(Cell* startCell, int curVehSpeed, bool* sawObstacle);
	void evalChangeLane(Cell* vehCell, std::vector<MoveData>* moves);
	void evalRandomEvent(Cell* vehCell, MoveData* vehMoveData);
	std::vector<Cell*> moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MoveData> vehMovesData);
};

