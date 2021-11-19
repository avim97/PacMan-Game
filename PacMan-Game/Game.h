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

	Ghost m_Ghost[2];
	Pacman m_Pacman;
	Board m_Board;
	int m_score;
	int m_life;


public:
	Game() : m_Pacman(), m_Ghost{{36, 20, eColor::Blue},{36, 9, eColor::Red}}, m_score(0), m_life(3) {srand(time(NULL));};
	bool updateLife();
	void updateScore();
	void printBoard() {m_Board.printBoard(); initView();}
	void initView();
	void checkTunnel(const int Ycoord, const int Xcoord);
	void PacmanStepCheck(const int Ycoord, const int Xcoord);//checks pacman's next step
	void moveObject(char nextDir);
	void GhostStepCheck(const int Ycoord, const int Xcoord); //checks ghost's next step
	void moveObject(int ghost);
};

#endif /*GAME_H*/

