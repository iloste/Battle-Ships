#include "Input.h"

const int Input::KeyCodeValues[10]{ 119, 97, 115, 100, 72, 80, 75,  77, 13, 114};


Input::KeyCode Input::getKeyCodeFromPlayer()
{
	int c = _getch();

	// if the arrow key is pressed _getch() returns twice. In that scenario, this function is called twice,
	// returning KeyCode::Arrow the first time and then which arrow was pressed.
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
