#include "RGYTrafficLights.h"

RGYTrafficLights::RGYTrafficLights(LightColor startState, int position, int redDuration, int greenDuration, int redYellowDuration, int yellowDuration, int timerOffset) : TrafficLights(startState, redDuration, greenDuration, timerOffset), redYellowLightDuration(redYellowDuration), yellowLightDuration(yellowDuration) {
	switch (startState) {
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
	}

}

int RGYTrafficLights::getRedYellowDuration() {
	return redYellowLightDuration;
}

int RGYTrafficLights::getYellowDuration() {
	return yellowLightDuration;
}

void RGYTrafficLights::changeState() {
	switch (color) {
	case LightColor::red:
		timer = redLightDuration;
		color = LightColor::redyellow;
		break;
	case LightColor::redyellow:
		timer = greenLightDuration;
		color = LightColor::green;
		break;
	case LightColor::green:
		timer = yellowLightDuration;
		color = LightColor::yellow;
		break;
	case LightColor::yellow:
		timer = redLightDuration;
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
