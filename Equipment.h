#pragma once

#include "GlobalVariableDefinitions.h"

static double racketHeight, racketWidth;

class Racket {
private:
	double xTopLeftLocation , yTopLeftLocation;
	double xTopRightLocation , yTopRightLocation;
	double xBottomRightLocation , yBottomRightLocation;
	double xBottomLeftLocation , yBottomLeftLocation;
	double movementSpeed;
	double normalFormRed = 200.0f, normalFormGreen = 0.0f, normalFormBlue = 0.0f;
	double outlinesRed = 255.0f, outlinesGreen = 0.0f, outlinesBlue = 0.0f;

public:
	Racket(std::string);
	void InitializeRacket(double xTopLeftLocation, double yTopLeftLocation, double height, double width);
	void setLocation(double xLocation, double yLocation);
	double getTopLeftXLocation();
	double getTopLeftYLocation();
	void setSpeed(double newSpeed);
	void setHeight(double newSize);
	double getHeight();
	void setWidth(double newSize);
	double getWidth();
	double getSpeed();
};

class Ball {
private:
	Location location;
	//double location[2];
	double currSpeed = 0.02;
	double addSpeed = 0.005;
	bool status = 0; // 0 means negative (moving down),  1 means positive (moving up)
	int xDirection = -1; // 1 means positive x movement, -1 means negative x movement
	int yDirection = -1; // 1 means positive y movement, -1 means negative y movement

public:
	Ball();
	Location getBallLocation();
	bool getStatus();
	void speedUp();
	void speedDown();
	void moveBall();
	void setBallLocation(int newXLocation, int newYLocation);
	void setDefaultBallLocation();
	void changeDefaultXDirection();
	void changeDefaultYDirection();

};
