#include "Grid.h"

//const int Grid::gridSize = 10;

Grid::Grid() {
	fleet = Fleet();
	fleet.autoPlaceShips();
	initialiseGrid(true);
}

Grid::Grid(bool aiControlled) {
	// to do: remove autoplace ship 
	fleet = Fleet();
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
		initialiseShipTiles();
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

void Grid::initialiseShipTiles() {
	std::vector<Ship> ships = fleet.getShips();

	for (size_t i = 0; i < ships.size(); i++)
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


void Grid::updateShipPositionAndOrientation(Input::KeyCode keycode, Ship& ship)
{
	Coordinate coordinate = ship.coordinates[0];

	switch (keycode)
	{
	case Input::KeyCode::Up:
	case Input::KeyCode::W:
		coordinate = coordinate + Coordinate::down();
		break;
	case Input::KeyCode::Left:
	case Input::KeyCode::A:
		coordinate = coordinate + Coordinate::left();
		break;
	case Input::KeyCode::Down:
	case Input::KeyCode::S:
		coordinate = coordinate + Coordinate::up();
		break;
	case Input::KeyCode::Right:
	case Input::KeyCode::D:
		coordinate = coordinate + Coordinate::right();
		break;
	case Input::KeyCode::Enter:
		break;
	case Input::KeyCode::R:
		ship.rotate();
		break;
	case Input::KeyCode::Arrow:
		break;
	case Input::KeyCode::Default:
		break;
	default:
		break;
	}

	ship.resetCoordinates(coordinate);
}

void Grid::showShipOnGrid(Ship& ship)
{
	for (size_t i = 0; i < ship.coordinates.size(); i++)
	{
		grid[ship.coordinates[i].x][ship.coordinates[i].y] = 'o';
	}
}


void Grid::manuallyPlaceShips()
{
	int shipsToPlace = 5;
	int shipsPlaced = 0;
	bool placingShip = true;
	int shipSizes[5] = { 5, 4, 3, 3, 2 };
	Ship newShip = Ship(Coordinate(0, 0), shipSizes[shipsPlaced], Ship::Orientation::Horizontal);
	Input::KeyCode keycode;
	std::string errorMessage = "";

	while (shipsPlaced < shipsToPlace)
	{
		setSelectedCoordinate(newShip.coordinates[0]);
		initialiseWaterTiles();
		initialiseShipTiles();
		showShipOnGrid(newShip);
		Output::ClearScreen();
		Output::printInColour("Place your ships\n", Output::Colour::Green);
		displayGrid();

		#pragma region Print Controls
		Output::printInColour("Press");
		Output::printInColour(" Enter ", Output::Colour::Green);
		Output::printInColour("to place ship\n");
		Output::printInColour("Press");
		Output::printInColour(" R ", Output::Colour::Green);
		Output::printInColour("to rotate ship\n");
		#pragma endregion
		Output::printInColour(errorMessage, Output::Colour::Red);

		keycode = Input::getKeyFromPlayer();
		errorMessage = "";
		updateShipPositionAndOrientation(keycode, newShip);

		if (keycode == Input::KeyCode::Enter)
		{
			if (!fleet.shipCollidesWithFleet(newShip))
			{
				fleet.addShip(newShip);
				shipsPlaced++;

				if (shipsPlaced < shipsToPlace)
				{
					newShip = Ship(Coordinate(0, 0), shipSizes[shipsPlaced], Ship::Orientation::Horizontal);
				}
			}
			else {
				errorMessage = "Invalid location, try again\n";
			}
		}
	}

	unselectAllCoordinates();
}

