#pragma once
#include <iostream>
#include <string>
#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
};

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
};
int Point::getX() const {
	return this->x;
};

int Point::getY() const {
	return this->y;
};

void Point::setX(int x) {
	this->x = x;
};

void Point::setY(int y) {
	this->y = y;
};

void Point::setXY(int x, int y) {
	this->x = x;
	this->y = y;
};


void Point::swapXY() {
	int holder = this->x;
	this->x = this->y;
	this->y = holder;

};

void Point::multiplyX(int factor) {
	this->x = this->x * factor;
};

void Point::multiplyY(int factor) {
	this->y = this->y * factor;
};

//doesn't change anything but it will create a copy of the thing to string.
std::string Point::toString() const {

	std::string stringy = "hello";
	return stringy;
};
