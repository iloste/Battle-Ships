#include "Grid.h"

//const int Grid::gridSize = 10;

Grid::Grid() {
	fleet = Fleet(true);
	InitialiseGrid();
	DisplayGrid();
}


void Grid::InitialiseGrid() {
	InitialiseWaterTiles();
	InitiaiseShipTiles();
}


void Grid::InitialiseWaterTiles() {
	for (size_t x = 0; x < gridSize; x++)
	{
		for (size_t y = 0; y < gridSize; y++)
		{
			grid[x][y] = '~';
		}
	}
}

void Grid::InitiaiseShipTiles() {
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

void Grid::DisplayGrid() {
	Output::printInColour("  0 1 2 3 4 5 6 7 8 9\n", Output::Colour::White);

	for (size_t x = 0; x < gridSize; x++)
	{
		Output::printInColour(std::to_string(x) + " ", Output::Colour::White);

		for (size_t y = 0; y < gridSize; y++)
		{
			Output::printInColour(std::string(1, grid[y][x]) + " " , getColour(grid[y][x]));
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
	default:
		colour = Output::Colour::White;
		break;
	}

	return colour;
}

