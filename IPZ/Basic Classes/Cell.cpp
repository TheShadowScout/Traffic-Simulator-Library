#pragma once
#include "Cell.h"

Cell::Cell() : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(0) {}

Cell::Cell(int maxSpeed) : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(maxSpeed) {}

Cell::~Cell() {
    delete vehicle;
}

Vehicle* Cell::getVehicle() {
    return vehicle;
}

Cell* Cell::getRightCell() {
    return rightCell;
}

Cell* Cell::getLeftCell() {
    return leftCell;
}

Cell* Cell::getPreviousCell() {
    return previousCell;
}

Cell* Cell::getNextCell() {
    return nextCell;
}

int Cell::getMaxSpeed() {
    return maxSpeed;
}

void Cell::setVehicle(Vehicle* Vehicle) {
    this->vehicle = Vehicle;
}

void Cell::setRightCell(Cell* RightCell) {
    this->rightCell = RightCell;
}

void Cell::setLeftCell(Cell* LeftCell) {
    this->leftCell = LeftCell;
}

void Cell::setPreviousCell(Cell* PreviousCell) {
    this->previousCell = PreviousCell;
}

void Cell::setNextCell(Cell* NextCell) {
    this->nextCell = NextCell;
}

void Cell::setMaxSpeed(int maxSpeed) {
    this->maxSpeed = maxSpeed;
}