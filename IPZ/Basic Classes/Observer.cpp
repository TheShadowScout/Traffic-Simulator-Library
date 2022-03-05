#pragma once
#include "Observer.h"

Observer::Observer(std::string name, Cell* observationOriginCell) : observationOriginCell(observationOriginCell), lastObservedVeh(nullptr), observedPassingVehsCnt(0) {
	ID = IDcnt++;
	this->name = filterName(name);
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

std::string Observer::toString() {
	std::string tempStr = "";
	tempStr += name;
	tempStr += ";";
	tempStr += std::to_string(observedPassingVehsCnt);
	tempStr += "\n";
	return tempStr;
}

std::string Observer::filterName(std::string rawName) {
	std::string tempName = "";
	for (char character : rawName) {
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9')) {
			tempName += character;
		}
	}
	return tempName;
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
