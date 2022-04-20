#pragma once
#include "Coordinate.h"

class AIHit
{
public:
	enum class Direction
	{
		North,
		East,
		South,
		West,
	};

	//TODO initialise the arrays using static const of m_numberOfNeighbours
	const int m_numberOfNeighbours = 4;
	Coordinate m_location;
	Coordinate m_neighbours[4];
	bool m_neighboursHit[4]{};

	AIHit();
	Coordinate getNextNighbourToHit();
	bool isSurroundedByHit();
	void markNeighbourHit(Direction direction);

private:
	void setNeighbours();

};

