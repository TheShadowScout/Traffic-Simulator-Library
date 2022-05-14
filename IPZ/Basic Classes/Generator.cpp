#pragma once

#include "Generator.h"

Generator::Generator(std::string name, int maxSpeed, double createVehProb) : name(name), RoadCell(maxSpeed), createVehProb(createVehProb) {
	create();
}

Generator::Generator(int maxSpeed, double createVehProb) : RoadCell(maxSpeed), createVehProb(createVehProb) {
	create();
	name = std::to_string(ID);
}

int Generator::getID() {
	return ID;
}

std::string Generator::getName() {
	return name;
}

void Generator::create() {
	if (maxSpeed < 1 || maxSpeed > 6)
		throw std::invalid_argument("Max speed must be in range between 1 and 6");
	if (createVehProb < 0 || createVehProb > 1)
		throw std::invalid_argument("Create vehicle probability must be in range between 0 and 1");
	ID = IDcnt++;
	setCarHolder(new CarHolder());
}

bool Generator::createVeh() {
	if (carHolder->getVehicle() == nullptr && 1.0 * std::rand() / RAND_MAX <= createVehProb) {
		Cell* tempCell = this;
		for (int i = 1; i <= maxSpeed; i++) {
			tempCell = tempCell->getNextCell();
			if (tempCell == nullptr) {
				break;
			}
			if (tempCell->getVehicle() != nullptr) {
				carHolder->setVehicle(new Vehicle(i - 1));
				return true;
			}
		}
		carHolder->setVehicle(new Vehicle(maxSpeed));
		return true;
	}
	return false;
}

std::string Generator::toString() {
	std::string repStr = "Generator: ";
	repStr += name;
	repStr += "\n";
	if (carHolder->getVehicle() == nullptr) {
		repStr += ".";
	}
	else {
		repStr += std::to_string(carHolder->getVehicle()->getSpeed());
	}
	repStr += "\n";
	return repStr;
}