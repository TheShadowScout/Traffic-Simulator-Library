#pragma once

#include <string>

enum class LightColor { red = 1, redyellow = 2, green = 3, yellow = 4 };

class TrafficLights {
public:
	int static IDcnt;

protected:
	int ID;
	LightColor color;
	int redDuration;
	int greenDuration;
	int timer;
	std::string name;

	void create(int timerOffset);

public:
	TrafficLights(std::string name, LightColor startColor, int redDuration, int greenDuration, int timerOffset = 0);
	TrafficLights(LightColor startColor, int redDuration, int greenDuration, int timerOffset = 0);
	int getID();
	std::string getName();
	int getGreenDuration();
	int getRedDuration();
	LightColor getColor();
	int getTimer();
	virtual void updateTrafficLights() = 0;
};