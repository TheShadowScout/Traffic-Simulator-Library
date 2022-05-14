#pragma once

#include "Crossing.h"

class BasicCrossing : public Crossing {
protected:
	std::vector<BasicCrossingInput*> inputN;
	std::vector<BasicCrossingInput*> inputE;
	std::vector<BasicCrossingInput*> inputS;
	std::vector<BasicCrossingInput*> inputW;

	void create();

public:
	BasicCrossing(std::string name, int crossingHeight, int crossingLength, int crossingMaxSpeed);
	BasicCrossing(int crossingHeight, int crossingLength, int crossingMaxSpeed);
	~BasicCrossing();
	void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight);
	void linkRoadLaneToCrossing(Cell* previousCell, char inputSide, int inputIndex);
	void linkRoadLaneToCrossing(char outputSide, int outputIndex, Cell* nextCell);
	void updateCrossing();
	void addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex);

protected:
	void checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex);
};
