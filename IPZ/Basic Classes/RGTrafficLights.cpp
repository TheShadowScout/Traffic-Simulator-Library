#pragma once

#include "RGTrafficLights.h"

RGTrafficLights::RGTrafficLights(LightColor startState, int redDuration, int greenDuration) : TrafficLights(startState, redDuration, greenDuration) { ; }

void RGTrafficLights::changeState() {
	switch (color) 	{
	case LightColor::red:
		timer = greenLightDuration;
		color = LightColor::green;
		break;
	case LightColor::green:
		timer = redLightDuration;
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
