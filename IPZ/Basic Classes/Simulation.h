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
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int breakingDist[7] = { 0, 1, 3, 6, 10, 15, 21 };
	double randEventProb;
	Map* simMap;
	Statistics* simStats;
	std::vector<Observer*> observers;
public:
	Simulation(Map* simMap, double randEventProb);
	void addObserver(Observer* observer);
	void initiateSimulation();
	void saveStatisticsToFile(std::string outFolder = "StatisticsHistory/");
	void transitionFunc();
	std::string toString();
	Statistics* getSimulationStatistics();
	Observer* getSimulationObserver();
	Map* getMap();
private:
	MovePrediction evalVehMove(Cell* vehCell, int curVehSpeed, bool canCallItself);
	MovePrediction evalChangeLane(Cell* vehCellAdjacentCell, int curVehSpeed);
	std::vector<Cell*> moveVehs(std::vector<Cell*> cellsWithVehs, std::vector<MovePrediction> vehMovesData);

};