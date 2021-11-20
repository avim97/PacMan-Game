#pragma once
#include "eBoardObjects.h"




class Board
{

private:
	static const int HEIGHT = 25;
	static const int WIDTH = 80;
	int totalBreadcrumbs = 0;
	char board[HEIGHT][WIDTH];


public:
	Board();
	void printBoard();
	char getPosition(const int x, const int y) { return board[x][y]; };
	int getWidth() { return WIDTH; };
	int getHeight() { return HEIGHT; };
	int getMaxScore() { return totalBreadcrumbs; };
	void setChar(const int xCoord, const int yCoord, char ch) { board[xCoord][yCoord] = ch; };
};


