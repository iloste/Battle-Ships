#include "Ship.h"


Ship::Ship() {
	size = 1;
	orientation = Orientation::Horizontal;
	hits = new bool[1];
	coordinates = getCoordinates(Coordinate(-1, -1), size);
	placedOnBoard = false;
}

Ship::Ship(Coordinate origin, int size, Orientation orientation) {
	this->size = size;
	this->orientation = orientation;
	hits = new bool[size]();
	coordinates = getCoordinates(origin, size);
	placedOnBoard = true;
}

bool Ship::hitShip(Coordinate location) {
	for (size_t i = 0; i < coordinates.size(); i++)
	{
		if (coordinates[i] == location)
		{
			return true;
		}
	}

	return false;
}

std::vector<Coordinate> Ship::getCoordinates(Coordinate origin, int size) {
	std::vector<Coordinate> coords{};
	Coordinate nextCoord = origin;
	Coordinate directionCoord;
	
	if (orientation == Orientation::Horizontal)
	{
		directionCoord = Coordinate(1, 0);
	}
	else 
	{
		directionCoord = Coordinate(0, 1);
	}


	for (size_t i = 0; i < size; i++)
	{
		coords.push_back(nextCoord);
		nextCoord = nextCoord + directionCoord;
	}

	return coords;
}

void Ship::printCoords() {
	std::cout << "Ships coordinates: ";

	for (size_t i = 0; i < coordinates.size(); i++)
	{
		std::cout << "(" << coordinates[i].x << ", " << coordinates[i].y << ")";

		if (i + 1 < coordinates.size())
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}
