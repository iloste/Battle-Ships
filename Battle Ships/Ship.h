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

	bool placedOnBoard;

	Ship();
	Ship(Coordinate origin, int size, Orientation orientation);
	bool hitShip(Coordinate location);
	void printCoords();
	std::vector<Coordinate> getCoordinates(Coordinate origin);

	bool isDestroyed();
	bool collidesWith(Ship& ship);
	void resetCoordinates(Coordinate newOrigin);
	void rotate();
	
	int shipSize{};
	Orientation orientation{};
	std::vector<Coordinate> coordinates{};
	bool* hits;






};


