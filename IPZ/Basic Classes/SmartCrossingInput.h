#pragma once

#include "BasicCrossingInput.h"

class SmartCrossingInput : public BasicCrossingInput
{
protected:
    int maxSpeedReminder;
    int drawnLaneReminder;
    std::vector<Cell*> destinationCells;

public:
    SmartCrossingInput(int maxSpeed);
    void setNextCell(Cell* nextCell);
    void setNextCell(Cell* nextCell, int weight);
    void addDestinatinCell(Cell* destinationCell);
    void drawLane();
    void checkCrossingEntryAvailability(int laneIndex);
};
