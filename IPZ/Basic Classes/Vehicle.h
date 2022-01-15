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
	Vehicle(std::string name, int speed, bool isObstacle = false) : name(name), speed(speed), isObstacle(isObstacle) {
		ID = IDcnt++;
	}

	Vehicle(int speed, bool isObstacle = false) : speed(speed), isObstacle(isObstacle) {
		ID = IDcnt++;
		name = std::to_string(ID);
	}

	std::string getName() {
		return name;
	}

	int getID() {
		return ID;
	}

	int getSpeed() {
		return speed;
	}

	void setSpeed(int newSpeed) {
		this->speed = newSpeed;
	}

	bool checkIsObstacle() {
		return isObstacle;
	}

	void createJSON() {
		ptree VehicleTree;
		std::string nameTree = "Vehicle" + std::to_string(getID());
		VehicleTree.put(nameTree + ".Name", getName());
		VehicleTree.put(nameTree + ".ID", getID());
		VehicleTree.put(nameTree + ".Speed", getSpeed());
		VehicleTree.put(nameTree + ".IsObstacle", checkIsObstacle());   // Tutaj nie jestem pewien czy nie należy przekonwertować bool na string?
		std::ostringstream oss;
		boost::property_tree::write_json(oss, VehicleTree);
		std::cout << oss.str();
	}


};