#pragma once

#include "RoadCell.h"
#include "Obstacle.h"
#include "TrafficLights.h"

using boost::property_tree::ptree;

class Road {
public:
    int static IDcnt;

protected:
    int ID;
    int maxSpeed;
    int length;
    int height;
    std::string name;
    std::vector<std::vector<Cell*>> lanes;
    std::vector<TrafficLights*> trafficLights;

    void create();

public:
    Road(std::string name, int length, int height, int maxSpeed);
    Road(int length, int height, int maxSpeed);
    ~Road();
    Cell* getLaneHead(int lane);
    Cell* getLaneTail(int lane);
    int getMaxSpeed();
    int getID();
    std::string getName();
    int getLength();
    int getHeight();
    std::vector<std::vector<Cell*>> getLanes();
    int getPassableCellsCnt();
    std::vector<Cell*> getCellsWithVehs();
    std::vector<TrafficLights*> getTrafficLights();
    void addTrafficLightsToOneLane(TrafficLights* newLight, int distanceFromHead, int lane);
    void addTrafficLightsToAllLanes(TrafficLights* newLight, int distanceFromHead);
    void addObstacle(int distanceFromHead, int lane, int spotDistance = 0);
    void fillWithVehs(double fillingDegree);
    void createJSON();
    std::string toString();
};
