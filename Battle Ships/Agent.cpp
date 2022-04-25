#include "Agent.h"


void Agent::setOpponent(Agent* _opponent) {
	this->m_opponent = _opponent;
}


void Agent::takeShot(Coordinate _coord) {
	m_grid.takeShot(_coord);
}


void Agent::displayGrid()
{
	m_grid.displayGrid();
}


bool Agent::fleetDestroyed()
{
	return m_grid.fleetDestroyed();
}


void Agent::highlightCoordinateOnGrid(Coordinate _selectedCoordinate)
{
	m_grid.highlightCoordinate(_selectedCoordinate);
}


void Agent::unhighlightAllCoordinates()
{
	m_grid.unhighlighCoordinate();
}
