#include "Fleet.h"

const int Fleet::m_shipSizes[5]{ 5, 4, 3, 3, 2 };


Fleet::Fleet() {
	m_ships = std::vector<Ship>();
}


std::vector<Ship> Fleet::getShips() {
	return m_ships;
}


void Fleet::addShip(Ship& _newShip)
{
	m_ships.push_back(_newShip);
}


bool Fleet::shipCollidesWithFleet(Ship& _ship) {

	for (size_t i = 0; i < m_ships.size(); i++)
	{
		if (m_ships[i].collidesWith(_ship))
		{
			return true;
		}
	}

	return false;
}


bool Fleet::hitShipAtCoordinate(Coordinate _coord) {
	for (size_t i = 0; i < m_ships.size(); i++)
	{
		if (m_ships[i].containsCoordinate(_coord))
		{
			std::cout << "hit \n";
			return true;
		}
	}

	return false;
}


bool Fleet::fleetDestroyed()
{
	for (size_t i = 0; i < m_ships.size(); i++)
	{
		if (m_ships[i].isDestroyed() == false)
		{
			return false;
		}
	}

	return true;
}
