#ifndef GAME_H
#define GAME_H

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "io_utils.h"
#include "eBoardObjects.h"
#include <iostream>

class Game
{
private:

	Ghost m_Speedy, m_Bashful;
	Pacman m_Pacman;
	Board m_Board;
	int m_score;
	int m_life;


public:
	Game() : m_Pacman(), m_Speedy(0, 0, eColor::Blue), m_Bashful(0, 0, eColor::Red), m_score(0), m_life(3) {};
	bool updateLife();
	void updateScore();
	void printBoard() {
		m_Board.printBoard();
		initView();
	} //transfer to cpp.
	void initView();
	void checkTunnel(const int Ycoord, const int Xcoord);
	void PacmanStepCheck(const int Ycoord, const int Xcoord);//checks the next step cell
	void pacmanMove(int Xcoord, int Ycoord);

};

#endif /*GAME_H*/

