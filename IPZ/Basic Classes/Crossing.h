#pragma once

#include <cmath>

#include "RoadCell.h"
#include "BasicCrossingInput.h"

class Crossing {
public:
	int static IDcnt;

protected:
	int ID;
	std::string name;
	int crossingHeight;
	int crossingLength;
	int crossingMaxSpeed;
	std::vector<std::vector<CarHolder*>> carHolderMatrix;
	std::vector<RoadCell*> outputN;
	std::vector<RoadCell*> outputE;
	std::vector<RoadCell*> outputS;
	std::vector<RoadCell*> outputW;
	std::vector<std::vector<RoadCell*>> crossingLanes;
	std::vector<TrafficLights*> trafficLights;

	void create();

public:
	Crossing(std::string name, int crossingHeight, int crossingLength, int crossingMaxSpeed);
	Crossing(int crossingHeight, int crossingLength, int crossingMaxSpeed);
	~Crossing();
	std::vector<TrafficLights*> getTrafficLights();
	virtual void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight) = 0;
	virtual void linkRoadLaneToCrossing(Cell* previousCell, char inputSide, int inputIndex) = 0;
	void linkRoadLaneToCrossing(char outputSide, int outputIndex, Cell* nextCell);
	virtual void updateCrossing() = 0;
	virtual void addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex) = 0;
	std::string toString();
};
