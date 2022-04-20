#include "AIHit.h"

AIHit::AIHit()
{
}

Coordinate AIHit::getNextNighbourToHit()
{
	if (!m_neighboursHit[0])
	{
		return m_neighbours[0];
	}
	else if (!m_neighboursHit[1])
	{
		return m_neighbours[1];
	}
	else if (!m_neighboursHit[2])
	{
		return m_neighbours[2];
	}
	else if (!m_neighboursHit[3])
	{
		return m_neighbours[3];
	}
}

bool AIHit::isSurroundedByHit()
{
	for (size_t i = 0; i < m_numberOfNeighbours; i++)
	{
		if (m_neighboursHit[i] == false)
		{
			return false;
		}
	}

	return true;
}

void AIHit::setNeighbours()
{
	// North/East/South/West. it starts with down because (0, 0) of the grid is at the top and increasing 
	// the y value goes down the console.
	m_neighbours[0] = m_location + Coordinate::down();
	m_neighbours[1] = m_location + Coordinate::right();
	m_neighbours[2] = m_location + Coordinate::up();
	m_neighbours[3] = m_location + Coordinate::left();
}
