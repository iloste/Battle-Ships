#include "Fleet.h"


const int Fleet::shipSizes[5]{ 5, 4, 3, 3, 2 };


Fleet::Fleet() {
	//ships = new Ship[5]();
	ships = std::vector<Ship>();
}


std::vector<Ship> Fleet::getShips() {
	return ships;
}

void Fleet::autoPlaceShips() {
	//int shipsPlaced = 0;

	//while (shipsPlaced < 5)
	//{
	//	// to do: randomise origin and orientation
	//	Coordinate origin = Coordinate(shipsPlaced, 0);
	//	Ship::Orientation orientation = Ship::Orientation::Vertical;
	//	Ship newShip = Ship(origin, shipSizes[shipsPlaced], orientation);

	//	if (!shipCollidesWithFleet(newShip))
	//	{
	//		ships.push_back(newShip);
	//		shipsPlaced++;
	//	}
	//}

}

void Fleet::addShip(Ship& newShip)
{
	ships.push_back(newShip);
}

//void Fleet::manuallyPlaceShips() {
//	int shipsPlaced = 0;
//
//	while (shipsPlaced < 5)
//	{
//		Coordinate origin = getCoordinateFromPlayer();
//		Ship::Orientation orientation = getOrientationFromPlayer();
//		Ship newShip = Ship(origin, shipSizes[shipsPlaced], orientation);
//
//		if (!shipCollidesWithFleet(newShip))
//		{
//			ships.push_back(newShip);
//			shipsPlaced++;
//		}
//		else {
//			std::cout << "Ship collides with another. Please try again.\n";
//		}
//	}
//}
//

Coordinate Fleet::getCoordinateFromPlayer() {
	std::cout << "Enter the x coordinate" << "\n";
	int x;
	std::cin >> x;

	std::cout << "Enter the y coordinate" << "\n";
	int y;
	std::cin >> y;

	return Coordinate(x, y);
}

//Ship::Orientation Fleet::getOrientationFromPlayer() {
//	std::cout << "Choose Horizontal (1) or Vertical (2)" << "\n";
//	int playerInput;
//	//to do: try parse this
//	std::cin >> playerInput;
//
//	if (playerInput == 1)
//	{
//		return Ship::Orientation::Horizontal;
//	}
//	else {
//		return Ship::Orientation::Vertical;
//	}
//}


bool Fleet::shipCollidesWithFleet(Ship& ship) {

	for (size_t i = 0; i < ships.size(); i++)
	{
		if (ships[i].collidesWith(ship))
		{
			return true;
		}
	}

	return false;
}





bool Fleet::hitShip(Coordinate coord) {
	for (size_t i = 0; i < ships.size(); i++)
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
	for (size_t i = 0; i < ships.size(); i++)
	{
		if (ships[i].isDestroyed() == false)
		{
			return false;
		}
	}

	return true;
}
