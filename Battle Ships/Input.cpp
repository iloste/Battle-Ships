#include "Input.h"


Coordinate Input::getCoordinateFromPlayer() {
	Output::printInColour("Enter the x coordinate\n", Output::Colour::White);
	int x;
	std::cin >> x;

	Output::printInColour("Enter the y coordinate\n", Output::Colour::White);

	int y;
	std::cin >> y;

	return Coordinate(x, y);
}