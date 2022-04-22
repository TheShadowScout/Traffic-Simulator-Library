#pragma once
#include "TrafficLights.h"

TrafficLights::TrafficLights(LightColor startState, int position, int redDuration, int greenDuration)
{
	color = startState;
	this->position = position;
	redLightDuration = redDuration;
	greenLightDuration = greenDuration;
	switch (startState)
	{
	case LightColor::red:
		timer = redDuration;
		break;
	case LightColor::green:
		timer = greenDuration;
		break;
	}
}

int TrafficLights::getGreenDuration()
{
	return greenLightDuration;
}

int TrafficLights::getRedDuration()
{
	return redLightDuration;
}

LightColor TrafficLights::getColor()
{
	return color;
}

int TrafficLights::getPosition()
{
	return position;
}

int TrafficLights::getTimer()
{
	return timer;
}

void TrafficLights::setTimer(int newTimer)
{
	timer = newTimer;
}

void TrafficLights::changeState()
{
	switch (getColor())
	{
	case LightColor::red:
		setTimer(getGreenDuration());
		setColor(LightColor::green);
		break;
	case LightColor::green:
		setTimer(getRedDuration());
		setColor(LightColor::red);
		break;
	}
}

void TrafficLights::setColor(LightColor newColor)
{
	color = newColor;
}

void TrafficLights::setPosition(int newPosition)
{
	position = newPosition;
}

void TrafficLights::setRedLightDuration(int duration)
{
	redLightDuration = duration;
}

void TrafficLights::setGreenLightDuration(int duration)
{
	greenLightDuration = duration;
}