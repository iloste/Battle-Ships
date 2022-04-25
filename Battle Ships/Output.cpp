#include "Output.h"

const int Output::m_colourValues[5]{ 31, 32, 34, 37, 90 };

void Output::print(std::string _message, Colour _colour) {
	{
		std::string _colourValue = std::to_string(m_colourValues[(int)_colour]);
		_message = "\x1B[" + _colourValue + "m" + _message + "\033[0m";
		std::cout << _message;
	}
}


void Output::ClearScreen()
{
	std::cout << "\x1B[2J\x1B[H";
}
