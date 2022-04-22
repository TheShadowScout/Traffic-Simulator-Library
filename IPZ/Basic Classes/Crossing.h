#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "CarHolder.h"
#include "RoadCell.h"
#include "CrossingInput.h"

class Crossing {
protected:
	int crossingHeight;
	int crossingLength;
	int crossingMaxSpeed;
	std::vector<std::vector<CarHolder*>> carHolderMatrix;
	std::vector<CrossingInput*> inputN;
	std::vector<CrossingInput*> inputE;
	std::vector<CrossingInput*> inputS;
	std::vector<CrossingInput*> inputW;
	std::vector<RoadCell*> outputN;
	std::vector<RoadCell*> outputE;
	std::vector<RoadCell*> outputS;
	std::vector<RoadCell*> outputW;

public:
	Crossing(int crossingHeight, int crossingLength, int crossingMaxSpeed);
	~Crossing();
	void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight);
	void linkRoadLaneToCrossing(Cell* previousCell, char inputSide, int inputIndex);
	void linkRoadLaneToCrossing(char outputSide, int outputIndex, Cell* nextCell);
	std::string toString();

protected:
	void checkParametersAreCorrect(char inputSide, int inputIndex, char outputSide, int outputIndex);
};
