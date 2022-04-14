#include "Player.h"

Player::Player() {
	// to do: set this to false so player can place ships
	grid = Grid(true, false);
}

void Player::takeTurn()
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

void Player::fireAtOpponent()
{
	Coordinate coord = Input::getCoordinateFromPlayer();
	opponent->takeShot(coord);
}

void Player::updateScreen()
{
	Output::ClearScreen();
	Output::printInColour("Player's turn\n");
	opponent->displayGrid();
}



