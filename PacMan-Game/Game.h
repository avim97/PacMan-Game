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
	enum BoardObjects
	{
		FOOD = 249, SPACE = ' '
	};
	Ghost m_Speedy, m_Bashful;
	Pacman m_Pacman;
	Board m_Board;
	int m_score;
	int m_maxScore;
	int m_life;


public:
	Game() : m_Pacman(), m_Speedy(0, 0, eColor::Blue), m_Bashful(0, 0, eColor::Red), m_score(0), m_maxScore(0), m_life(3) {};
	bool updateLife();
	void updateScore();
	void calcMaxScore();
	void printBoard() {
		m_Board.printBoard();
		void initView();

	}
	void initView();

};

#endif /*GAME_H*/

