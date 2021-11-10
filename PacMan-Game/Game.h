#ifndef GAME_H
#define GAME_H

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "io_utils.h"


class Game
{
private:
	Ghost m_Speedy, m_Bashful;
	Pacman m_Pacman;
	Board m_Board;
	int m_score;
	int m_life;

public:
	Game() : m_Pacman(), m_Speedy(0, 0), m_Bashful(0, 0) , m_score(0), m_life(3){};
	bool updateLife() {};
	void printBoard() {m_Board.printBoard();};
	void initView()
	{
		int xCoord, yCoord;
		gotoxy(m_Pacman.getXcoord(), m_Pacman.getYcoord());
		cout << " ";
		xCoord = m_Pacman.initialPos.getXcoord();
		yCoord = m_Pacman.initialPos.getYcoord();
		gotoxy(xCoord,yCoord);
		m_Pacman.setPosition(xCoord, yCoord);

		// check on the board for the ghost if there was breadcrumb from initializing their position to the initial positioin and then init their position.

	};
};	




#endif /*GAME_H*/

