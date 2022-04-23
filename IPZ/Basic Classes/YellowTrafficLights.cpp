#include "YellowTrafficLights.h"

YellowTrafficLights::YellowTrafficLights(LightColor startState, int position, int redDuration, int greenDuration, int redYellowDuration, int yellowDuration) : TrafficLights(startState, redDuration, greenDuration), redYellowLightDuration(redYellowDuration), yellowLightDuration(yellowDuration)
{
	switch (startState) {
	case LightColor::red:
		timer = redDuration;
		break;
	case LightColor::green:
		timer = greenDuration;
		break;
	case LightColor::redyellow:
		timer = redYellowDuration;
		break;
	case LightColor::yellow:
		timer = yellowDuration;
		break;
	default:
		timer = 0;
	}

}

int YellowTrafficLights::getRedYellowDuration()
{
	return redYellowLightDuration;
}

int YellowTrafficLights::getYellowDuration()
{
	return yellowLightDuration;
}

void YellowTrafficLights::setRedYellowLightDuration(int duration)
{
	redYellowLightDuration = duration;
}

void YellowTrafficLights::setYellowLightDuration(int duration)
{
	yellowLightDuration = duration;
}

void YellowTrafficLights::changeState()
{
	switch (getColor())
	{
	case LightColor::red:
		setTimer(getRedYellowDuration());
		setColor(LightColor::redyellow);
		break;
	case LightColor::redyellow:
		setTimer(getGreenDuration());
		setColor(LightColor::green);
		break;
	case LightColor::green:
		setTimer(getYellowDuration());
		setColor(LightColor::yellow);
		break;
	case LightColor::yellow:
		setTimer(getRedDuration());
		setColor(LightColor::red);
		break;
	}
}
