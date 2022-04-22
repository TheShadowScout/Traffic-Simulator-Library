#pragma once

#include "Cell.h"

Cell::Cell() : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), carHolder(nullptr), maxSpeed(0), obstacleAhead(false), light(nullptr) {}

Cell::Cell(int maxSpeed) : rightCell(nullptr), leftCell(nullptr), previousCell(nullptr), carHolder(nullptr), maxSpeed(maxSpeed), obstacleAhead(false), light(nullptr) {
    if(maxSpeed > 6 || maxSpeed < 1)
        throw std::invalid_argument("Max speed must be in range between 1 and 6");
}

Cell::~Cell() {
    delete carHolder;
}

Vehicle* Cell::getVehicle() {
    return carHolder->getVehicle();
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

int Cell::getMaxSpeed() {
    return maxSpeed;
}

void Cell::setVehicle(Vehicle* vehicle) {
    this->carHolder->setVehicle(vehicle);
}

void Cell::setRightCell(Cell* rightCell) {
    this->rightCell = rightCell;
}

void Cell::setLeftCell(Cell* leftCell) {
    this->leftCell = leftCell;
}

void Cell::setPreviousCell(Cell* previousCell) {
    this->previousCell = previousCell;
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

void Cell::setCarHolder(CarHolder* carHolder)
{
    this->carHolder = carHolder;
}

// Czy w statystykach pojedynczej komórki jest koniecznoœæ zapisanie informacji o najbli¿szych do niej komórek, czy te¿ nie?
   // Zauwa¿y³em równie¿, ¿e komórki nie posiadaj¹ swojego ID czy te¿ to nie jest potrzebne.
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
