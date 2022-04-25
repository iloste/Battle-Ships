#pragma once
#include "Fleet.h"
#include <iostream>
#include "Output.h"
#include "Input.h"
#include <stdexcept>

class Grid
{
public:
	Grid();
	Grid(bool _aiControlled);
	void displayGrid();
	/// <summary>
	/// Determines whether the shot hits or misses
	/// </summary>
	void takeShot(Coordinate _coord);
	bool fleetDestroyed();
	void manuallyPlaceShips();
	void autoPlaceShips();

	/// <summary>
	/// Highlights the given coordinate with a green line either side.
	/// </summary>
	/// <param name="_coord"></param>
	void highlightCoordinate(Coordinate _coord);

	void unhighlighCoordinate();
	char getCell(Coordinate _coord);
	bool coordinateIsWithinBounds(Coordinate _coord);

private:
	Fleet m_fleet;
	static const int m_gridSize = 10;
	char m_grid[m_gridSize][m_gridSize]{};
	static const int m_spacingGridSize = 11;
	char m_spacingGrid[m_spacingGridSize][m_spacingGridSize]{};

	void initialiseGrid(bool _showShips);
	void initialiseWaterTiles();
	void initialiseShipTiles();
	void initiaiseSpacingTiles();

	/// <summary>
	/// Returns the color to use based on the symbol of the given character. Eg '~' returns Blue
	/// </summary>
	Output::Colour getColour(char _c);

	void showShipOnGrid(Ship& _ship);
	bool shipWouldBeWithinConfinesOfGrid(Ship& _ship, Coordinate _newPosition);

	/// <summary>
	/// Moves/rotates the given ships based on the keycode
	/// </summary>
	/// <param name="_keycode">Keyboard button pressed</param>
	void updateShipPositionAndOrientation(Input::KeyCode _keycode, Ship& _ship);

	/// <summary>
	/// Returns a coordinate that a ship could be placed, based on size and orientation, 
	/// so no part of it will be out of bounds.
	/// </summary>
	Coordinate getRandomCoordinateForShip(int _shipSize, Ship::Orientation _orientation);
};

