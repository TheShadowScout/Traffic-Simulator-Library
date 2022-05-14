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
	int ID;
	int speed;
	bool isObstacle;

	void create();

public:
	Vehicle(std::string name, int speed);
	Vehicle(int speed);
	std::string getName();
	int getID();
	int getSpeed();
	void setSpeed(int newSpeed);
	bool getIsObstacle();
	void createJSON();
};