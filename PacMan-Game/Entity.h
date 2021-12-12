#pragma once

#include <iostream>
#include "Direction.h"
#include "Position.h"
#include "Color.h"
#include "eBoardObjects.h"

class Entity {
public:
	Position initPosition;
private:
	const char m_figure;
	Color m_color;
	Position m_position;
	unsigned char m_currDir;
public:
	Entity(const char figure, Color color, const int x, const int y, unsigned char dir): m_figure(figure), m_color(color), m_position(x,y),m_currDir(dir) {};

	//get functions
	const char GetFigure()const const { return m_figure; };
	Color GetColor() const { return m_color; };
	Position GetPosition() const { return m_position; };
	int GetXcoord() const { return m_position.getXcoord(); };
	int GetYcoord() const { return m_position.getYcoord(); };
	char GetDirection() const { return m_currDir; };

	//set functions
	void SetPosition(int x, int y) { m_position.setXcoord(x); m_position.setYcoord(y); };
	void SetXcoord(int x) { m_position.setXcoord(x); };
	void SetYcoord(int y) { m_position.setYcoord(y); };
	void SetColor(Color::eColor color) { m_color.setColor(color); };
	void SetDirection(char newDir) { m_currDir = newDir; };

	// virtual 'move' function
	virtual void Move() = 0;         //to do
	virtual bool StepCheck() = 0;    //to do
};