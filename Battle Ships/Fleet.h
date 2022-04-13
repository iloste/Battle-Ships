#pragma once
#include "Ship.h"
#include <vector>

class Fleet
{
public:
	static const int numberOfShips;

	Fleet();
	Fleet(bool autoPlaceShips);
	Ship* getShips();

private:
	static const int shipSizes[5];
	void placeShips();
	Coordinate getCoordinateFromPlayer();
	Ship::Orientation getOrientationFromPlayer();
	bool collidesWithFleet(Ship ship);
	bool collidesWithShip(Ship ship1, Ship ship2);
	void autoPlaceShips();
	Ship* ships;
};

