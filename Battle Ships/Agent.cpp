#include "Agent.h"


void Agent::setOpponent(Agent* opponent) {
	this->opponent = opponent;
}

void Agent::takeShot(Coordinate coord) {
	grid.takeShot(coord);
}

void Agent::displayGrid()
{
	grid.displayGrid();
}





bool Agent::fleetDestroyed()
{
	return grid.fleetDestroyed();
}

void Agent::setSelectedCoordinate(Coordinate _selectedCoordinate)
{
	grid.setSelectedCoordinate(_selectedCoordinate);
}

void Agent::unselectAllCoordinates()
{
	grid.unselectAllCoordinates();
}
