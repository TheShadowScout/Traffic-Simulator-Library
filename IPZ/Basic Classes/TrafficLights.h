#pragma once
class TrafficLights
{
	bool isRed;
	int position;
	int changePeriod;
	int timer;

public:
	TrafficLights(bool startState, int position, int period);
	int getChangePeriod();
	bool getState();
	int getPosition();
	int getTimer();
	void setTimer(int newTimer);
	void setState(bool newState);
	void setPosition(int newPosition);
	void setChangePeriod(double newPeriod);
};