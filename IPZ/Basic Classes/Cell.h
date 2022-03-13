#pragma once

#include <iostream>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Vehicle.h"
#include "CarHolder.h"

using boost::property_tree::ptree;

class Cell {
protected:
    Cell* rightCell;
    Cell* leftCell;
    Cell* previousCell;
    CarHolder* carHolder;
    int maxSpeed;
    bool obstacleAhead;

public:
    Cell();
    Cell(int maxSpeed);
    ~Cell();
    Vehicle* getVehicle();
    Cell* getRightCell();
    Cell* getLeftCell();
    Cell* getPreviousCell();
    virtual Cell* getNextCell() = 0;
    int getMaxSpeed();
    void setCarHolder(CarHolder* carHolder);
    void setVehicle(Vehicle* Vehicle);
    void setRightCell(Cell* RightCell);
    void setLeftCell(Cell* LeftCell);
    void setPreviousCell(Cell* PreviousCell);
    virtual void setNextCell(Cell* nextCell) = 0;
    void setMaxSpeed(int maxSpeed);
    void updateObstacleAhead();
    bool checkObstacleAhead();
	void createJSON();
};
