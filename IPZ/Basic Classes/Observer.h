#pragma once

#include "Cell.h"

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
	void checkVehPassing();
	std::string toString();
};
