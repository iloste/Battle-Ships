#include "AI.h"


void AI::takeTurn()
{
	updateScreen();
	fireAtOpponent();
	updateScreen();

	// to do: change this so it's a timer?
	// enter for AI's turn
	std::cout << "Press enter to continue\n";
	std::string x;
	std::cin >> x;
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
	Output::printInColour("Opponent's turn\n");
	opponent->displayGrid();
}


