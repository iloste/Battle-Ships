#pragma once
#include "Fleet.h"
#include <iostream>
#include "Output.h"

class Grid
{



public:
	Grid();
	void DisplayGrid();


private:
	Fleet fleet;
	static const int gridSize = 10;
	//to do: make a gridSize int to replace 10
	char grid[gridSize][gridSize]{};

	void InitialiseGrid();
	void InitialiseWaterTiles();
	void InitiaiseShipTiles();
	Output::Colour getColour(char c);
};

