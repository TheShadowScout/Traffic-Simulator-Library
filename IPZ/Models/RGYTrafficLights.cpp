#pragma once

#include "RGYTrafficLights.h"

RGYTrafficLights::RGYTrafficLights(std::string name, LightColor startColor, int position, int redDuration, int greenDuration, int redYellowDuration, int yellowDuration, int timerOffset) : TrafficLights(name, startColor, redDuration, greenDuration, timerOffset), redYellowDuration(redYellowDuration), yellowDuration(yellowDuration) {
	create(timerOffset);
}

RGYTrafficLights::RGYTrafficLights(LightColor startColor, int position, int redDuration, int greenDuration, int redYellowDuration, int yellowDuration, int timerOffset) : TrafficLights(startColor, redDuration, greenDuration, timerOffset), redYellowDuration(redYellowDuration), yellowDuration(yellowDuration) {
	create(timerOffset);
}

void RGYTrafficLights::create(int timerOffset) {
	switch (color) {
	case LightColor::red:
		timer = redDuration - timerOffset;
		break;
	case LightColor::green:
		timer = greenDuration - timerOffset;
		break;
	case LightColor::redyellow:
		timer = redYellowDuration - timerOffset;
		break;
	case LightColor::yellow:
		timer = yellowDuration - timerOffset;
		break;
	default:
		timer = 0;
		break;
	}
}

int RGYTrafficLights::getRedYellowDuration() {
	return redYellowDuration;
}

int RGYTrafficLights::getYellowDuration() {
	return yellowDuration;
}

void RGYTrafficLights::changeState() {
	switch (color) {
	case LightColor::red:
		timer = redDuration;
		color = LightColor::redyellow;
		break;
	case LightColor::redyellow:
		timer = greenDuration;
		color = LightColor::green;
		break;
	case LightColor::green:
		timer = yellowDuration;
		color = LightColor::yellow;
		break;
	case LightColor::yellow:
		timer = redDuration;
		color = LightColor::red;
		break;
	}
}

void RGYTrafficLights::updateTrafficLights() {
	if (timer > 0) {
		timer -= 1;
	}
	else {
		changeState();
	}
}
