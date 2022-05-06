#pragma once

#include "TrafficLights.h"

class RGTrafficLights : public TrafficLights {
public:
	RGTrafficLights(LightColor startState, int redDuration, int greenDuration, int timerOffset = 0);
	void changeState();
	void updateTrafficLights();
};