#pragma once
#include "Agent.h"
#include "Input.h"

class AI : public Agent
{
public:
	virtual void takeTurn() override;

protected:
	virtual void fireAtOpponent() override;
	virtual void updateScreen() override;
};

