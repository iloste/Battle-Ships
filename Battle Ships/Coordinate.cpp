#include "Coordinate.h"


Coordinate::Coordinate(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}


Coordinate::Coordinate() {
	this->x = 0;
	this->y = 0;
}


Coordinate Coordinate::operator+(const Coordinate& _coord) {
	int newX = this->x + _coord.x;
	int newY = this->y + _coord.y;
	Coordinate newCoord = Coordinate(newX, newY);
	return newCoord;
}


Coordinate Coordinate::operator-(const Coordinate& _coord) {
	int newX = this->x - _coord.x;
	int newY = this->y - _coord.y;
	Coordinate newCoord = Coordinate(newX, newY);
	return newCoord;
}


bool Coordinate::operator==(const Coordinate& _coord) {
	if (this->x == _coord.x && this->y == _coord.y)
	{
		return true;
	}

	return false;
}


std::string Coordinate::toString()
{
	std::ostringstream oss;
	oss << "(" << x << ", " << y << ")";
	return oss.str();
}
