#include "AI.h"

AI::AI()
{
	bool showShipsOnGrid = false;
	m_grid = Grid(showShipsOnGrid);
	m_grid.autoPlaceShips();
}


void AI::takeTurn()
{
	updateScreen();
	fireAtOpponent();
	updateScreen();

	Output::print("Press enter to continue\n");
	Input::getKeyCodeFromPlayer();
}


Coordinate AI::getNextCoordinate()
{
	Coordinate nextCoordinate = Coordinate(0, 0);

	while (!m_nextShots.empty())
	{
		nextCoordinate = m_nextShots.top();
		m_nextShots.pop();

		if (!shotAlreadyTaken(nextCoordinate))
		{
			m_shotsTaken.push_back(nextCoordinate);
			return nextCoordinate;
		}
	}

	bool findingValidCoordinate = true;

	while (findingValidCoordinate)
	{
		int x = std::rand() % 10;
		int y = std::rand() % 10;
		nextCoordinate = Coordinate(x, y);

		if (!shotAlreadyTaken(nextCoordinate))
		{
			findingValidCoordinate = false;
			m_shotsTaken.push_back(nextCoordinate);
		}
	}

	return nextCoordinate;
}


void AI::fireAtOpponent()
{
	Coordinate coord = getNextCoordinate();
	m_opponent->highlightCoordinateOnGrid(coord);
	m_opponent->takeShot(coord);

	if (m_opponent->m_grid.getCell(coord) == 'x')
	{
		addNextNeighboursToNextShot(coord);
	}
}


void AI::updateScreen()
{
	Output::ClearScreen();
	Output::print("Opponent's turn\n", Output::Colour::Red);
	m_opponent->displayGrid();
}


bool AI::shotAlreadyTaken(Coordinate _coordinate)
{
	for (size_t i = 0; i < m_shotsTaken.size(); i++)
	{
		if (m_shotsTaken[i] == _coordinate)
		{
			return true;
		}
	}

	return false;
}


void AI::addNextNeighboursToNextShot(Coordinate _coordinate)
{
	std::vector<Coordinate> neighbours{};
	neighbours.push_back(_coordinate + Coordinate::down());
	neighbours.push_back(_coordinate + Coordinate::right());
	neighbours.push_back(_coordinate + Coordinate::up());
	neighbours.push_back(_coordinate + Coordinate::left());

	for (size_t i = 0; i < neighbours.size(); i++)
	{
		if (!shotAlreadyTaken(neighbours[i]))
		{
			if (m_opponent->m_grid.coordinateIsWithinBounds(neighbours[i]))
			{
				m_nextShots.push(neighbours[i]);
			}
		}
	}
}
