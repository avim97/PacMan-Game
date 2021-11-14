#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>
using namespace std;

#include "Position.h"
#include "eColor.h"
#include "Direction.h"

class Pacman
{
public:
	const Position initialPos = { 50,50 } ;

private:

	const char m_figure;
	eColor m_color;
	Position m_position;

	
public:
	Pacman() :  m_figure('@'), m_color(eColor::Yellow), m_position(initialPos) {};
	//void setColor() {}; //check
	int getXcoord() const { return m_position.getXcoord() ; };
	int getYcoord() const { return m_position.getYcoord() ; };
	const char getFigure() { return m_figure; };
	void setPosition(int x, int y) 
	{
		m_position.setXcoord(x);
		m_position.setYcoord(y);
	} // transfer to cpp.
	void Move(char nextDir);


	
};




#endif /* PACMAN_H */
