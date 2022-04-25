#include "AI.h"




AI::AI()
{
	bool showShipsOnGrid = false;
	grid = Grid(showShipsOnGrid);
	grid.autoPlaceShips();
}


void AI::takeTurn()
{
	updateScreen();
	fireAtOpponent();
	updateScreen();

	Output::printInColour("Press enter to continue\n");
	Input::getKeyFromPlayer();
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
	opponent->setSelectedCoordinate(coord);
	opponent->takeShot(coord);

	if (opponent->grid.getCell(coord) == 'x')
	{
		addNextNeighboursToNextShot(coord);
	}
}


void AI::updateScreen()
{
	Output::ClearScreen();
	Output::printInColour("Opponent's turn\n", Output::Colour::Red);
	opponent->displayGrid();
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
			if (opponent->grid.coordinateIsWithinBounds(neighbours[i]))
			{
				m_nextShots.push(neighbours[i]);
			}
		}
	}
}


