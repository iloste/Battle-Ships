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

		Arrow,
		// leave default as the last element
		Default,
	};


	static Coordinate getCoordinateFromPlayer();
	static KeyCode getKeyFromPlayer();

private:
	static const int KeyCodeValues[9];
};

