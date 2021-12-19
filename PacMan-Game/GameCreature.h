#pragma once
#include <iostream>
#include "Direction.h"
#include "Position.h"
#include "Color.h"
#include "eBoardObjects.h"
#include "Board.h"
#include <vector>

using std::cout;
using std::endl;

class GameCreature
{
public:
	
private:
	char m_figure;
	Color m_color;
	Position m_initialPosition;
	Position m_currentPosition;
	unsigned char m_currDir;
public:
	GameCreature(const char figure, Color::eColor color, Position _initalPosition, unsigned char dir) : 
		m_figure(figure), 
		m_color(color), 
		m_initialPosition(_initalPosition),
		m_currentPosition(_initalPosition), 
		m_currDir(dir) 
	{};


	//get functions
	const char GetFigure() const { return m_figure; };
	Color GetColor() const { return m_color; };
	Position const&  GetPosition() const { return m_currentPosition; };
	int GetXcoord() const { return m_currentPosition.getXcoord(); };
	int GetYcoord() const { return m_currentPosition.getYcoord(); };
	char GetCurrentDirection() const { return m_currDir; };
	Position GetInitialPosition()const { return m_initialPosition; };

	//set functions
	void SetPosition(const int x, const int y) { m_currentPosition.setXcoord(x); m_currentPosition.setYcoord(y); };
	void SetPosition(Position position) { m_currentPosition = position; };
	void SetInitialPosition(Position position) { m_initialPosition = position; };
	void SetXcoord(const int x) { m_currentPosition.setXcoord(x); };
	void SetYcoord(const int y) { m_currentPosition.setYcoord(y); };
	void SetFigure(const char figure) { m_figure = figure; };
	void SetColor(Color::eColor color) { m_color.setColor(color); };
	void SetDirection(const char newDir) { m_currDir = newDir; };
	void ResetCurrentPosition() { m_currentPosition = m_initialPosition; };

	//i_o functions
	void Move() const;
	void Move(const Position _position) const;
	void Draw() const { cout << m_figure; };
	virtual void Erase(const int yCoord, const int xCoord, Board& board) const = 0;
	void EraseFood(const int yCoord, const int xCoord, Board& board);

	
};

