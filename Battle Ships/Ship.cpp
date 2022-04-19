#include "Ship.h"


Ship::Ship() {
	shipSize = 1;
	orientation = Orientation::Horizontal;
	hits = new bool[1];
	coordinates = getCoordinates(Coordinate(-1, -1));
	placedOnBoard = false;
}

Ship::Ship(Coordinate origin, int shipSize, Orientation orientation) {
	this->shipSize = shipSize;
	this->orientation = orientation;
	hits = new bool[shipSize]();
	coordinates = getCoordinates(origin);
	placedOnBoard = true;
}

bool Ship::hitShip(Coordinate location) {
	for (size_t i = 0; i < coordinates.size(); i++)
	{
		if (coordinates[i] == location)
		{
			hits[i] = true;
			return true;
		}
	}

	return false;
}

std::vector<Coordinate> Ship::getCoordinates(Coordinate origin) {
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


	for (size_t i = 0; i < shipSize; i++)
	{
		coords.push_back(nextCoord);
		nextCoord = nextCoord + directionCoord;
	}

	return coords;
}

bool Ship::isDestroyed()
{
	for (size_t i = 0; i < shipSize; i++)
	{
		if (hits[i] == false)
		{
			return false;
		}
	}

	return true;
}

bool Ship::collidesWith(Ship& ship)
{
	if (!this->placedOnBoard || !ship.placedOnBoard)
	{
		return false;
	}

	for (size_t i = 0; i < this->coordinates.size(); i++)
	{
		for (size_t j = 0; j < ship.coordinates.size(); j++)
		{
			if (this->coordinates[i] == ship.coordinates[j])
			{
				return true;
			}
		}
	}

	return false;
}

void Ship::resetCoordinates(Coordinate newOrigin)
{
	coordinates = getCoordinates(newOrigin);
}

void Ship::rotate()
{
	if (orientation == Orientation::Horizontal)
	{
		orientation = Orientation::Vertical;
	}
	else {
		orientation = Orientation::Horizontal;
	}
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
