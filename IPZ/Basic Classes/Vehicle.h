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
	Vehicle(std::string name, int speed, bool isObstacle = false, int originLane = 0);
	Vehicle(int speed, bool isObstacle = false, int originLane = 0);
	std::string getName();
	int getID();
	int getSpeed();
	bool getIsObstacle();
	int getOriginLane();
	void setSpeed(int newSpeed);
	void setOriginLane(int originLane);
};