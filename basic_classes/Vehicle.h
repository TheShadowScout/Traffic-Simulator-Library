#pragma once
#include <iostream>

class Vehicle {
	std::string name;
	int id;
	int speed;
public:	
	Vehicle(std::string name, int id, int speed) {
		this->name = name;
		this->id = id;
		this->speed = speed;
	}

	std::string getName() {
		return this->name;
	}

	int getID() {
		return this->id;
	}

	int getSpeed() {
		return this->speed;
	}

	void setSpeed(int newSpeed) {
		speed = newSpeed;
	}
};