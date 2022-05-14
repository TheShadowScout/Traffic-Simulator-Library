#pragma once

#include "../Basic Classes/TrafficLights.h"

class RGTrafficLights : public TrafficLights {
public:
	RGTrafficLights(std::string name, LightColor startState, int redDuration, int greenDuration, int timerOffset = 0);
	RGTrafficLights(LightColor startState, int redDuration, int greenDuration, int timerOffset = 0);
	void changeState();
	void updateTrafficLights();
};