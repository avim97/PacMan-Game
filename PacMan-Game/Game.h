#pragma once

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include <vector>
#include "eGameStatus.h"

using std::vector;
typedef vector<Ghost> GhostsVector;



class Game
{
private:

	Board m_Board;
	GhostsVector m_Ghosts;
	Pacman m_Pacman;
	eGameStatus m_gameStatus;
	int m_score;
	//int m_life;
	bool m_isColorful;

public:
	Game() : 
		m_Board(),
		m_Pacman(),
		m_gameStatus(eGameStatus::RUNNING),
		m_score(0), 
		/*m_life(3)*/ 
		m_isColorful(true) 
	{
		srand((unsigned int)time(nullptr)); InitializeGhosts(4);
	};
	//bool updateLife(); // ##
	//int getLives() {return m_life;}
	//int getScore() {return m_score;}
	//bool updateScore();
	void printBoard() { m_Board.printBoard(); initView();}
	void initView();
	void initialGhostPos();
	void initialPacmanPos();
	eGameStatus getGameStatus() { return m_gameStatus; };

	//------------- COLORS -------------
	void setColorStyle(bool isColorful); 
	bool getColorStyle() { return m_isColorful; };
	void setDefaultColor();

	// ----------- PACMAN---------
	bool checkTunnel(const int yCoord, const int xCoord); //## - MOVED TO GAMECREATURE CLASS
	bool PacmanStepCheck(const int yCoord, const int xCoord); //##
	void crossTunnel(const int yCoord, const int xCoord); //## - MOVED TI PACMAN CLASS
	void movePacman(char nextDir); 
	void eraseFood(const int yCoord, const int xCoord); //## - MOVED TO GAMECREATURE CLASS
	//void erasePacman(const int yCoord, const int xCoord); // ## 
	//void printPacman(const int yCoord, const int xCoord); // ## - MOVED TO GAMECREATURE CLASS
	//bool isValidMove(char move);   // ## - MOVED TO DIRECTION CLASS
	bool CheckPacmanIntersection();
// ##

	// -------------- GHOST ----------
	void GhostStepCheck(const int yCoord, const int xCoord, int ghost); 
	void moveGhost(int ghost);
	bool checkGhostIntersection(int GhostIndex);
	void InitializeGhosts(const int& ghostsNumber);
	//void eraseGhost(const int yCoord, const int xCoord);
	//void printGhost(const int yCoord, const int xCoord, int ghost);

	//---------- Playing the game ---------
	void PlayGame();
	void PauseGame();
	void showPlayerStatus();
	void userWon();
	void userLost();


	//Updated functions for inheritence
	//void MoveCreature(char nextDir, BoardObjects object);


};



