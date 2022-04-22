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
#include "MovePrediction.h"
#include "Statistics.h"
#include "Observer.h"

class Simulation {
protected:
	double randEventProb;
	Map* simMap;
	Statistics* simStats;
	std::vector<Observer*> observers;
	int seed;
	std::default_random_engine randomEngine;
	int viewDist;
	int minSafeSpace;
	bool shuffleIfCompetition;

public:
	Simulation(Map* simMap, double randEventProb, int viewDist, int minSafeSpace, int seed = NULL, bool shuffleIfCompetition = true);
	Map* getSimulationMap();
	Statistics* getSimulationStatistics();
	Observer* getSimulationObserver();
	std::string toString();
	void addObserver(Observer* observer);
	void saveStatisticsToFile(std::string outFolder = "StatisticsHistory/");
	void initiateSimulation();
	void transitionFunc();

protected:
	MovePrediction evalVehMove(Cell* vehCell);
	int evalNewVehSpeed(Cell* startCell, int curVehSpeed, bool* sawObstacle);
	void evalChangeLane(Cell* vehCell, std::vector<MovePrediction>* moves);
	std::vector<Cell*> moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MovePrediction> vehMovesData);
};
