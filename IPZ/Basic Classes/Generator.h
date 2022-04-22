#pragma once

#include <iostream>
#include <string>

#include "Cell.h"
#include "RoadCell.h"
#include "Vehicle.h"

class Generator : public RoadCell
{
public:
	int static IDcnt;

protected:
	std::string name;
	int ID;
	double createVehProb;

public:
	Generator(std::string name, int maxSpeed, double createVehProb);
	Generator(int maxSpeed, double createVehProb);
	~Generator();
	std::string toString();
	std::string filterName(std::string rawName);
	bool createVeh();
};
