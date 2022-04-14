#pragma once
#include <string>
#include <iostream>

static class Output
{

public:
	enum class Colour
	{
		Red,
		Green,
		Blue,
		White,
		Grey,
	};

	static  const int colourValues[5];

	static void printInColour(std::string message, Colour colour = Colour::White);
	static void ClearScreen();
};

