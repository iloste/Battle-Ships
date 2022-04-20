#pragma once
#include "Agent.h"
#include "Input.h"
#include <vector>
#include <stack>

class AI : public Agent
{
public:
	AI();
	virtual void takeTurn() override;
	Coordinate getNextCoordinate();

protected:
	virtual void fireAtOpponent() override;
	virtual void updateScreen() override;

private:
	std::vector<Coordinate> m_shotsTaken{};
	std::stack<Coordinate> m_nextShots{};

	bool shotAlreadyTaken(Coordinate _coordinate);
	void addNextNeighboursToNextShot(Coordinate _coordinate);
};

