#ifndef POSITION_H
#define POSITION_H

#include "io_utils.h"
#include "Board.h"
class Position
{
private:
	int xCoord;
	int yCoord;
 
public:
	Position(const int x, const int y) : xCoord(x), yCoord(y) {}; //c'tor
	void setPosition(const int xCoord, const int yCoord) {};
	int getXcoord() const { return xCoord; } ;
	int getYcoord() const { return yCoord; };
	void setXcoord(int x) { xCoord = x; };
	void setYcoord(int y) { yCoord = y; };

};



#endif /* POSITION_H */
