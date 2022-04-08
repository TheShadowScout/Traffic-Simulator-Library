#pragma once
#include "TrafficLights.h"

class YellowTrafficLights : public TrafficLights
{
	int redYellowLightDuration;
	int yellowLightDuration;
public:
	YellowTrafficLights(LightColor startState, int position, int redDuration, int greenDuration, int redYellow = 1, int yellow = 1);
	int getRedYellowDuration();
	int getYellowDuration();
	void setRedYellowLightDuration(double duration);
	void setYellowLightDuration(double duration);
	void changeState();
};