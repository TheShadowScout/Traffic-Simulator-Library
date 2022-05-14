#pragma once

#include "RoadCell.h"

class Generator : public RoadCell
{
public:
	int static IDcnt;

protected:
	std::string name;
	int ID;
	double createVehProb;

	void create();

public:
	Generator(std::string name, int maxSpeed, double createVehProb);
	Generator(int maxSpeed, double createVehProb);
	int getID();
	std::string getName();
	bool createVeh();
	std::string toString();
};
