#pragma once

#include "TrafficLights.h"

class RGTrafficLights : public TrafficLights {
public:
	RGTrafficLights(LightColor startState, int redDuration, int greenDuration);
	void changeState();
	void updateTrafficLights();
};