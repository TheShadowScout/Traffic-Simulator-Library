#pragma once

#include <string>

#include "Cell.h"
#include "Vehicle.h"

class Observer {
public:
	int static IDcnt;

protected:
	std::string name;
	int ID;
	Cell* observationOriginCell;
	Vehicle* lastObservedVeh;
	int observedPassingVehsCnt;
	int distToSearch;

public:
	Observer(std::string name, Cell* observationOriginCell);
	Observer(Cell* observationOriginCell);
	std::string getName();
	int getObservedPassingVehsCnt();
	std::string toString();
	std::string filterName(std::string rawName);
	void checkVehPassing();
};
