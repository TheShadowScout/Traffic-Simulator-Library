#pragma once
#include "Vehicle.h"

class Cell {
protected:
    Cell* rightCell;
    Cell* leftCell;
    Cell* previousCell;
    Cell* nextCell;
    Vehicle* vehicle;
    int maxSpeed;

public:
    Cell();
    Cell(int maxSpeed);
    ~Cell();
    Vehicle* getVehicle();
    Cell* getRightCell();
    Cell* getLeftCell();
    Cell* getPreviousCell();
    Cell* getNextCell();
    int getMaxSpeed();
    void setVehicle(Vehicle* Vehicle);
    void setRightCell(Cell* RightCell);
    void setLeftCell(Cell* LeftCell);
    void setPreviousCell(Cell* PreviousCell);
    void setNextCell(Cell* NextCell);
    void setMaxSpeed(int maxSpeed);
};