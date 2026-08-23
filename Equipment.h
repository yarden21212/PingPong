#pragma once
class Racket {
private:
	double xLocation , yLocation;
	double movementSpeed;
	double size;
	double normalFormRed = 200.0f, normalFormGreen = 0.0f, normalFormBlue = 0.0f;
	double outlinesRed = 255.0f, outlinesGreen = 0.0f, outlinesBlue = 0.0f;

public:
	Racket();
	void setLocation(double xLocation, double yLocation);
	double getXLocation();
	double getYLocation();
	void setSpeed(double newSpeed);
	void setSize(double newSize);
	double getSize();
};