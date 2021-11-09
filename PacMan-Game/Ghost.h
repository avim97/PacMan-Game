#ifndef GHOST_H
#define GHOST_H

#include "Position.h"
#include <iostream>

class ghost 
{

private:
	position position;
	const char figure=234;
	//color
public:
	void setPoint(int x, int y);
	void setColor();


};


#endif /* GHOST_H */