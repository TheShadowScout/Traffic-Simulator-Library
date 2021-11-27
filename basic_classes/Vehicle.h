#pragma once
#include <iostream>

class Vehicle {
	protected:
	std::string name;
	int id;
	int speed;

	public:	
	// name - nazwa pojazdu, speed - prêdkoœæ pojazdu
	Vehicle(std::string name, int speed) {
		this->name = name;
		this->id = 1;
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

	// newSpeed - nowa prêdkoœæ pojazdu
	void setSpeed(int newSpeed) {
		speed = newSpeed;
	}
};