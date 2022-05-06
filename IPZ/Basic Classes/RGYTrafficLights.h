#pragma once

#include "TrafficLights.h"

class RGYTrafficLights : public TrafficLights {
	int redYellowLightDuration;
	int yellowLightDuration;
public:
	RGYTrafficLights(LightColor startState, int position, int redDuration, int greenDuration, int redYellow = 1, int yellow = 1, int timerOffset = 0);
	int getRedYellowDuration();
	int getYellowDuration();
	void changeState();
	void updateTrafficLights();
};