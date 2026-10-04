#pragma once

#include <vector>
#include <iostream>

#include "GlobalVariableDefinitions.h"


static float racketHeight, racketWidth;

class Racket {
private:
	float red, green, blue;
	float xTopLeftLocation , yTopLeftLocation;
	float xTopRightLocation , yTopRightLocation;
	float xBottomRightLocation , yBottomRightLocation;
	float xBottomLeftLocation , yBottomLeftLocation;
	float movementSpeed;
	float normalFormRed = 200.0f, normalFormGreen = 0.0f, normalFormBlue = 0.0f;
	/* Shape outlines (another shape but bigger) */
	float xTopLeftLocationOutline;
	float yTopLeftLocationOutline;
	float outlinesRed = 255.0f, outlinesGreen = 0.0f, outlinesBlue = 0.0f;
	bool activePhysicsType = 0;

public:
	Racket(std::string);
	void InitializeRacket(float xTopLeftLocation, float yTopLeftLocation, float height, float width);
	void setLocation(float xLocation, float yLocation);
	float getTopLeftXLocation();
	float getTopLeftYLocation();
	void setSpeed(float newSpeed);
	void setHeight(float newSize);
	float getHeight();
	void setWidth(float newSize);
	float getWidth();
	float getSpeed();
	void setColor(float red, float blue, float green);
	std::vector<float> getColor();
	bool getPhysics();
	void setPhysics();
};

class Ball {
private:
	Location location;
	//double location[2];
	float speed = 0.5f;
	float addSpeed = 1.0f;
	bool status = 0; // 0 means negative (moving down),  1 means positive (moving up)
	float xDirection = -1.0f; // 1 means positive x movement, -1 means negative x movement
	float yDirection = -1.0f; // 1 means positive y movement, -1 means negative y movement
	int red, blue, green;

public:
	Ball();
	Location getBallLocation();
	bool getStatus();
	void speedUp();
	void speedDown();
	void moveBall();
	void setBallLocation(float newXLocation, float newYLocation);
	void setDefaultBallLocation();
	void changeDefaultXDirection();
	void changeDefaultYDirection();
	void changeYDirection(const float fraction);
	void changeXDirection(const float fraction);
	float getSpeed();
	float getXDirection();
	float getYDirection();
	//void setSpeed();
	

};
