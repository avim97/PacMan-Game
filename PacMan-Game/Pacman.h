#pragma once


#include <iostream>
#include "Direction.h"
#include "Position.h"
#include "eColor.h"

using namespace std;


class Pacman
{
public:
	const Position initialPos = { 36, 14 };

private:

	const char m_figure;
	eColor m_color;
	Position m_position;
	char m_currDir;


public:
	Pacman() : m_figure('@'), m_color(eColor::Yellow), m_position(initialPos), m_currDir((char)Direction::eDirection::STAY) {};
	//void setColor() {}; //check
	int getXcoord() const { return m_position.getXcoord(); };
	int getYcoord() const { return m_position.getYcoord(); };
	const char getFigure() { return m_figure; };
	void setPosition(int x, int y) { m_position.setXcoord(x); m_position.setYcoord(y); };
	void setXcoord(int x) { m_position.setXcoord(x); };
	void setYcoord(int y) { m_position.setYcoord(y); };
	Position getPosition() { return m_position;};
	char getDirection() { return m_currDir; };
	void setDirection(char newDir) { m_currDir = newDir; };




};



