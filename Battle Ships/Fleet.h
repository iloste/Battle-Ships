#pragma once
#include "Ship.h"
#include <vector>

class Fleet
{
public:
	//static const int numberOfShips;

	Fleet();
	//Fleet(bool autoPlaceShips);
	std::vector<Ship>  getShips();
	bool hitShip(Coordinate coord);
	bool fleetDestroyed();
	void manuallyPlaceShips();
	void autoPlaceShips();
	void addShip(Ship& newShip);
	bool shipCollidesWithFleet(Ship& ship);

private:
	static const int shipSizes[5];
	Coordinate getCoordinateFromPlayer();
	Ship::Orientation getOrientationFromPlayer();
	std::vector<Ship> ships{};
};

