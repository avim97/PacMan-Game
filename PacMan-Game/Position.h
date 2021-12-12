#pragma once


#include "io_utils.h"

class Position
{
private:
	int xCoord;
	int yCoord;
 
public:
	Position() : xCoord(0), yCoord(0) {};
	Position(const int x, const int y) : xCoord(x), yCoord(y) {}; 
	void setPosition(const int _xCoord, const int _yCoord) { xCoord = _xCoord; yCoord = _yCoord; };
	int getXcoord() const { return xCoord; } ;
	int getYcoord() const { return yCoord; };
	void setXcoord(int _xCoord) { xCoord = _xCoord; };
	void setYcoord(int _yCoord) { yCoord = _yCoord; };

};




