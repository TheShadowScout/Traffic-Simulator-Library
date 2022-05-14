#pragma once

#include "TrafficLights.h"

TrafficLights::TrafficLights(std::string name, LightColor startColor, int redDuration, int greenDuration, int timerOffset) : name(name), color(startColor), redDuration(redDuration), greenDuration(greenDuration) {
	create(timerOffset);
	ID = IDcnt++;
}

TrafficLights::TrafficLights(LightColor startColor, int redDuration, int greenDuration, int timerOffset) : color(startColor), redDuration(redDuration), greenDuration(greenDuration) {
	create(timerOffset);
	ID = IDcnt++;
	name = std::to_string(ID);
}

int TrafficLights::getID() {
	return ID;
}

std::string TrafficLights::getName() {
	return name;
}

void TrafficLights::create(int timerOffset) {
	switch (color) {
	case LightColor::red:
		timer = redDuration - timerOffset;
		break;
	case LightColor::green:
		timer = greenDuration - timerOffset;
		break;
	default:
		timer = 0;
	}
}

int TrafficLights::getGreenDuration() {
	return greenDuration;
}

int TrafficLights::getRedDuration() {
	return redDuration;
}

LightColor TrafficLights::getColor() {
	return color;
}

int TrafficLights::getTimer() {
	return timer;
}