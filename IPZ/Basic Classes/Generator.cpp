#pragma once

#include "Generator.h"

Generator::Generator(std::string name, int maxSpeed, double createVehProb) : RoadCell(maxSpeed), createVehProb(createVehProb) {
	ID = IDcnt++;
	this->name = filterName(name);
	this->setCarHolder(new CarHolder());
}

Generator::Generator(int maxSpeed, double createVehProb) : RoadCell(maxSpeed), createVehProb(createVehProb) {
	ID = IDcnt++;
	name = std::to_string(ID);
	this->setCarHolder(new CarHolder());
}

Generator::~Generator() {
	delete carHolder->getVehicle();
}

std::string Generator::toString() {
	if (carHolder->getVehicle() == nullptr) {
		return ".\n";
	}
	return std::to_string(carHolder->getVehicle()->getSpeed()) + "\n";
}

std::string Generator::filterName(std::string rawName) {
	std::string tempName = "";
	for (char character : rawName) {
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9')) {
			tempName += character;
		}
	}
	return tempName;
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
