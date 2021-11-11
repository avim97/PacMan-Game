#ifndef GHOST_H
#define GHOST_H

#include "Position.h"
#include "eColor.h"
#include <iostream>

class Ghost 
{
public:
	const Position initialPos ;

private:
	const char m_figure;
	eColor m_color;
	Position m_position;

public:
	Ghost(const int x, const int y, eColor color) : initialPos({x, y}), m_figure((const char)234), m_color(color), m_position(initialPos) {};
	void setPoint(int x, int y);
	void setColor();
	int getXcoord() const { return m_position.getXcoord(); };
	int getYcoord() const { return m_position.getYcoord(); };
	void setPosition(int x, int y)
	{
		m_position.setXcoord(x);
		m_position.setYcoord(y);
	}
};


#endif /* GHOST_H */