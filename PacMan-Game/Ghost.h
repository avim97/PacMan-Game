#pragma once

#include "Position.h"
#include "Color.h"
#include "eBoardObjects.h"
#include "Direction.h"
#include <iostream>


class Ghost 
{
public:
	const Position initialPos ;

private:
	const char m_figure;
	Color m_color;
	Position m_position;

public:
	Ghost(const int x, const int y, Color::eColor color) : initialPos({x, y}), m_figure((int)BoardObjects::GHOST), m_color(color), m_position(initialPos) {};
	void setColor(Color::eColor color) { m_color = color; };
	Color getColor() { return m_color; };
	int getXcoord() const { return m_position.getXcoord(); };
	int getYcoord() const { return m_position.getYcoord(); };
	const char getFigure() { return m_figure; };
	void setPosition(int x, int y) { m_position.setXcoord(x); m_position.setYcoord(y); };
	Position getPosition() { return m_position; };
	void setXcoord(int x) { m_position.setXcoord(x); };
	void setYcoord(int y) { m_position.setYcoord(y); };
};


