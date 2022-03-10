#pragma once

#include <iostream>
#include <string>

#include "Cell.h"
#include "Vehicle.h"

class Generator : public Cell
{
public:
	int static IDcnt;

protected:
	std::string name;
	int ID;
	double createVehProb;

public:
	Generator(std::string name, double createVehProb);
	Generator(double createVehProb);
	~Generator();
	std::string toString();
	std::string filterName(std::string rawName);
	bool createVeh();
};

