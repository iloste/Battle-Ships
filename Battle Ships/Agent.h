#pragma once
#include "Grid.h"


class Agent
{
public:
	Grid grid{};
	Agent* opponent;

	virtual void takeTurn() = 0;
	void setOpponent(Agent* opponent);
	virtual void takeShot(Coordinate coord);
	virtual void displayGrid();
	bool fleetDestroyed();

protected:
	virtual void fireAtOpponent() = 0;
	virtual void updateScreen() = 0;
};

