#pragma once
#include <string>
#include <sstream>

class Coordinate
{
public:
	int x{};
	int y{};

	Coordinate();
	Coordinate(int x, int y);

    Coordinate operator+(const Coordinate& _coord); 
    Coordinate operator-(const Coordinate& _coord); 
    bool operator==(const Coordinate& _coord); 
	std::string toString();

	static Coordinate up() { return Coordinate(0, 1); }
	static Coordinate down() { return Coordinate(0, -1); }
	static Coordinate left() { return Coordinate(-1, 0); }
	static Coordinate right() { return Coordinate(1, 0); }
};

