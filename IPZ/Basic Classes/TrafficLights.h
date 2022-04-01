#pragma once
enum class LightColor { red = 1, redyellow = 2, green = 3, yellow = 4 };

class TrafficLights
{
	// bool isRed; // enum RED:YELLOW:GREEN
	LightColor color;
	bool yellowOn;
	int position;
	int redLightDuration;
	int greenLightDuration;
	int redYellowLightDuration;
	int yellowLightDuration;
	int timer;

public:
	TrafficLights(LightColor startState, int position, int redDuration, int greenDuration, bool yellowOn = false, int redYellow = 1, int yellow = 1);
	int getGreenDuration();
	int getRedDuration();
	int getRedYellowDuration();
	int getYellowDuration();
	LightColor getColor();
	int getPosition();
	int getTimer();
	void setTimer(int newTimer);
	void setColor(LightColor newColor);
	void setPosition(int newPosition);
	void setRedLightDuration(double duration);
	void setRedYellowLightDuration(double duration);
	void setGreenLightDuration(double duration);
	void setYellowLightDuration(double duration);
	bool getYellowOn();
};