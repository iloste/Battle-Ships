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
	void placeShips();
	void setSelectedCoordinate(Coordinate _coord);
	void unselectAllCoordinates();

private:
	Fleet fleet;
	static const int gridSize = 10;
	char grid[gridSize][gridSize]{};
	char secondGrid[gridSize + 1][gridSize + 1]{};

	Coordinate currentLocation{};
	void moveLocation();


	void initialiseGrid(bool aiControlled);
	void initialiseWaterTiles();
	void initiaiseShipTiles();
	void initiaiseEmptySpaceTiles();
	Output::Colour getColour(char c);
};

