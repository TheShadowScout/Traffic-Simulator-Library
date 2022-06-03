#pragma once

#include <ctime>
#include <vector>

#include "Cell.h"

class Statistics {
protected:
	double simRandEventProb;
	int minSafeSpace;
	int simMapPassableCellsCnt;
	int vehsCntSum;
	int vehsSpeedsSum;
	int iterationCnt;
	std::string simInitiationTime;

public:
	Statistics(double simRandEventProb, int minSafeSpace, int simMapPassableCellsCnt);
	double getDensity();
	std::string getSimInitiationTime();
	void updateStatistics(std::vector<Cell*> cellsWithVehs);
	std::string toString();
};
