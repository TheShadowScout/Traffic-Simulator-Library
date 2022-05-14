#pragma once

#include "RGTrafficLights.h"

RGTrafficLights::RGTrafficLights(std::string name, LightColor startState, int redDuration, int greenDuration, int timerOffset) : TrafficLights(name, startState, redDuration, greenDuration, timerOffset) { ; }

RGTrafficLights::RGTrafficLights(LightColor startState, int redDuration, int greenDuration, int timerOffset) : TrafficLights(startState, redDuration, greenDuration, timerOffset) { ; }

void RGTrafficLights::changeState() {
	switch (color) 	{
	case LightColor::red:
		timer = greenDuration;
		color = LightColor::green;
		break;
	case LightColor::green:
		timer = redDuration;
		color = LightColor::red;
		break;
	}
}

void RGTrafficLights::updateTrafficLights() {
	if (timer > 0) {
		timer -= 1;
	}
	else {
		changeState();
	}
}
