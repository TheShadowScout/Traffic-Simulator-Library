#pragma once

#include "../Basic Classes/Crossing.h"

class BasicCrossing : public Crossing {
protected:
	std::vector<BasicCrossingInput*> inputsN;
	std::vector<BasicCrossingInput*> inputsE;
	std::vector<BasicCrossingInput*> inputsS;
	std::vector<BasicCrossingInput*> inputsW;

	void create();

public:
	BasicCrossing(std::string name, int height, int length, int maxSpeed);
	BasicCrossing(int height, int length, int maxSpeed);
	~BasicCrossing();
	void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight);
	void linkCellToCrossingInput(Cell* previousCell, char inputSide, int inputIndex);
	void updateCrossing();
	void addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex);
	std::string toString();

protected:
	void checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex);
};
