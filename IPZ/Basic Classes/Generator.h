#pragma once

#include <iostream>
#include <string>

#include "Cell.h"
#include "Vehicle.h"

class Generator : public Cell
{
public:
	int static IDcnt;

protected:
	int distToSearch[7] = { 1, 3, 6, 10, 15, 21, 28 };
	int breakingDist[7] = { 0, 1, 3, 6, 10, 15, 21 };
	std::string name;
	int ID;
	double createVehProb;
	
public:
	Generator(std::string name, double createVehProb) : name(name), createVehProb(createVehProb) {
		Cell(0);
		ID = IDcnt++;
	}

	Generator(double createVehProb) : createVehProb(createVehProb) {
		Cell(0);
		ID = IDcnt++;
		name = std::to_string(ID);
	}

	bool createVeh() {
		if (vehicle == nullptr && 1.0 * std::rand() / RAND_MAX <= createVehProb) {
			Cell* tempCell = this;
			for (int i = 1; i <= distToSearch[maxSpeed]; i++) {
				tempCell = tempCell->getNextCell();
				if (tempCell == nullptr) {
					break;
				}
				if (tempCell->getVehicle() != nullptr) {
					int nextVehSpeed = tempCell->getVehicle()->getSpeed();
					for (int j = maxSpeed; j >= 0; j--) {
						if (breakingDist[j] - breakingDist[std::max(nextVehSpeed - 1, 0)] > i - 1) {
							continue;
						}
						vehicle = new Vehicle(j);
						return true;
					}
				}
			}
			vehicle = new Vehicle(maxSpeed);
			return true;
		}
		return false;
	}

	std::string tempToString() {
		if (vehicle == nullptr) {
			return ".\n";
		}
		return std::to_string(vehicle->getSpeed()) + "\n";
	}
};