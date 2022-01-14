#pragma once

#include <string>
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
	Statistics(double simRandEventProb, int simMapPassableCellsCnt) : simRandEventProb(simRandEventProb), simMapPassableCellsCnt(simMapPassableCellsCnt), vehsCntSum(0), vehsSpeedsSum(0), iterationCnt(0) {
		time_t now;
		struct tm* timeinfo;
		char buffer[80];
		time(&now);
		timeinfo = localtime(&now);
		strftime(buffer, 80, "%X;%Y-%m-%d", timeinfo);
		simInitiationTime = buffer;
	}

	std::string getSimInitiationTime() {
		return simInitiationTime;
	}

	void updateStatistics(std::vector<Cell*> cellsWithVehs) {
		vehsCntSum += cellsWithVehs.size();
		for (Cell* vehCell : cellsWithVehs) {
			vehsSpeedsSum += vehCell->getVehicle()->getSpeed();
		}
		iterationCnt++;
	}

	std::string toString() {
		std::string tempStr = "";
		tempStr += "time;date;randomEventProbability;meanMapFillingDegree;meanVehiclesSpeed\n";
		tempStr += simInitiationTime;
		tempStr += ";";
		tempStr += std::to_string(simRandEventProb);
		tempStr += ";";
		tempStr += std::to_string(1.0 * vehsCntSum / iterationCnt);
		tempStr += ";";
		tempStr += std::to_string(1.0 * vehsSpeedsSum / vehsCntSum);
		tempStr += "\n";
		return tempStr;
	}
};
