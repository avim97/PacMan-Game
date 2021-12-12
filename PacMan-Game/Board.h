#pragma once
#include "eBoardObjects.h"
#include "Color.h"



class Board
{

private:
	static const int HEIGHT = 25;
	static const int WIDTH = 80;
	unsigned int totalBreadcrumbs = 0;
	char board[HEIGHT][WIDTH];
	Color m_wallColor ;
	Color m_breadcrumbColor ;


public:
	Board() :m_wallColor(Color::eColor::DEFAULT), m_breadcrumbColor(Color::eColor::BOLD_GREEN) { initBoard(); };
	void initBoard();
	void createTopTunnel();
	void createBottomtunnel();
	void printBoard();
	char getPosition(const int x, const int y) { return board[y][x]; };
	int getWidth() { return WIDTH; };
	int getHeight() { return HEIGHT; };
	int getMaxScore() { return totalBreadcrumbs; };
	void setChar(const int xCoord, const int yCoord, char ch) { board[yCoord][xCoord] = ch; };
	void setWallColor(Color::eColor color) { m_wallColor.setColor(color); };
	void setBreadcrumColor(Color::eColor color) { m_breadcrumbColor.setColor(color); };
	Color  getWallColor() { return m_wallColor; };
	Color  getBreadcrumbColor(){ return m_breadcrumbColor; };
};


