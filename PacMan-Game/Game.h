#pragma once

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "eGameStatus.h"
#include "io_utils.h"



class Game
{
private:

	Board m_Board;
	Ghost m_Ghost[2];
	Pacman m_Pacman;
	eGameStatus m_gameStatus;
	int m_score;
	int m_life;
	bool m_isColorful;

public:
	Game() : m_Board(), m_Ghost{{36, 20, Color::eColor::BLUE},{36, 9, Color::eColor::RED}}, m_Pacman(), m_gameStatus(eGameStatus::RUNNING), m_score(0), m_life(3) ,m_isColorful(true){srand((unsigned int)time(nullptr));};
	bool updateLife();
	int getLives() {return m_life;}
	int getScore() {return m_score;}
	bool updateScore();
	void printBoard() { m_Board.printBoard(); initView();}
	void initView();
	void initialGhostPos(int ghostInd);
	void initialPacmanPos();
	eGameStatus getGameStatus() { return m_gameStatus; };

	//------------- COLORS -------------
	void setColorStyle(bool isColorful) { m_isColorful = isColorful; };
	bool getColorStyle() { return m_isColorful; };
	void setDefaultColor();

	// ----------- PACMAN---------
	bool checkTunnel(const int yCoord, const int xCoord);
	bool PacmanStepCheck(const int yCoord, const int xCoord);
	void crossTunnel(const int yCoord, const int xCoord);
	void movePacman(char nextDir);
	void eraseFood(const int yCoord, const int xCoord);
	void erasePacman(const int yCoord, const int xCoord);
	void printPacman(const int yCoord, const int xCoord);
	bool isValidMove(char move);
	bool checkGhostIntersection();

	// --------------GHOST ----------
	void GhostStepCheck(const int yCoord, const int xCoord, int ghost); 
	void moveGhost(int ghost);
	void eraseGhost(const int yCoord, const int xCoord);
	void printGhost(const int yCoord, const int xCoord, int ghost);

	//---------- Playing the game ---------
	void PlayGame();
	void PauseGame();
	void showPlayerStatus();
	void userWon();
	void userLost();

};



