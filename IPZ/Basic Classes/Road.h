#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Cell.h"
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
    char direction;

public:
    Road(std::string name, int length, int height, int maxSpeed, char direction);
    Road(int length, int height, int maxSpeed, char direction);
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
    void setDirection(char direction);
    char getDirection();
    std::string toString();
    std::string filterName(std::string rawName);
    void createJSON();
    void addLights(TrafficLights* newLight);
    std::vector<TrafficLights*> getLights();
};
