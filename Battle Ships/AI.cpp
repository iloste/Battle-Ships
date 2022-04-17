#include "AI.h"


void AI::takeTurn()
{
	updateScreen();
	fireAtOpponent();
	updateScreen();

	Output::printInColour("Press enter to continue\n");
	Input::getKeyFromPlayer();
}

void AI::fireAtOpponent()
{
	int x = std::rand() % 10;
	int y = std::rand() % 10;
	Coordinate coord = Coordinate(x, y);
	opponent->takeShot(coord);
}

void AI::updateScreen()
{
	Output::ClearScreen();
	Output::printInColour("Opponent's turn\n", Output::Colour::Red);
	opponent->displayGrid();
}


