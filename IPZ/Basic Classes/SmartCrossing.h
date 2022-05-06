#pragma once

#include "Crossing.h"

#include "SmartCrossingInput.h"

class SmartCrossing : public Crossing {
protected:
	std::vector<SmartCrossingInput*> inputN;
	std::vector<SmartCrossingInput*> inputE;
	std::vector<SmartCrossingInput*> inputS;
	std::vector<SmartCrossingInput*> inputW;
public:
	SmartCrossing(int crossingHeight, int crossingLength, int crossingMaxSpeed);
	~SmartCrossing();
	void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight);
	void linkRoadLaneToCrossing(Cell* previousCell, char inputSide, int inputIndex);
	void linkRoadLaneToCrossing(char outputSide, int outputIndex, Cell* nextCell);
	void updateCrossing();
	void addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex);

protected:
	void checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex);
};
