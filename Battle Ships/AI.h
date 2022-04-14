#pragma once
#include "Agent.h"


class AI : public Agent
{
public:
	virtual void takeTurn() override;

protected:
	virtual void fireAtOpponent() override;
	virtual void updateScreen() override;
};

