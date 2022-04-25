#include "Grid.h"

//const int Grid::gridSize = 10;

Grid::Grid() {
	fleet = Fleet();
	//fleet.autoPlaceShips();
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
	for (size_t x = 0; x < secondGridSize; x++)
	{
		for (size_t y = 0; y < secondGridSize; y++)
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

		Output::printInColour(std::string(1, secondGrid[secondGridSize - 1][x]), getColour(secondGrid[secondGridSize - 1][x]));

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

char Grid::getCell(Coordinate _coord)
{
	if (!coordinateIsWithinBounds(_coord))
	{
		throw std::runtime_error("Coordinate " + _coord.toString() + " is outside the bounds of the grid");
	}

	return grid[_coord.x][_coord.y];
}

bool Grid::coordinateIsWithinBounds(Coordinate _coord)
{
	if (_coord.x < 0 || _coord.y < 0 || _coord.x >= gridSize || _coord.y >= gridSize)
	{
		return false;
	}

	return true;
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
	Coordinate movement = Coordinate(0, 0);

	switch (keycode)
	{
	case Input::KeyCode::Up:
	case Input::KeyCode::W:
		movement = Coordinate::down();
		break;
	case Input::KeyCode::Left:
	case Input::KeyCode::A:
		movement = Coordinate::left();
		break;
	case Input::KeyCode::Down:
	case Input::KeyCode::S:
		movement = Coordinate::up();
		break;
	case Input::KeyCode::Right:
	case Input::KeyCode::D:
		movement = Coordinate::right();
		break;
	case Input::KeyCode::Enter:
		break;
	case Input::KeyCode::R:
		ship.rotate();
		ship.resetCoordinates(ship.coordinates[0]);

		if (!shipWouldBeWithinConfinesOfGrid(ship, Coordinate(0, 0)))
		{
			ship.rotate();
			ship.resetCoordinates(ship.coordinates[0]);
		}
		break;
	case Input::KeyCode::Arrow:
		break;
	case Input::KeyCode::Default:
		break;
	default:
		break;
	}

	if (shipWouldBeWithinConfinesOfGrid(ship, movement))
	{
		Coordinate newPosition = ship.coordinates[0] + movement;
		ship.resetCoordinates(newPosition);
	}
}

Coordinate Grid::getRandomCoordinateForShip(int shipSize, Ship::Orientation orientation)
{
	int maxX = gridSize;
	int maxY = gridSize;

	if (orientation == Ship::Orientation::Horizontal)
	{
		maxX -= shipSize;
	}
	else {
		maxY -= shipSize;
	}

	int x = rand() % maxX;
	int y = rand() % maxY;

	return Coordinate(x, y);
}

void Grid::showShipOnGrid(Ship& ship)
{
	for (size_t i = 0; i < ship.coordinates.size(); i++)
	{
		grid[ship.coordinates[i].x][ship.coordinates[i].y] = 'o';
	}
}

bool Grid::shipWouldBeWithinConfinesOfGrid(Ship& ship, Coordinate movement)
{
	//check start of ship
	Coordinate newStartPosition = ship.coordinates[0] + movement;
	if (!coordinateIsWithinBounds(newStartPosition))
	{
		return false;
	}
	//check end of ship
	Coordinate newEndPosition = ship.coordinates[ship.shipSize - 1] + movement;
	if (!coordinateIsWithinBounds(newEndPosition))
	{
		return false;
	}

	return true;
}


void Grid::manuallyPlaceShips()
{
	// to do: make sure the ship can't be placed off grid
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


void Grid::autoPlaceShips()
{
	int shipsToPlace = 5;
	int shipsPlaced = 0;
	bool placingShip = true;
	int shipSizes[5] = { 5, 4, 3, 3, 2 };

	while (shipsPlaced < shipsToPlace)
	{
		Ship::Orientation orientation;

		if (rand() % 2 == 1)
		{
			orientation = Ship::Orientation::Horizontal;
		}
		else {
			orientation = Ship::Orientation::Vertical;
		}

		Coordinate origin = getRandomCoordinateForShip(shipSizes[shipsPlaced], orientation);
		Ship ship = Ship(origin, shipSizes[shipsPlaced], orientation);

		if (!fleet.shipCollidesWithFleet(ship))
		{
			fleet.addShip(ship);
			shipsPlaced++;
		}
	}
}

