#include "Equipment.h"




/* Racket class */
double xTopLeftLocation, yTopLeftLocation;
double xTopRightLocation, yTopRightLocation;
double xBottomRightLocation, yBottomRightLocation;
double xBottomLeftLocation, yBottomLeftLocation;


void Racket::InitializeRacket(float xTopLeftLocation, float yTopLeftLocation, float height, float width) {
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

void Racket::setLocation(float xTopLeftLocation, float yTopLeftLocation) {
	//std::cout << "xTopLeftLocation: " << xTopLeftLocation << std::endl;
	if (xTopLeftLocation <= xWindowMin || xTopLeftLocation >= xWindowMax - racketWidth)
		return;
	this->xTopLeftLocation = xTopLeftLocation;
	this->yTopLeftLocation = yTopLeftLocation;
	InitializeRacket(this->xTopLeftLocation, this->yTopLeftLocation, racketHeight, racketWidth);
}
float Racket::getTopLeftXLocation() {
	return this->xTopLeftLocation;
}
float Racket::getTopLeftYLocation() {
	return this->yTopLeftLocation;
}
void Racket::setSpeed(float newSpeed) {
	this->movementSpeed = newSpeed;
}
void Racket::setHeight(float newHeight) {
	racketHeight = newHeight;
}
float Racket::getHeight() {
	return racketHeight;
}
void Racket::setWidth(float newWidth) {
	racketWidth = newWidth;
}
float Racket::getWidth() {
	return racketWidth;
}
float Racket::getSpeed() {
	return this->movementSpeed;
}
std::vector<float> Racket::getColor() {
	return { red, green, blue };
}
void Racket::setColor(float red, float blue, float green) {
	this->red = red;
	this->blue = blue;
	this->green = green;
}
bool Racket::getPhysics() {
	return this->activePhysicsType;
}
void Racket::setPhysics() {
	this->activePhysicsType = abs(this->activePhysicsType - 1); // 0 becomes |0-1| = 1, 1 becomes |1-1| = 0
}


/* ------------- Ball class -------------- */
Ball::Ball() {
	location = { xWindowMax / 2.0f , yWindowMax / 2.0f };
}
Location Ball::getBallLocation() {
	return location;
}
void Ball::setDefaultBallLocation() {
	location.x = location.x + xDirection;
	location.y = location.y + yDirection;
}
void Ball::setBallLocation(float newXLocation, float newYLocation) {
	location.x = newXLocation;
	location.y = newYLocation;
}
bool Ball::getStatus() {
	return status;
}
void Ball::speedUp() {
	if(speed < 8)
		speed += addSpeed;
}
void Ball::speedDown() {
	if(speed - addSpeed > 0)
		speed -= addSpeed;
}
float Ball::getSpeed() {
	return speed;
}
void Ball::changeDefaultXDirection() {
	xDirection *= -1;
}
void Ball::changeDefaultYDirection() {
	yDirection *= -1;
}
void Ball::changeYDirection(const float fraction) {
	yDirection = fraction;
}
void Ball::changeXDirection(const float fraction) {
	xDirection = fraction;
}
void Ball::moveBall() {
	setDefaultBallLocation();
}
float Ball::getXDirection() {
	return xDirection;
}
float Ball::getYDirection() {
	return yDirection;
}