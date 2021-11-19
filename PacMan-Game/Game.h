#ifndef GAME_H
#define GAME_H

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "io_utils.h"
#include <iostream>


class Game
{
private:

	Ghost m_Ghost[2];
	Pacman m_Pacman;
	Board m_Board;
	int m_score;
	int m_life;
	bool gameOn;

public:
	Game() : m_Board(),m_Pacman(), m_Ghost{{36, 20, eColor::Blue},{36, 9, eColor::Red}}, m_score(0), m_life(3), gameOn(true){srand(time(NULL));};
	bool updateLife();
	int getLives() {return m_life;};
	bool updateScore();
	void printBoard() {m_Board.printBoard(); initView();}
	void initView();

	// ----------- PACMAN---------
	bool checkTunnel(const int yCoord, const int xCoord);
	bool PacmanStepCheck(const int yCoord, const int xCoord);//checks pacman's next step
	void crossTunnel(const int yCoord, const int xCoord);
	void moveObject(char nextDir);
	void eraseFood(const int yCoord, const int xCoord);
	void erasePacman(const int yCoord, const int xCoord);
	void printPacman(const int yCoord, const int xCoord);
	// --------------GHOST -----------
	void GhostStepCheck(const int yCoord, const int xCoord, int ghost); //checks ghost's next step
	void moveObject(int ghost);
	void eraseGhost(const int yCoord, const int xCoord);
	void printGhost(const int yCoord, const int xCoord, int ghost);

};

#endif /*GAME_H*/

