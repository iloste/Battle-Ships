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

protected:
	virtual void fireAtOpponent() override;
	virtual void updateScreen() override;

private:
	std::vector<Coordinate> m_shotsTaken{};
	std::stack<Coordinate> m_nextShots{};

	/// <summary>
	/// Returns true if the AI has already fired at the given coordinate
	/// </summary>
	bool shotAlreadyTaken(Coordinate _coordinate);

	/// <summary>
	/// Adds the neighbours of the given coordinate to the stack of coordinates to choose from next
	/// </summary>
	/// <param name="_coordinate"></param>
	void addNextNeighboursToNextShot(Coordinate _coordinate);

	Coordinate getNextCoordinate();
};

