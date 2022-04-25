#pragma once
#include "Grid.h"


class Agent
{
public:
	Grid m_grid{};
	Agent* m_opponent;

	virtual void takeTurn() = 0;
	void setOpponent(Agent* _opponent);
	virtual void takeShot(Coordinate _coord);
	virtual void displayGrid();
	bool fleetDestroyed();
	void highlightCoordinateOnGrid(Coordinate _selectedCoordinate);
	void unhighlightAllCoordinates();

protected:
	virtual void fireAtOpponent() = 0;
	virtual void updateScreen() = 0;
};

