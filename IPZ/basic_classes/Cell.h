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

    void setVehicle(Vehicle* newVehicle) {
        this->vehicle = newVehicle;
    }

    void setRightCell(Cell* newRightCell) {
        this->rightCell = newRightCell;
    }

    void setLeftCell(Cell* newLeftCell) {
        this->leftCell = newLeftCell;
    }

    void setPreviousCell(Cell* newPreviousCell) {
        this->previousCell = newPreviousCell;
    }

    void setNextCell(Cell* newNextCell) {
        this->nextCell = newNextCell;
    }

    void setMaxSpeed(int maxSpeed) {
        this->maxSpeed = maxSpeed;
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
};