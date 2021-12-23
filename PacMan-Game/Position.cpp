#include "Position.h"



bool Position::operator==(const Position& _Position) const 
{
	if ((this->xCoord == _Position.getXcoord()) && (this->yCoord == _Position.getYcoord()))
		return true;
	else
		return false;
}