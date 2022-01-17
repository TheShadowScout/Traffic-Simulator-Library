#pragma once

#include <iostream>
#include <string>

#include "Cell.h"
#include "Vehicle.h"

class Generator : public Cell
{
public:
	int static IDcnt;
	Generator(std::string name, double createVehProb);
	Generator(double createVehProb);
	~Generator();
	std::string filterName(std::string rawName);
	bool createVeh();
	std::string toString();
protected:
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int breakingDist[7] = { 0, 1, 3, 6, 10, 15, 21 };
	std::string name;
	int ID;
	double createVehProb;
};