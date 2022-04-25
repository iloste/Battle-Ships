#pragma once
#include "Coordinate.h"
#include <iostream>
#include "Output.h"
#include <conio.h>


static class Input
{
public:
	enum class KeyCode
	{
		W, 
		A, 
		S, 
		D, 
		Up,
		Down, 
		Left, 
		Right,
		Enter,
		R,

		Arrow,
		// leave default as the last element
		Default,
	};

	/// <summary>
	/// Returns the key that was pressed.
	/// If the arrow key was pressed, it first returns KeyCode::Arrow, then the arrow key that was pressed
	/// </summary>
	/// <returns></returns>
	static KeyCode getKeyCodeFromPlayer();

private:
	static const int KeyCodeValues[10];
};

