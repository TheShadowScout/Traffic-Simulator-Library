#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

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
	void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight);
};
