#pragma once

#include "Generator.h"

Generator::Generator(std::string name, double createVehProb) : Cell(), createVehProb(createVehProb) {
	ID = IDcnt++;
	this->name = filterName(name);
}

Generator::Generator(double createVehProb) : Cell(), createVehProb(createVehProb) {
	ID = IDcnt++;
	name = std::to_string(ID);
}

Generator::~Generator() {
	delete vehicle;
}

std::string Generator::toString() {
	if (vehicle == nullptr) {
		return ".\n";
	}
	return std::to_string(vehicle->getSpeed()) + "\n";
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
	if (vehicle == nullptr && 1.0 * std::rand() / RAND_MAX <= createVehProb) {
		Cell* tempCell = this;
		for (int i = 1; i <= maxSpeed; i++) {
			tempCell = tempCell->getNextCell();
			if (tempCell == nullptr) {
				break;
			}
			if (tempCell->getVehicle() != nullptr) {
				vehicle = new Vehicle(i - 1);
				return true;
			}
		}
		vehicle = new Vehicle(maxSpeed);
		return true;
	}
	return false;
}
