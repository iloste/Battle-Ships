#include "Input.h"

const int Input::KeyCodeValues[10]{ 119, 97, 115, 100, 72, 80, 75,  77, 13, 114};

Coordinate Input::getCoordinateFromPlayer() {
	Output::printInColour("Enter the x coordinate\n", Output::Colour::White);
	int x;
	std::cin >> x;

	Output::printInColour("Enter the y coordinate\n", Output::Colour::White);

	int y;
	std::cin >> y;

	return Coordinate(x, y);
}

Input::KeyCode Input::getKeyFromPlayer()
{
	int c = _getch();

	if (c == 224)
	{
		return KeyCode::Arrow;
	}

	KeyCode keyCode = KeyCode::Default;

	for (size_t i = 0; i < sizeof(KeyCodeValues) / sizeof(KeyCodeValues[0]); i++)
	{
		if (KeyCodeValues[i] == c)
		{
			keyCode = (KeyCode)i;
			break;
		}
	}

	return keyCode;
}
