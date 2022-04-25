#include "Coordinate.h"


Coordinate::Coordinate(int x, int y) {
	this->x = x;
	this->y = y;
}

Coordinate::Coordinate() {
	this->x = 0;
	this->y = 0;
}

Coordinate Coordinate::operator+(const Coordinate& coord) {
	int newX = this->x + coord.x;
	int newY = this->y + coord.y;
	Coordinate newCoord = Coordinate(newX, newY);
	return newCoord;
}

Coordinate Coordinate::operator-(const Coordinate& coord) {
	int newX = this->x - coord.x;
	int newY = this->y - coord.y;
	Coordinate newCoord = Coordinate(newX, newY);
	return newCoord;
}

bool Coordinate::operator==(const Coordinate& coord) {
	if (this->x == coord.x && this->y == coord.y)
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
