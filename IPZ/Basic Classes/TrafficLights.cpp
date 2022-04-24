#pragma once

#include "TrafficLights.h"

TrafficLights::TrafficLights(LightColor startState, int redDuration, int greenDuration) {
	color = startState;
	redLightDuration = redDuration;
	greenLightDuration = greenDuration;
	switch (startState) {
	case LightColor::red:
		timer = redDuration;
		break;
	case LightColor::green:
		timer = greenDuration;
		break;
	default:
		timer = 0;
	}
}

int TrafficLights::getGreenDuration() {
	return greenLightDuration;
}

int TrafficLights::getRedDuration() {
	return redLightDuration;
}

LightColor TrafficLights::getColor() {
	return color;
}

int TrafficLights::getTimer() {
	return timer;
}