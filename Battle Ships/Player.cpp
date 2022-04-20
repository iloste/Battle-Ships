#include "Player.h"

Player::Player() {
	// to do: set this to false so player can place ships
	grid = Grid(false);
	grid.manuallyPlaceShips();
}

void Player::takeTurn()
{
	updateScreen();
	fireAtOpponent();
	updateScreen();

	Output::printInColour("Press enter to continue\n");
	Input::getKeyFromPlayer();
}

void Player::fireAtOpponent()
{
	Coordinate selectedCoordinate = getCoordinateFromPlayer();
	opponent->takeShot(selectedCoordinate);
}

Coordinate Player::getCoordinateFromPlayer()
{
	//TODO: make sure you can't leave grid when firing
	Coordinate selectedCoordinate = Coordinate(0, 0);
	opponent->setSelectedCoordinate(selectedCoordinate);
	updateScreen();
	Input::KeyCode keyCode;
	bool playerSelectingCoordinate = true;

	while (playerSelectingCoordinate)
	{
		keyCode = Input::getKeyFromPlayer();

		switch (keyCode)
		{
		case Input::KeyCode::W:
		case Input::KeyCode::Up:
			// adds down because 0, 0 of the grid starts at the top and to go down to 0, 1 you increase the coord value rather than decrease
			selectedCoordinate = selectedCoordinate + Coordinate::down();
			opponent->setSelectedCoordinate(selectedCoordinate);
			updateScreen();
			break;
		case Input::KeyCode::A:
		case Input::KeyCode::Left:
			selectedCoordinate = selectedCoordinate + Coordinate::left();
			opponent->setSelectedCoordinate(selectedCoordinate);
			updateScreen();
			break;
		case Input::KeyCode::S:
		case Input::KeyCode::Down:
			// adds up because 0, 0 of the grid starts at the top and to go down to 0, 1 you increase the coord value rather than decrease
			selectedCoordinate = selectedCoordinate + Coordinate::up();
			opponent->setSelectedCoordinate(selectedCoordinate);
			updateScreen();
			break;
		case Input::KeyCode::Right:
		case Input::KeyCode::D:
			selectedCoordinate = selectedCoordinate + Coordinate::right();
			opponent->setSelectedCoordinate(selectedCoordinate);
			updateScreen();
			break;
		case Input::KeyCode::Enter:
			opponent->unselectAllCoordinates();
			playerSelectingCoordinate = false;
			break;
		case Input::KeyCode::Arrow:
			//std::cout << "Arrow Pressed, Ignore this press\n";
			break;
		case Input::KeyCode::Default:
			std::cout << "Unrecognised Key\n";
			break;
		default:
			break;
		}
	}

	return selectedCoordinate;
}

void Player::updateScreen()
{
	Output::ClearScreen();
	Output::printInColour("Player's turn\n", Output::Colour::Green);
	opponent->displayGrid();
}
