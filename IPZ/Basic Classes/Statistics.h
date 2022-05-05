#pragma once

#include <ctime>
#include <vector>

#include "Cell.h"
#include "Vehicle.h"

class Statistics {
protected:
	double simRandEventProb;
	int simMapPassableCellsCnt;
	int vehsCntSum;
	int vehsSpeedsSum;
	int iterationCnt;
	std::string simInitiationTime;

public:
	Statistics(double simRandEventProb, int simMapPassableCellsCnt);
	double getDensity();
	std::string getSimInitiationTime();
	void updateStatistics(std::vector<Cell*> cellsWithVehs);
	std::string toString();
};
