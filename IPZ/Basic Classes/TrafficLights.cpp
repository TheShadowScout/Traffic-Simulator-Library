#pragma once
#include "TrafficLights.h"

TrafficLights::TrafficLights(bool startState, int position, int period)
{
	isRed = startState;
	this->position = position;
	changePeriod = period;
	timer = changePeriod;
}

int TrafficLights::getChangePeriod()
{
	return changePeriod;
}

bool TrafficLights::getState()
{
	return isRed;
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

void TrafficLights::setState(bool newState)
{
	isRed = newState;
}

void TrafficLights::setPosition(int newPosition)
{
	position = newPosition;
}

void TrafficLights::setChangePeriod(double newPeriod)
{
	changePeriod = newPeriod;
}
