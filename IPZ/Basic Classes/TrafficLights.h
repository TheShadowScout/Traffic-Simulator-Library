#pragma once

enum class LightColor { red = 1, redyellow = 2, green = 3, yellow = 4 };

class TrafficLights {
protected:
	LightColor color;
	int redLightDuration;
	int greenLightDuration;
	int timer;

public:
	TrafficLights(LightColor startState, int redDuration, int greenDuration);
	int getGreenDuration();
	int getRedDuration();
	LightColor getColor();
	int getTimer();
	virtual void updateTrafficLights() = 0;
};