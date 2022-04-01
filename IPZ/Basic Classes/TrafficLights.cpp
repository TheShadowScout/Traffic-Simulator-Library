#pragma once
#include "TrafficLights.h"

TrafficLights::TrafficLights(LightColor startState, int position, int redDuration, int greenDuration, bool yellowOn, int redYellow, int yellow)
{
	color = startState;
	this->position = position;
	redLightDuration = redDuration;
	greenLightDuration = greenDuration;
	this->yellowOn = yellowOn;
	redYellowLightDuration = redYellow;
	yellowLightDuration = yellow;
}

int TrafficLights::getGreenDuration()
{
	return greenLightDuration;
}

int TrafficLights::getRedDuration()
{
	return redLightDuration;
}

int TrafficLights::getRedYellowDuration()
{
	return redYellowLightDuration;
}

int TrafficLights::getYellowDuration()
{
	return yellowLightDuration;
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

void TrafficLights::setColor(LightColor newColor)
{
	color = newColor;
}

void TrafficLights::setPosition(int newPosition)
{
	position = newPosition;
}

void TrafficLights::setRedLightDuration(double duration)
{
	redLightDuration = duration;
}

void TrafficLights::setRedYellowLightDuration(double duration)
{
	redYellowLightDuration = duration;
}

void TrafficLights::setGreenLightDuration(double duration)
{
	greenLightDuration = duration;
}

void TrafficLights::setYellowLightDuration(double duration)
{
	yellowLightDuration = duration;
}

bool TrafficLights::getYellowOn()
{
	return yellowOn;
}