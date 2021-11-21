#pragma once


#include <iostream>
#include "Direction.h"
#include "Position.h"
#include "Color.h"
#include "eBoardObjects.h"

using namespace std;


class Pacman
{
public:
	const Position initialPos = { 36, 14 };

private:

	const char m_figure;
	Color m_color;
	Position m_position;
	char m_currDir;


public:
	Pacman() : m_figure((int)BoardObjects::PACMAN), m_color(Color::eColor::Yellow), m_position(initialPos), m_currDir((char)Direction::eDirection::STAY) {};
	void setColor(Color::eColor color) { m_color = color; };
	Color getColor() { return m_color; };
	int getXcoord() const { return m_position.getXcoord(); };
	int getYcoord() const { return m_position.getYcoord(); };
	Position getPosition() { return m_position; };
	const char getFigure() { return m_figure; };
	char getDirection() { return m_currDir; };
	void setPosition(int x, int y) { m_position.setXcoord(x); m_position.setYcoord(y); };
	void setXcoord(int x) { m_position.setXcoord(x); };
	void setYcoord(int y) { m_position.setYcoord(y); };
	void setDirection(char newDir) { m_currDir = newDir; };




};



