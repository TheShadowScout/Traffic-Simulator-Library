#pragma once

#include "Statistics.h"

Statistics::Statistics(double simRandEventProb, int simMapPassableCellsCnt) : simRandEventProb(simRandEventProb), simMapPassableCellsCnt(simMapPassableCellsCnt), vehsCntSum(0), vehsSpeedsSum(0), iterationCnt(0) {
	time_t now;
	struct tm timeinfo;
	char buffer[80];
	time(&now);
	localtime_s(&timeinfo, &now);
	strftime(buffer, 80, "%X;%Y-%m-%d", &timeinfo);
	simInitiationTime = buffer;
}

double Statistics::getDensity()
{
	return 1.0 * vehsCntSum / iterationCnt;
}

std::string Statistics::getSimInitiationTime() {
	return simInitiationTime;
}

std::string Statistics::toString() {
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

void Statistics::updateStatistics(std::vector<Cell*> cellsWithVehs) {
	vehsCntSum += cellsWithVehs.size();
	for (Cell* vehCell : cellsWithVehs) {
		vehsSpeedsSum += vehCell->getVehicle()->getSpeed();
	}
	iterationCnt++;
}
