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
	int height;
	int length;
	int maxSpeed;
	std::vector<std::vector<CarHolder*>> carHolderMatrix;
	std::vector<RoadCell*> outputsN;
	std::vector<RoadCell*> outputsE;
	std::vector<RoadCell*> outputsS;
	std::vector<RoadCell*> outputsW;
	std::vector<std::vector<RoadCell*>> lanes;
	std::vector<TrafficLights*> trafficLights;

	void create();

public:
	Crossing(std::string name, int height, int length, int maxSpeed);
	Crossing(int height, int length, int maxSpeed);
	virtual ~Crossing();
	int getID();
	int getHeight();
	int getLength();
	std::vector<RoadCell*> getOutputsN();
	std::vector<RoadCell*> getOutputsW();
	std::vector<RoadCell*> getOutputsS();
	std::vector<RoadCell*> getOutputsE();
	std::string getName();
	std::vector<TrafficLights*> getTrafficLights();
	std::vector<std::vector<CarHolder*>> getCarHolderMatrix();
	virtual void addNewCrossingLane(char inputSide, int inputIndex, char outputSide, int outputIndex, int laneWeight) = 0;
	virtual void linkCellToCrossingInput(Cell* previousCell, char inputSide, int inputIndex) = 0;
	void linkCellToCrossingOutput(char outputSide, int outputIndex, Cell* nextCell);
	virtual void updateCrossing() = 0;
	virtual void addTrafficLights(TrafficLights* newLight, char inputSide, int inputIndex) = 0;
	virtual int getPassableCellsCnt() = 0;
	virtual std::string toString() = 0;
};
