#pragma once

#include <iostream>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Vehicle.h"
#include "CarHolder.h"
#include "TrafficLights.h"

using boost::property_tree::ptree;

class Cell {
protected:
    Cell* rightCell;
    Cell* leftCell;
    Cell* previousCell;
    CarHolder* carHolder;
    int maxSpeed;
    bool isObstacleAhead;
    TrafficLights* trafficLight;

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
    bool getObstacleAhead();
    void setCarHolder(CarHolder* carHolder);
    void setVehicle(Vehicle* vehicle);
    void setRightCell(Cell* rightCell);
    void setLeftCell(Cell* leftCell);
    void setPreviousCell(Cell* previousCell);
    virtual void setNextCell(Cell* nextCell) = 0;
    void setMaxSpeed(int maxSpeed);
    void setObstacleAhead(bool isObstacleAhead);
	void createJSON();
    void setTrafficLight(TrafficLights* newLight);
    TrafficLights* getTrafficLight();
};
