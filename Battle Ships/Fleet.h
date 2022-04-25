#pragma once
#include "Ship.h"
#include <vector>

class Fleet
{
public:

	Fleet();
	std::vector<Ship> getShips();

	/// <summary>
	/// Returns true if part of one of the ships is at the given coordinate
	/// </summary>
	bool hitShipAtCoordinate(Coordinate coord);

	bool fleetDestroyed();
	void addShip(Ship& newShip);

	/// <summary>
	/// Returns true if the given ship's coordinates intersect with any of the current ships in the fleet
	/// </summary>
	bool shipCollidesWithFleet(Ship& ship);

private:
	static const int m_shipSizes[5];
	std::vector<Ship> m_ships{};
};

