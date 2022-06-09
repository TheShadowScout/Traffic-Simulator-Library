#pragma once

#include "../Basic Classes/Crossing.h"
#include "../Basic Classes/SmartCrossingInput.h"

class SmartCrossing : public Crossing {
protected:
	std::vector<SmartCrossingInput*> inputsN;
	std::vector<SmartCrossingInput*> inputsE;
	std::vector<SmartCrossingInput*> inputsS;
	std::vector<SmartCrossingInput*> inputsW;

	void create();

public:
	SmartCrossing(std::string name, int height, int length, int maxSpeed);
	SmartCrossing(int height, int length, int maxSpeed);
	std::vector<SmartCrossingInput*> getInputsN();
	std::vector<SmartCrossingInput*> getInputsE();
	std::vector<SmartCrossingInput*> getInputsS();
	std::vector<SmartCrossingInput*> getInputsW();
	~SmartCrossing();
	void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight);
	void addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex);
	void linkCellToCrossingInput(Cell* previousCell, char inputSide, int inputIndex);
	void updateCrossing();
	int getPassableCellsCnt();
	std::string toString();

protected:
	void checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex);
};
