#ifndef Board_h
#define Board_h
#include "eBoardObjects.h"

class Board
{
private:
	static const int HEIGHT = 25;
	static const int WIDTH = 80;
	int totalBreadcrumbs = 0;
	char board[HEIGHT][WIDTH];


public:
	Board(); // build a function to init the board with the maze and the breadcrumbs
	void printBoard();
	char getPosition(const int x, const int y) { return board[x][y]; };
	int getWidth() { return WIDTH; };
	int getHeight() { return HEIGHT; };
	int getMaxScore() { return totalBreadcrumbs; };
};
#endif /* Board_h */