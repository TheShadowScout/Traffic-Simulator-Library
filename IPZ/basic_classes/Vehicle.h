#pragma once
#include <iostream>

class Vehicle {
	protected:
	std::string name;
	int ID;
	int speed;

	public:	
	// name - nazwa pojazdu, speed - prêdkoœæ pojazdu
	Vehicle(std::string name, int speed) {
		this->name = name;
		this->ID = 1;
		this->speed = speed;
	}

	std::string getName() {
		return this->name;
	}

	int getID() {
		return this->ID;
	}

	int getSpeed() {
		return this->speed;
	}

	// newSpeed - nowa prêdkoœæ pojazdu
	void setSpeed(int newSpeed) {
		speed = newSpeed;
	}
};