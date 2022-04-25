#include "Grid.h"

Grid::Grid() {
	m_fleet = Fleet();
	bool showShipsOnGrid = true;
	initialiseGrid(showShipsOnGrid);
}


Grid::Grid(bool _showShipsOnGrid) {
	m_fleet = Fleet();
	initialiseGrid(_showShipsOnGrid);
}


void Grid::initialiseGrid(bool _showShipsOnGrid) {
	initialiseWaterTiles();

	if (_showShipsOnGrid)
	{
		initialiseShipTiles();
	}

	initiaiseSpacingTiles();
}


void Grid::initialiseWaterTiles() {
	for (size_t x = 0; x < m_gridSize; x++)
	{
		for (size_t y = 0; y < m_gridSize; y++)
		{
			m_grid[x][y] = '~';
		}
	}
}


void Grid::initiaiseSpacingTiles() {
	for (size_t x = 0; x < m_spacingGridSize; x++)
	{
		for (size_t y = 0; y < m_spacingGridSize; y++)
		{
			m_spacingGrid[x][y] = ' ';
		}
	}
}


void Grid::initialiseShipTiles() {
	std::vector<Ship> ships = m_fleet.getShips();

	for (size_t i = 0; i < ships.size(); i++)
	{
		for (size_t j = 0; j < ships[i].m_coordinates.size(); j++)
		{
			Coordinate coord = ships[i].m_coordinates[j];
			m_grid[coord.x][coord.y] = 'o';
		}
	}
}


void Grid::displayGrid() {
	Output::print("   0 1 2 3 4 5 6 7 8 9\n", Output::Colour::White);

	for (size_t x = 0; x < m_gridSize; x++)
	{
		Output::print(std::to_string(x) + " ", Output::Colour::White);

		for (size_t y = 0; y < m_gridSize; y++)
		{
			// prints the spacing inbetween the grid tiles.
			Output::print(std::string(1, m_spacingGrid[y][x]), getColour(m_spacingGrid[y][x]));
			// prints the grid tiles
			Output::print(std::string(1, m_grid[y][x]), getColour(m_grid[y][x]));
		}

		// prints last empty space at the end of the line (used to highligth last tile in row if needed)
		Output::print(std::string(1, m_spacingGrid[m_spacingGridSize - 1][x]), getColour(m_spacingGrid[m_spacingGridSize - 1][x]));

		std::cout << "\n";
	}
}


Output::Colour Grid::getColour(char _c) {
	Output::Colour colour;

	switch (_c)
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


void Grid::highlightCoordinate(Coordinate _coord)
{
	initiaiseSpacingTiles();
	m_spacingGrid[_coord.x][_coord.y] = '|';
	m_spacingGrid[_coord.x + 1][_coord.y] = '|';
}


void Grid::unhighlighCoordinate()
{
	initiaiseSpacingTiles();
}


char Grid::getCell(Coordinate _coord)
{
	if (!coordinateIsWithinBounds(_coord))
	{
		throw std::runtime_error("Coordinate " + _coord.toString() + " is outside the bounds of the grid");
	}

	return m_grid[_coord.x][_coord.y];
}


bool Grid::coordinateIsWithinBounds(Coordinate _coord)
{
	if (_coord.x < 0 || _coord.y < 0 || _coord.x >= m_gridSize || _coord.y >= m_gridSize)
	{
		return false;
	}

	return true;
}


void Grid::takeShot(Coordinate _coord) {
	if (m_fleet.hitShipAtCoordinate(_coord)) {
		m_grid[_coord.x][_coord.y] = 'x';
	}
	else {
		m_grid[_coord.x][_coord.y] = '@';
	}
}


bool Grid::fleetDestroyed()
{
	return m_fleet.fleetDestroyed();
}


void Grid::updateShipPositionAndOrientation(Input::KeyCode _keycode, Ship& _ship)
{
	Coordinate movement = Coordinate(0, 0);

	switch (_keycode)
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
		_ship.rotate();
		_ship.resetCoordinates(_ship.m_coordinates[0]);

		if (!shipWouldBeWithinConfinesOfGrid(_ship, Coordinate(0, 0)))
		{
			_ship.rotate();
			_ship.resetCoordinates(_ship.m_coordinates[0]);
		}
		break;
	case Input::KeyCode::Arrow:
		break;
	case Input::KeyCode::Default:
		break;
	default:
		break;
	}

	if (shipWouldBeWithinConfinesOfGrid(_ship, movement))
	{
		Coordinate newPosition = _ship.m_coordinates[0] + movement;
		_ship.resetCoordinates(newPosition);
	}
}


Coordinate Grid::getRandomCoordinateForShip(int _shipSize, Ship::Orientation _orientation)
{
	int maxX = m_gridSize;
	int maxY = m_gridSize;

	if (_orientation == Ship::Orientation::Horizontal)
	{
		maxX -= _shipSize;
	}
	else {
		maxY -= _shipSize;
	}

	int x = rand() % maxX;
	int y = rand() % maxY;

	return Coordinate(x, y);
}


void Grid::showShipOnGrid(Ship& _ship)
{
	for (size_t i = 0; i < _ship.m_coordinates.size(); i++)
	{
		m_grid[_ship.m_coordinates[i].x][_ship.m_coordinates[i].y] = 'o';
	}
}


bool Grid::shipWouldBeWithinConfinesOfGrid(Ship& _ship, Coordinate _movement)
{
	//check start of ship
	Coordinate newStartPosition = _ship.m_coordinates[0] + _movement;
	if (!coordinateIsWithinBounds(newStartPosition))
	{
		return false;
	}
	//check end of ship
	Coordinate newEndPosition = _ship.m_coordinates[_ship.m_shipSize - 1] + _movement;
	if (!coordinateIsWithinBounds(newEndPosition))
	{
		return false;
	}

	return true;
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
		highlightCoordinate(newShip.m_coordinates[0]);
		initialiseWaterTiles();
		initialiseShipTiles();
		showShipOnGrid(newShip);
		Output::ClearScreen();
		Output::print("Place your ships\n", Output::Colour::Green);
		displayGrid();

#pragma region Print Controls
		Output::print("Press");
		Output::print(" Enter ", Output::Colour::Green);
		Output::print("to place ship\n");
		Output::print("Press");
		Output::print(" R ", Output::Colour::Green);
		Output::print("to rotate ship\n");
		Output::print("Press");
		Output::print(" WASD/Arrow keys ", Output::Colour::Green);
		Output::print("to move\n");
#pragma endregion
		Output::print(errorMessage, Output::Colour::Red);

		keycode = Input::getKeyCodeFromPlayer();
		errorMessage = "";
		updateShipPositionAndOrientation(keycode, newShip);

		if (keycode == Input::KeyCode::Enter)
		{
			if (!m_fleet.shipCollidesWithFleet(newShip))
			{
				m_fleet.addShip(newShip);
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

	unhighlighCoordinate();
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

		if (!m_fleet.shipCollidesWithFleet(ship))
		{
			m_fleet.addShip(ship);
			shipsPlaced++;
		}
	}
}