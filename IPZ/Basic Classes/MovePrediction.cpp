#pragma once

#include "MovePrediction.h"

MovePrediction::MovePrediction(bool utilFlag, int newVehSpeed, int newVehLane) : utilFlag(utilFlag), newVehSpeed(newVehSpeed), newVehLane(newVehLane) {}

bool MovePrediction::getUtilFlag() {
	return utilFlag;
}

int MovePrediction::getNewVehSpeed() {
	return newVehSpeed;
}

int MovePrediction::getNewVahLane() {
	return newVehLane;
}

void MovePrediction::setNewVehSpeed(int newVehSpeed) {
	this->newVehSpeed = newVehSpeed;
}
