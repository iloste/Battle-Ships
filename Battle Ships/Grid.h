#pragma once
#include "Fleet.h"
#include <iostream>
#include "Output.h"
//may not need this if the get key press is moved to input class
#include <conio.h>


class Grid
{



public:
	Grid();
	Grid(bool _autoPlaceShips, bool _aiControlled);
	void displayGrid();
	void takeShot(Coordinate _coord);
	bool fleetDestroyed();

private:
	Fleet fleet;
	static const int gridSize = 10;
	char grid[gridSize][gridSize]{};

	Coordinate currentLocation{};
	void moveLocation();


	void initialiseGrid(bool aiControlled);
	void initialiseWaterTiles();
	void initiaiseShipTiles();
	Output::Colour getColour(char c);
};

