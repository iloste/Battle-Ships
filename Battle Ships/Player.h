#pragma once
#include "Agent.h"
#include "Input.h"


class Player : public Agent
{
public:
	Player();
	virtual void takeTurn() override;

protected:
	virtual void fireAtOpponent() override;

private:
	Coordinate getCoordinateFromPlayer();






	// Inherited via Agent
	virtual void updateScreen() override;

};

