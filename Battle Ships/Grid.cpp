#include "Grid.h"

//const int Grid::gridSize = 10;

Grid::Grid() {
	fleet = Fleet();
	fleet.autoPlaceShips();
	initialiseGrid(true);
}

Grid::Grid(bool _autoPlaceShips, bool aiControlled) {
	// to do: remove autoplace ship 
	fleet = Fleet();
	if (_autoPlaceShips)
	{
		fleet.autoPlaceShips();
	}
	else {
		fleet.manuallyPlaceShips();
	}

	initialiseGrid(aiControlled);
}


void Grid::moveLocation()
{
	int c = _getch();
}

void Grid::initialiseGrid(bool aiControlled) {
	initialiseWaterTiles();

	if (!aiControlled)
	{
		initiaiseShipTiles();
	}

	initiaiseEmptySpaceTiles();
}


void Grid::initialiseWaterTiles() {
	for (size_t x = 0; x < gridSize; x++)
	{
		for (size_t y = 0; y < gridSize; y++)
		{
			grid[x][y] = '~';
		}
	}
}


void Grid::initiaiseEmptySpaceTiles() {
	for (size_t x = 0; x < gridSize; x++)
	{
		for (size_t y = 0; y < gridSize; y++)
		{
			secondGrid[x][y] = ' ';
		}
	}
}

void Grid::initiaiseShipTiles() {
	Ship* ships = fleet.getShips();

	for (size_t i = 0; i < fleet.numberOfShips; i++)
	{
		for (size_t j = 0; j < ships[i].coordinates.size(); j++)
		{
			Coordinate coord = ships[i].coordinates[j];
			grid[coord.x][coord.y] = 'o';
		}
	}
}

void Grid::displayGrid() {
	Output::printInColour("   0 1 2 3 4 5 6 7 8 9\n", Output::Colour::White);

	for (size_t x = 0; x < gridSize; x++)
	{
		Output::printInColour(std::to_string(x) + " ", Output::Colour::White);

		for (size_t y = 0; y < gridSize; y++)
		{
			Output::printInColour(std::string(1, secondGrid[y][x]), getColour(secondGrid[y][x]));
			Output::printInColour(std::string(1, grid[y][x]), getColour(grid[y][x]));
		}

		std::cout << "\n";
	}
}



Output::Colour Grid::getColour(char c) {
	Output::Colour colour;

	switch (c)
	{
	case '@':
	case '~':
		colour = Output::Colour::Blue;
		break;
	case 'o':
		colour = Output::Colour::Grey;
		break;
	case 'x':
		colour = Output::Colour::Red;
		break;
	case '|':
	case '-':
		colour = Output::Colour::Green;
		break;
	default:
		colour = Output::Colour::White;
		break;
	}

	return colour;
}

void Grid::setSelectedCoordinate(Coordinate _coord)
{
	initiaiseEmptySpaceTiles();
	secondGrid[_coord.x][_coord.y] = '|';
	secondGrid[_coord.x + 1][_coord.y] = '|';
}

void Grid::unselectAllCoordinates()
{
	initiaiseEmptySpaceTiles();
}


void Grid::takeShot(Coordinate coord) {
	if (fleet.hitShip(coord)) {
		grid[coord.x][coord.y] = 'x';
	}
	else {
		grid[coord.x][coord.y] = '@';
	}
}

bool Grid::fleetDestroyed()
{
	return fleet.fleetDestroyed();
}

void Grid::placeShips()
{
}

