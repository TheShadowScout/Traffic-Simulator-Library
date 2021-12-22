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
};