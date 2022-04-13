#pragma once
class Coordinate
{

public:
	int x{};
	int y{};

	Coordinate();
	Coordinate(int x, int y);

    Coordinate operator+(const Coordinate& coord); 
    Coordinate operator-(const Coordinate& coord); 
    bool operator==(const Coordinate& coord); 


};

