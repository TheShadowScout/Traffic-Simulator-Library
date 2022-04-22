#pragma once
enum class LightColor { red = 1, redyellow = 2, green = 3, yellow = 4 };

class TrafficLights
{
	// bool isRed; // enum RED:YELLOW:GREEN
protected:
	LightColor color;
	int position;
	int redLightDuration;
	int greenLightDuration;
	int timer;

public:
	TrafficLights(LightColor startState, int position, int redDuration, int greenDuration);
	int getGreenDuration();
	int getRedDuration();
	LightColor getColor();
	int getPosition();
	int getTimer();
	void setTimer(int newTimer);
	void setColor(LightColor newColor);
	void setPosition(int newPosition);
	void setRedLightDuration(int duration);
	void setGreenLightDuration(int duration);
	void changeState();
};