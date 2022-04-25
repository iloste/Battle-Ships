#pragma once
#include "Coordinate.h"
#include <vector>
#include <iostream>


class Ship
{
public:
	enum class Orientation
	{
		Horizontal,
		Vertical,
	};

	bool m_placedOnGrid;

	Ship();
	Ship(Coordinate _origin, int _size, Orientation _orientation);
	bool containsCoordinate(Coordinate _coordinate);
	void printCoords();

	bool isDestroyed();

	/// <summary>
	/// Returns true if any coordinate of this ship and the given ship intersect
	/// </summary>
	/// <param name="_ship"></param>
	/// <returns></returns>
	bool collidesWith(Ship& _ship);

	/// <summary>
	/// Recalculates the coordinates of the ships based on the orientation and the new origin point
	/// </summary>
	/// <param name="_newOrigin"></param>
	void resetCoordinates(Coordinate _newOrigin);

	/// <summary>
	/// Toggles the ship orientation between horizontal and vertical
	/// </summary>
	void rotate();
	
	int m_shipSize{};
	Orientation m_orientation{};
	std::vector<Coordinate> m_coordinates{};

private:
	std::vector<Coordinate> calculateCoordinatesOfShip(Coordinate _origin);
	bool* m_hitsTaken;

};


