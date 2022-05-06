#pragma once

#include "Vehicle.h"
#include "CarHolder.h"
#include "TrafficLights.h"

using boost::property_tree::ptree;

class Cell {
protected:
    int maxSpeed;
    CarHolder* carHolder;
    Cell* rightCell;
    Cell* leftCell;
    Cell* previousCell;
    TrafficLights* trafficLight;
    bool isObstacleAhead;

public:
    Cell();
    Cell(int maxSpeed);
    ~Cell();
    int getMaxSpeed();
    void setMaxSpeed(int maxSpeed);
    void setCarHolder(CarHolder* carHolder);
    Vehicle* getVehicle();
    void setVehicle(Vehicle* vehicle);
    Cell* getRightCell();
    void setRightCell(Cell* rightCell);
    Cell* getLeftCell();
    void setLeftCell(Cell* leftCell);
    Cell* getPreviousCell();
    void setPreviousCell(Cell* previousCell);
    virtual Cell* getNextCell() = 0;
    virtual void setNextCell(Cell* nextCell) = 0;
    TrafficLights* getTrafficLight();
    void setTrafficLight(TrafficLights* newLight);
    bool getObstacleAhead();
    void setObstacleAhead(bool isObstacleAhead);
	void createJSON();
};
