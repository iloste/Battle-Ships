#include "Output.h"

const int Output::colourValues[5]{ 31, 32, 34, 37, 90 };

void Output::printInColour(std::string message, Colour colour) {
	{
		std::string _colourValue = std::to_string(colourValues[(int)colour]);
		message = "\x1B[" + _colourValue + "m" + message + "\033[0m";
		std::cout << message;
	}
}