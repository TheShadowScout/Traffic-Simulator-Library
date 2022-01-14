#pragma once

class MovePrediction {
protected:
	bool utilFlag;
	int newVehSpeed;
	int newVehLane;

public:
	MovePrediction(bool utilFlag, int newVehSpeed, int newVehLane) : utilFlag(utilFlag), newVehSpeed(newVehSpeed), newVehLane(newVehLane) {}

	bool getUtilFlag() {
		return utilFlag;
	}

	int getNewVehSpeed() {
		return newVehSpeed;
	}

	int getNewVahLane() {
		return newVehLane;
	}

	void setNewVehSpeed(int newVehSpeed) {
		this->newVehSpeed = newVehSpeed;
	}
};