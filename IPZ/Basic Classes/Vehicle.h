#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;


class Vehicle {
public:
	int static IDcnt;

protected:
	std::string name;
	int speed;
	int ID;
	bool isObstacle;
	int originLane;

public:
	Vehicle(std::string name, int speed, bool isObstacle = false, int originLane = 0);
	Vehicle(int speed, bool isObstacle = false, int originLane = 0);
	std::string getName();
	int getID();
	int getSpeed();
	bool getIsObstacle();
	int getOriginLane();
	void setSpeed(int newSpeed);
	void setOriginLane(int originLane);
	void createJSON();
	bool checkIsObstacle();
};