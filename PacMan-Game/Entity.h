#pragma once

#include <iostream>
#include "Direction.h"
#include "Position.h"
#include "Color.h"
#include "eBoardObjects.h"

class Entity {
Public:
	Position initPosition;
Private:
	cosnt char m_figure;
	char m_color;
	Position m_position;
	unsigned char m_currDir;
Public:
	Entity();

	//get functions
	const char GetFigure()const {return m_figure};
	Color GetColor(){ return m_color };
	Position GetPosition() { return m_position; };
	int GetXcoord() const { return m_position.getXcoord(); };
	int GetYcoord() const { return m_position.getYcoord(); };
	char GetDirection() { return m_currDir; };

	//set functions
	void SetPosition(int x, int y) { m_position.setXcoord(x); m_position.setYcoord(y); };
	void SetXcoord(int x) { m_position.setXcoord(x); };
	void SetYcoord(int y) { m_position.setYcoord(y); };
	void SetColor(Color::eColor color) { m_color.setColor(color); };
	void SetDirection(char newDir) { m_currDir = newDir; };

	// virtual 'move' function
	virtual void Move();         //to do
	virtual bool StepCheck();    //to do
};