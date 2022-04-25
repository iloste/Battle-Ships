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


	static void print(std::string _message, Colour _colour = Colour::White);
	static void ClearScreen();


private:
	static const int m_colourValues[5];

};

