#pragma once

#include <iostream>
#include <fstream>
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

public:
	Simulation(Map* simMap, double randEventProb);
	Map* getSimulationMap();
	Statistics* getSimulationStatistics();
	Observer* getSimulationObserver();
	std::string toString();
	void addObserver(Observer* observer);
	void saveStatisticsToFile(std::string outFolder = "StatisticsHistory/");
	void initiateSimulation();
	void transitionFunc();

private:
	MovePrediction evalVehMove(Cell* vehCell, int curVehSpeed);
	std::vector<Cell*> moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MovePrediction> vehMovesData);
};
