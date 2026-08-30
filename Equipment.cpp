#include "Equipment.h"




/* Racket class */
double xTopLeftLocation, yTopLeftLocation;
double xTopRightLocation, yTopRightLocation;
double xBottomRightLocation, yBottomRightLocation;
double xBottomLeftLocation, yBottomLeftLocation;


void Racket::InitializeRacket(double xTopLeftLocation, double yTopLeftLocation, double height, double width) {
	if (xBottomLeftLocation <= xWindowMin)
		return;
	
	xTopRightLocation = xTopLeftLocation + width, yTopRightLocation = yTopLeftLocation;
	xBottomRightLocation = xTopLeftLocation + width, yBottomRightLocation = yTopLeftLocation - height;
	xBottomLeftLocation = xTopLeftLocation, yBottomLeftLocation = yTopLeftLocation - height;
}

Racket::Racket(std::string user) {
	racketHeight = 30;
	racketWidth = 100;
	movementSpeed = 10.0f;
	normalFormRed = 200.0f, normalFormGreen = 0.0f, normalFormBlue = 0.0f;
	outlinesRed = 255.0f, outlinesGreen = 0.0f, outlinesBlue = 0.0f;

	if (user == "first") {
		xTopLeftLocation = xWindowMin + racketWidth;
		yTopLeftLocation = yWindowMin + 2* racketHeight;
	}
	else if (user == "second") {
		xTopLeftLocation = xWindowMax - racketWidth *2;
		yTopLeftLocation = yWindowMax - racketHeight;
	}
	else{
		throw std::invalid_argument(user + "is invalid argument!");
	}

	InitializeRacket(xTopLeftLocation, yTopLeftLocation, racketHeight, racketWidth);
}

void Racket::setLocation(double xTopLeftLocation, double yTopLeftLocation) {
	//std::cout << "xTopLeftLocation: " << xTopLeftLocation << std::endl;
	if (xTopLeftLocation <= xWindowMin || xTopLeftLocation >= xWindowMax - racketWidth)
		return;
	this->xTopLeftLocation = xTopLeftLocation;
	this->yTopLeftLocation = yTopLeftLocation;
	InitializeRacket(this->xTopLeftLocation, this->yTopLeftLocation, racketHeight, racketWidth);
}
double Racket::getTopLeftXLocation() {
	return this->xTopLeftLocation;
}
double Racket::getTopLeftYLocation() {
	return this->yTopLeftLocation;
}
void Racket::setSpeed(double newSpeed) {
	this->movementSpeed = newSpeed;
}
void Racket::setHeight(double newHeight) {
	racketHeight = newHeight;
}
double Racket::getHeight() {
	return racketHeight;
}
void Racket::setWidth(double newWidth) {
	racketWidth = newWidth;
}
double Racket::getWidth() {
	return racketWidth;
}
double Racket::getSpeed() {
	return this->movementSpeed;
}
std::vector<int> Racket::getColor() {
	return { red, green, blue };
}
void Racket::setColor(int red, int blue, int green) {
	this->red = red;
	this->blue = blue;
	this->green = green;
}
/* Ball class */
Ball::Ball() {
	//location[0] = xWindowMax / 2;
	//location[1] = yWindowMax / 2;
	location = { xWindowMax / 2.0 , yWindowMax / 2.0 };
}
Location Ball::getBallLocation() {
	return location;
}
void Ball::setDefaultBallLocation() {
	location.x = location.x + xDirection;
	location.y = location.y + yDirection;
}
void Ball::setBallLocation(int newXLocation, int newYLocation) {
	location.x = newXLocation;
	location.y = newYLocation;
}
bool Ball::getStatus() {
	return status;
}
void Ball::speedUp() {
	if(currSpeed < 20)
		currSpeed += addSpeed;
}
void Ball::speedDown() {
	if(currSpeed - addSpeed > 0)
		currSpeed -= addSpeed;
}
void Ball::changeDefaultXDirection() {
	xDirection *= -1;
}
void Ball::changeDefaultYDirection() {
	yDirection *= -1;
}
void Ball::changeYDirection(const double fraction) {
	yDirection = -1 * fraction;
}
void Ball::changeXDirection(const double fraction) {
	xDirection = -1 * fraction;
}
void Ball::moveBall() {
	setDefaultBallLocation();
}