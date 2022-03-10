#pragma once

#include <iostream>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Vehicle.h"

using boost::property_tree::ptree;

class Cell {
protected:
    Cell* rightCell;
    Cell* leftCell;
    Cell* previousCell;
    Cell* nextCell;
    Vehicle* vehicle;
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
    Cell* getNextCell();
    int getMaxSpeed();
    void setVehicle(Vehicle* Vehicle);
    void setRightCell(Cell* RightCell);
    void setLeftCell(Cell* LeftCell);
    void setPreviousCell(Cell* PreviousCell);
    void setNextCell(Cell* NextCell);
    void setMaxSpeed(int maxSpeed);
    void updateObstacleAhead();
    bool checkObstacleAhead();
	void createJSON();
};
