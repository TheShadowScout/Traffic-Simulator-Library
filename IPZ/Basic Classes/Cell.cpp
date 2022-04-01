#pragma once

#include "Cell.h"

Cell::Cell() : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(0), obstacleAhead(false), light(nullptr) {}

Cell::Cell(int maxSpeed) : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), nextCell(nullptr), vehicle(nullptr), maxSpeed(maxSpeed), obstacleAhead(false), light(nullptr) {}

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

void Cell::updateObstacleAhead() {
    obstacleAhead = true;
}

bool Cell::checkObstacleAhead() {
    return obstacleAhead;
}

// Czy w statystykach pojedynczej kom�rki jest konieczno�� zapisanie informacji o najbli�szych do niej kom�rek, czy te� nie?
   // Zauwa�y�em r�wnie�, �e kom�rki nie posiadaj� swojego ID czy te� to nie jest potrzebne.
void Cell::createJSON() {
    ptree CellTree;
    std::string nameTree = "Cell";
    CellTree.put(nameTree + ".MaxSpeed", getMaxSpeed());

    std::ostringstream oss;
    boost::property_tree::write_json(oss, CellTree);
    std::cout << oss.str();
}

void Cell::setLight(TrafficLights* newLight)
{
    light = newLight;
}

TrafficLights* Cell::getLight()
{
    return light;
}
