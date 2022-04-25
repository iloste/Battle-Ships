#include "Ship.h"


Ship::Ship() {
	m_shipSize = 1;
	m_orientation = Orientation::Horizontal;
	m_hitsTaken = new bool[1];
	m_coordinates = calculateCoordinatesOfShip(Coordinate(-1, -1));
	m_placedOnGrid = false;
}


Ship::Ship(Coordinate _origin, int _shipSize, Orientation _orientation) {
	this->m_shipSize = _shipSize;
	this->m_orientation = _orientation;
	m_hitsTaken = new bool[_shipSize]();
	m_coordinates = calculateCoordinatesOfShip(_origin);
	m_placedOnGrid = true;
}


bool Ship::containsCoordinate(Coordinate _coordinate) {
	for (size_t i = 0; i < m_coordinates.size(); i++)
	{
		if (m_coordinates[i] == _coordinate)
		{
			m_hitsTaken[i] = true;
			return true;
		}
	}

	return false;
}

std::vector<Coordinate> Ship::calculateCoordinatesOfShip(Coordinate _origin) {
	std::vector<Coordinate> coords{};
	Coordinate nextCoord = _origin;
	Coordinate directionCoord;
	
	if (m_orientation == Orientation::Horizontal)
	{
		directionCoord = Coordinate(1, 0);
	}
	else 
	{
		directionCoord = Coordinate(0, 1);
	}

	for (size_t i = 0; i < m_shipSize; i++)
	{
		coords.push_back(nextCoord);
		nextCoord = nextCoord + directionCoord;
	}

	return coords;
}


bool Ship::isDestroyed()
{
	for (size_t i = 0; i < m_shipSize; i++)
	{
		if (m_hitsTaken[i] == false)
		{
			return false;
		}
	}

	return true;
}


bool Ship::collidesWith(Ship& _ship)
{
	if (!this->m_placedOnGrid || !_ship.m_placedOnGrid)
	{
		return false;
	}

	for (size_t i = 0; i < this->m_coordinates.size(); i++)
	{
		for (size_t j = 0; j < _ship.m_coordinates.size(); j++)
		{
			if (this->m_coordinates[i] == _ship.m_coordinates[j])
			{
				return true;
			}
		}
	}

	return false;
}


void Ship::resetCoordinates(Coordinate _newOrigin)
{
	m_coordinates = calculateCoordinatesOfShip(_newOrigin);
}


void Ship::rotate()
{
	if (m_orientation == Orientation::Horizontal)
	{
		m_orientation = Orientation::Vertical;
	}
	else {
		m_orientation = Orientation::Horizontal;
	}
}


void Ship::printCoords() {
	std::cout << "Ships coordinates: ";

	for (size_t i = 0; i < m_coordinates.size(); i++)
	{
		std::cout << "(" << m_coordinates[i].x << ", " << m_coordinates[i].y << ")";

		if (i + 1 < m_coordinates.size())
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}