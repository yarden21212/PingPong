#include "Equipment.h"

void Racket::setLocation(double xLocation, double yLocation) {
	this->xLocation = xLocation;
	this->yLocation = yLocation;
}

Racket::Racket() {
	xLocation = 0.0f;
	yLocation = 0.0f;
	movementSpeed = 3.0f;
	normalFormRed = 200.0f, normalFormGreen = 0.0f, normalFormBlue = 0.0f;
	outlinesRed = 255.0f, outlinesGreen = 0.0f, outlinesBlue = 0.0f;
}
double Racket::getXLocation() {
	return this->xLocation;
}
double Racket::getYLocation() {
	return this->yLocation;
}
void Racket::setSpeed(double newSpeed) {
	this->movementSpeed = newSpeed;
}
void Racket::setSize(double newSize) {
	this->size = newSize;
}
double Racket::getSize() {
	return this->size;
}