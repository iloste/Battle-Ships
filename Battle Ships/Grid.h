#pragma once
#include "Fleet.h"
#include <iostream>
#include "Output.h"
#include "Input.h"
//may not need this if the get key press is moved to input class
#include <conio.h>

class Grid
{
public:
	Grid();
	Grid(bool _aiControlled);
	void displayGrid();
	void takeShot(Coordinate _coord);
	bool fleetDestroyed();
	void manuallyPlaceShips();
	void autoPlaceShips();
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
	void initialiseShipTiles();
	void initiaiseEmptySpaceTiles();
	Output::Colour getColour(char c);
	void showShipOnGrid(Ship& ship);
	bool shipWouldBeWithinConfinesOfGrid(Ship& ship, Coordinate newPosition);
	bool shipWouldBeWithinConfinesOfGrid(Ship& ship, Ship::Orientation newOrientation);

	void updateShipPositionAndOrientation(Input::KeyCode keycode, Ship& ship);
};

