#pragma once

#include "Observer.h"

Observer::Observer(std::string name, Cell* observationOriginCell) : name(name), observationOriginCell(observationOriginCell), lastObservedVeh(nullptr), observedPassingVehsCnt(0) {
	ID = IDcnt++;
	distToSearch = observationOriginCell->getMaxSpeed();
}

Observer::Observer(Cell* observationOriginCell) : observationOriginCell(observationOriginCell), lastObservedVeh(nullptr), observedPassingVehsCnt(0) {
	ID = IDcnt++;
	name = std::to_string(ID);
	distToSearch = observationOriginCell->getMaxSpeed();
}

std::string Observer::getName() {
	return name;
}

int Observer::getObservedPassingVehsCnt() {
	return observedPassingVehsCnt;
}

void Observer::checkVehPassing() {
	Cell* tempCell = observationOriginCell;
	for (int i = 1; i <= distToSearch; i++) {
		Vehicle* cellVeh = tempCell->getVehicle();
		if (cellVeh != nullptr) {
			if (cellVeh != lastObservedVeh) {
				if (lastObservedVeh != nullptr) {
					observedPassingVehsCnt++;
				}
				lastObservedVeh = cellVeh;
				return;
			}
			return;
		}
		tempCell = tempCell->getPreviousCell();
		if (tempCell == nullptr) {
			break;
		}
	}
	if (lastObservedVeh != nullptr) {
		observedPassingVehsCnt++;
	}
	lastObservedVeh = nullptr;
}

std::string Observer::toString() {
	std::string tempStr = "ObserverName;PassingVehicalsCount\n";
	tempStr += name;
	tempStr += ";";
	tempStr += std::to_string(observedPassingVehsCnt);
	tempStr += "\n";
	return tempStr;
}