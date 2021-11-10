#ifndef Board_h
#define Board_h


class Board
{
private:
	static const int HIGHT = 25;
	static const int WIDTH = 80;
	char board[WIDTH][HIGHT];


public:
	Board(); // build a function to init the board with the maze and the breadcrumbs
	void printBoard() {};
	char getPosition(const int x, const int y) { return board[x][y]; };
	
};
#endif /* Board_h */