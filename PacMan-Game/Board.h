#pragma once
#include "eBoardObjects.h"
#include "Color.h"
#include "Position.h"
#include <vector>

using std::vector;
typedef vector<vector<char>> gameBoard;


class Board
{
private:
	static const int HEIGHT = 25;
	static const int WIDTH = 80;
	unsigned int totalBreadcrumbs = 0;
	Position pacmanInitialPos = { 0,0 };
	vector<Position> ghostInitialPos={};
	Position fruitInitialPos = { 0,0 };
	gameBoard board;
	Color m_wallColor;
	Color m_breadcrumbColor;
	


public:
	Board() :m_wallColor(Color::eColor::DEFAULT), m_breadcrumbColor(Color::eColor::BOLD_GREEN) { initBoard(pacmanInitialPos,ghostInitialPos, fruitInitialPos); };
	void initBoard(Position& pacmanInitialPos, vector<Position>& ghostInitialPos, Position& fruitInitialPos);
	void printBoard();
	int getWidth() { return WIDTH; };
	int getHeight() { return HEIGHT; };
	int getMaxScore() { return totalBreadcrumbs; };
	Color  getWallColor() { return m_wallColor; };
	Color  getBreadcrumbColor() { return m_breadcrumbColor; };
	char getCellValue(const int x, const int y) const { return board[y][x]; };
	char getCellValue(const Position& position) const { return board[position.getYcoord()][position.getXcoord()]; }; //check
	void setChar(const int xCoord, const int yCoord, char ch) { board[yCoord][xCoord] = ch; };
	void setWallColor(Color::eColor color) { m_wallColor.setColor(color); };
	void setBreadcrumColor(Color::eColor color) { m_breadcrumbColor.setColor(color); };

};


