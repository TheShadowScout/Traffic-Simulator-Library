#pragma once

class MovePrediction {
protected:
	bool utilFlag;
	int newVehSpeed;
	int newVehLane;

public:
	MovePrediction(bool utilFlag, int newVehSpeed, int newVehLane);
	bool getUtilFlag();
	int getNewVehSpeed();
	int getNewVahLane();
	void setNewVehSpeed(int newVehSpeed);
	friend bool operator < (const MovePrediction& lhs, const MovePrediction& rhs);
};
