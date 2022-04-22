#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Cell.h"
#include "RoadCell.h"
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
    std::vector<TrafficLights*> lights;

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
    std::vector<Cell*> fillWithVehs(double fillingDegree);
    void createJSON();
    void addLights(TrafficLights* newLight);
    std::vector<TrafficLights*> getLights();
};
