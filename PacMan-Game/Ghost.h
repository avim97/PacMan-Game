#pragma once

#include "Position.h"
#include "eColor.h"
#include "Direction.h"
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
	int getXcoord() const { return m_position.getXcoord(); };
	int getYcoord() const { return m_position.getYcoord(); };
	const char getFigure() { return m_figure; };
	void setPosition(int x, int y) { m_position.setXcoord(x); m_position.setYcoord(y); };
	Position getPosition() { return m_position; };
	void setXcoord(int x) { m_position.setXcoord(x); };
	void setYcoord(int y) { m_position.setYcoord(y); };
};


