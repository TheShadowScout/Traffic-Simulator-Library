#pragma once

#include "../Basic Classes/TrafficLights.h"

class RGYTrafficLights : public TrafficLights {
protected:
	int redYellowDuration;
	int yellowDuration;

	void create(int timerOffset);

public:
	RGYTrafficLights(std::string name, LightColor startColor, int position, int redDuration, int greenDuration, int redYellowDuration = 1, int yellowDuration = 1, int timerOffset = 0);
	RGYTrafficLights(LightColor startColor, int position, int redDuration, int greenDuration, int redYellowDuration = 1, int yellowDuration = 1, int timerOffset = 0);
	int getRedYellowDuration();
	int getYellowDuration();
	void changeState();
	void updateTrafficLights();
};