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
    Cell() : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(0) {}

    Cell(int maxSpeed) : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(maxSpeed) {}

    ~Cell() {
        delete vehicle;
    }

    Vehicle* getVehicle() {
        return vehicle;
    }

    Cell* getRightCell() {
        return rightCell;
    }

    Cell* getLeftCell() {
        return leftCell;
    }

    Cell* getPreviousCell() {
        return previousCell;
    }

    Cell* getNextCell() {
        return nextCell;
    }

    int getMaxSpeed() {
        return maxSpeed;
    }

    void setVehicle(Vehicle* Vehicle) {
        this->vehicle = Vehicle;
    }

    void setRightCell(Cell* RightCell) {
        this->rightCell = RightCell;
    }

    void setLeftCell(Cell* LeftCell) {
        this->leftCell = LeftCell;
    }

    void setPreviousCell(Cell* PreviousCell) {
        this->previousCell = PreviousCell;
    }

    void setNextCell(Cell* NextCell) {
        this->nextCell = NextCell;
    }

    void setMaxSpeed(int maxSpeed) {
        this->maxSpeed = maxSpeed;
    }
};