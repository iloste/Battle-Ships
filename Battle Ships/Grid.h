#pragma once
#include "Fleet.h"
#include <iostream>
#include "Output.h"

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
	//to do: make a gridSize int to replace 10
	char grid[gridSize][gridSize]{};

	void initialiseGrid(bool aiControlled);
	void initialiseWaterTiles();
	void initiaiseShipTiles();
	Output::Colour getColour(char c);
};

