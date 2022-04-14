#include "Fleet.h"


const int Fleet::shipSizes[5]{ 5, 4, 3, 3, 2 };
const int Fleet::numberOfShips{ 5 };


Fleet::Fleet() {
	
}

Fleet::Fleet(bool _autoPlaceShips) {
	ships = new Ship[5]();

	// to do: give the player the option to autoplace ships too
	if (_autoPlaceShips)
	{
		autoPlaceShips();
	}
	else {
		placeShips();
	}
}

Ship* Fleet::getShips() {
	return ships;
}

void Fleet::autoPlaceShips() {
	int shipsPlaced = 0;

	while (shipsPlaced < 5)
	{
		// to do: randomise origin and orientation
		Coordinate origin = Coordinate(shipsPlaced, 0);
		Ship::Orientation orientation = Ship::Orientation::Vertical;
		Ship newShip = Ship(origin, shipSizes[shipsPlaced], orientation);

		if (!collidesWithFleet(newShip))
		{
			ships[shipsPlaced] = newShip;
			shipsPlaced++;
		}
	}

}

void Fleet::placeShips() {
	int shipsPlaced = 0;

	while (shipsPlaced < 5)
	{
		Coordinate origin = getCoordinateFromPlayer();
		Ship::Orientation orientation = getOrientationFromPlayer();
		Ship newShip = Ship(origin, shipSizes[shipsPlaced], orientation);

		if (!collidesWithFleet(newShip))
		{
			ships[shipsPlaced] = newShip;
			shipsPlaced++;
		}
		else {
			std::cout << "Ship collides with another. Please try again.\n";
		}
	}
}


Coordinate Fleet::getCoordinateFromPlayer() {
	std::cout << "Enter the x coordinate" << "\n";
	int x;
	std::cin >> x;

	std::cout << "Enter the y coordinate" << "\n";
	int y;
	std::cin >> y;

	return Coordinate(x, y);
}

Ship::Orientation Fleet::getOrientationFromPlayer() {
	std::cout << "Choose Horizontal (1) or Vertical (2)" << "\n";
	int playerInput;
	//to do: try parse this
	std::cin >> playerInput;

	if (playerInput == 1)
	{
		return Ship::Orientation::Horizontal;
	}
	else {
		return Ship::Orientation::Vertical;
	}
}


bool Fleet::collidesWithFleet(Ship ship) {

	for (size_t i = 0; i < numberOfShips; i++)
	{
		if (collidesWithShip(ship, ships[i]))
		{
			return true;
		}
	}

	return false;
}


bool Fleet::collidesWithShip(Ship ship1, Ship ship2) {
	if (!ship1.placedOnBoard || !ship2.placedOnBoard)
	{
		return false;
	}

	for (size_t i = 0; i < ship1.coordinates.size(); i++)
	{
		for (size_t j = 0; j < ship2.coordinates.size(); j++)
		{
			if (ship1.coordinates[i] == ship2.coordinates[j])
			{
				return true;
			}
		}
	}

	return false;
}


bool Fleet::hitShip(Coordinate coord) {
	for (size_t i = 0; i < numberOfShips; i++)
	{
		if (ships[i].hitShip(coord))
		{
			std::cout << "hit \n";
			return true;
		}
	}

	return false;
}

bool Fleet::fleetDestroyed()
{
	for (size_t i = 0; i < numberOfShips; i++)
	{
		if (ships[i].shipDestroyed() == false)
		{
			return false;
		}
	}

	return true;
}
