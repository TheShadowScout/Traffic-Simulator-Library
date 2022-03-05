#pragma once

#include "Vehicle.h"

Vehicle::Vehicle(std::string name, int speed, bool isObstacle, int originLane) : name(name), speed(speed), isObstacle(isObstacle), originLane(originLane) {
	ID = IDcnt++;
}

Vehicle::Vehicle(int speed, bool isObstacle, int originLane) : speed(speed), isObstacle(isObstacle), originLane(originLane) {
	ID = IDcnt++;
	name = std::to_string(ID);
}

std::string Vehicle::getName() {
	return name;
}

int Vehicle::getID() {
	return ID;
}

int Vehicle::getSpeed() {
	return speed;
}

bool Vehicle::getIsObstacle() {
	return isObstacle;
}

int Vehicle::getOriginLane() {
	return originLane;
}

void Vehicle::setSpeed(int newSpeed) {
	this->speed = newSpeed;
}

void Vehicle::setOriginLane(int originLane) {
	this->originLane = originLane;
}

bool Vehicle::checkIsObstacle() {
	return isObstacle;
}

void Vehicle::createJSON() {
	ptree VehicleTree;
	std::string nameTree = "Vehicle" + std::to_string(getID());
	VehicleTree.put(nameTree + ".Name", getName());
	VehicleTree.put(nameTree + ".ID", getID());
	VehicleTree.put(nameTree + ".Speed", getSpeed());
	VehicleTree.put(nameTree + ".IsObstacle", checkIsObstacle());   // Tutaj nie jestem pewien czy nie nale¿y przekonwertowaæ bool na string?
	std::ostringstream oss;
	boost::property_tree::write_json(oss, VehicleTree);
	std::cout << oss.str();
}