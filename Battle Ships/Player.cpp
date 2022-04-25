#include "Player.h"

Player::Player() {
	bool showShipsOnGrid = true;
	m_grid = Grid(showShipsOnGrid);
	m_grid.manuallyPlaceShips();
}


void Player::takeTurn()
{
	updateScreen();
	fireAtOpponent();
	updateScreen();

	Output::print("Press enter to continue\n");
	Input::getKeyCodeFromPlayer();
}


void Player::fireAtOpponent()
{
	Coordinate selectedCoordinate = getCoordinateFromPlayer();
	m_opponent->takeShot(selectedCoordinate);
}


Coordinate Player::getCoordinateFromPlayer()
{
	Coordinate selectedCoordinate = Coordinate(0, 0);
	m_opponent->highlightCoordinateOnGrid(selectedCoordinate);
	updateScreen();
	Input::KeyCode keyCode;
	bool playerSelectingCoordinate = true;

	while (playerSelectingCoordinate)
	{
		keyCode = Input::getKeyCodeFromPlayer();

		switch (keyCode)
		{
		case Input::KeyCode::W:
		case Input::KeyCode::Up:
			if (m_opponent->m_grid.coordinateIsWithinBounds(selectedCoordinate + Coordinate::down()))
			{
				// adds down because 0, 0 of the grid starts at the top and to go down to 0, 1 you increase the coord value rather than decrease
				selectedCoordinate = selectedCoordinate + Coordinate::down();
				m_opponent->highlightCoordinateOnGrid(selectedCoordinate);
				updateScreen();
			}
			break;
		case Input::KeyCode::A:
		case Input::KeyCode::Left:
			if (m_opponent->m_grid.coordinateIsWithinBounds(selectedCoordinate + Coordinate::left()))
			{
				selectedCoordinate = selectedCoordinate + Coordinate::left();
				m_opponent->highlightCoordinateOnGrid(selectedCoordinate);
				updateScreen();
			}
			break;
		case Input::KeyCode::S:
		case Input::KeyCode::Down:
			if (m_opponent->m_grid.coordinateIsWithinBounds(selectedCoordinate + Coordinate::up()))
			{
				// adds up because 0, 0 of the grid starts at the top and to go down to 0, 1 you increase the coord value rather than decrease
				selectedCoordinate = selectedCoordinate + Coordinate::up();
				m_opponent->highlightCoordinateOnGrid(selectedCoordinate);
				updateScreen();
			}
			break;
		case Input::KeyCode::Right:
		case Input::KeyCode::D:
			if (m_opponent->m_grid.coordinateIsWithinBounds(selectedCoordinate + Coordinate::right()))
			{
				selectedCoordinate = selectedCoordinate + Coordinate::right();
				m_opponent->highlightCoordinateOnGrid(selectedCoordinate);
				updateScreen();
			}
			break;
		case Input::KeyCode::Enter:
			m_opponent->unhighlightAllCoordinates();
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
	Output::print("Player's turn\n", Output::Colour::Green);
	m_opponent->displayGrid();
}