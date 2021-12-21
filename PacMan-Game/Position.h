#pragma once
#include "io_utils.h"

class Position
{
private:
	int yCoord;
	int xCoord;
public:
	Position() : xCoord(0), yCoord(0){};
	Position(const int _xCoord, const int _yCoord) : xCoord(_xCoord), yCoord(_yCoord) {};
	bool operator==(const Position& _Position) const;
	void setPosition(const int _xCoord, const int _yCoord) { xCoord = _xCoord; yCoord = _yCoord; };
	int getXcoord() const { return xCoord; };
	int getYcoord() const { return yCoord; };
	void setXcoord(const int _xCoord) { xCoord = _xCoord; };
	void setYcoord(const int _yCoord) { yCoord = _yCoord; };

};




