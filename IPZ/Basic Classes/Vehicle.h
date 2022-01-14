#pragma once

#include <string>

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
	Vehicle(std::string name, int speed, bool isObstacle = false, int originLane = 0) : name(name), speed(speed), isObstacle(isObstacle), originLane(originLane) {
		ID = IDcnt++;
	}

	Vehicle(int speed, bool isObstacle = false, int originLane = 0) : speed(speed), isObstacle(isObstacle), originLane(originLane) {
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

	bool getIsObstacle() {
		return isObstacle;
	}

	int getOriginLane() {
		return originLane;
	}

	void setSpeed(int newSpeed) {
		this->speed = newSpeed;
	}

	void setOriginLane(int originLane) {
		this->originLane = originLane;
	}
};