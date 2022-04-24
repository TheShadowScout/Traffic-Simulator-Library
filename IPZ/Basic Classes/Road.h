#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Cell.h"
#include "RoadCell.h"
#include "Obstacle.h"
#include "TrafficLights.h"

using boost::property_tree::ptree;

class Road {
public:
    int static IDcnt;
    std::vector<Cell*> head;
    std::vector<Cell*> tail;

protected:
    int ID;
    int maxSpeed;
    int length;
    int height;
    std::string name;
    std::vector<std::vector<Cell*>> road;
    std::vector<TrafficLights*> trafficLights;

public:
    Road(std::string name, int length, int height, int maxSpeed);
    Road(int length, int height, int maxSpeed);
    ~Road();
    void createRoad();
    int getMaxSpeed();
    int getID();
    std::string getName();
    int getLength();
    int getHeight();
    std::vector<std::vector<Cell*>> getRoad();
    void setMaxSpeed(int maxSpeed);
    void setName(std::string name);
    std::string toString();
    std::string filterName(std::string rawName);
    void fillWithVehs(double fillingDegree);
    void createJSON();
    void addTrafficLightsToOneLane(TrafficLights* newLight, int distanceFromHead, int lane);
    void addTrafficLightsToAllLanes(TrafficLights* newLight, int distanceFromHead);
    std::vector<TrafficLights*> getTrafficLights();
    void addObstacle(int distanceFromHead, int lane, int spotDistance = 0);
};
