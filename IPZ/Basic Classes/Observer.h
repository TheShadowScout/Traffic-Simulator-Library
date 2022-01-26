#pragma once

#include <string>

#include "Cell.h"
#include "Vehicle.h"

class Observer {
public:
	int static IDcnt;
	Observer(std::string name, Cell* observationOriginCell);
	Observer(Cell* observationOriginCell);
	std::string getName();
	int getObservedPassingVehsCnt();
	std::string filterName(std::string rawName);
	void checkVehPassing();
	std::string toString();
protected:
	Cell* observationOriginCell;
	Vehicle* lastObservedVeh;
	int observedPassingVehsCnt;
	int distToSearch;
	std::string name;
	int ID;
};