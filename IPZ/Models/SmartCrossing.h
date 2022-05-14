#pragma once

#include "../Basic Classes/Crossing.h"
#include "../Basic Classes/SmartCrossingInput.h"

class SmartCrossing : public Crossing {
protected:
	std::vector<SmartCrossingInput*> inputN;
	std::vector<SmartCrossingInput*> inputE;
	std::vector<SmartCrossingInput*> inputS;
	std::vector<SmartCrossingInput*> inputW;

	void create();

public:
	SmartCrossing(std::string name, int crossingHeight, int crossingLength, int crossingMaxSpeed);
	SmartCrossing(int crossingHeight, int crossingLength, int crossingMaxSpeed);
	~SmartCrossing();
	void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight);
	void addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex);
	void linkRoadLaneToCrossing(Cell* previousCell, char inputSide, int inputIndex);
	void updateCrossing();

protected:
	void checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex);
};
