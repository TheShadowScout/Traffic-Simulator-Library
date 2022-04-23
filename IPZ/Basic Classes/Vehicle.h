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

public:
	Vehicle(std::string name, int speed);
	Vehicle(int speed);
	std::string getName();
	int getID();
	int getSpeed();
	bool getIsObstacle();
	void setSpeed(int newSpeed);
	void createJSON();
};