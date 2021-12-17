#pragma once

#include <string>

class Vehicle {
public:
	int static IDcnt;

protected:
	std::string name;
	int speed;
	int ID;

public:	
	// name - nazwa pojazdu, speed - prêdkoœæ pojazdu
	Vehicle(std::string name, int speed) : name(name), speed(speed) {
		ID = IDcnt++;
	}

	Vehicle(int speed) : speed(speed) {
		ID = IDcnt++;
		name = std::to_string(ID);
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
		this->speed = newSpeed;
	}
};