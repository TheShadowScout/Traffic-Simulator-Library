#pragma once

#include "Cell.h"

class RoadCell : public Cell
{
protected:
	Cell* nextCell;

public:
	RoadCell();
	RoadCell(int maxSpeed);
	Cell* getNextCell();
	void setNextCell(Cell* nextCell);
};