#pragma once

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
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
	Fruit m_Fruit;
	eGameStatus m_gameStatus;
	bool m_IsColorful;

public:
	Game(Position position) : //after merging get the initial position for the pacman and the fruit from the board member
		m_Board(),
		m_Pacman(),
		m_Fruit(m_Board.GetRandomPosition()),
		m_gameStatus(eGameStatus::RUNNING),
		m_IsColorful(true) 
	{
		srand((unsigned int)time(nullptr)); InitializeGhosts(4);
	};
	void printBoard() { m_Board.printBoard(); initView();}
	void initView();
	void initialGhostPos();
	void initialPacmanPos();
	eGameStatus getGameStatus() { return m_gameStatus; };


	//------------- COLORS -------------
	void setColorStyle(bool isColorful); 
	bool getColorStyle() { return m_IsColorful; };
	void setDefaultColor();

	// ----------- PACMAN---------

	bool checkTunnel(const int yCoord, const int xCoord); //## - MOVED TO GAMECREATURE CLASS
	bool PacmanStepCheck(const int yCoord, const int xCoord); //##
	void crossTunnel(const int yCoord, const int xCoord); //## - MOVED IT PACMAN CLASS
	void MovePacman(char nextDir); 
	void eraseFood(const int yCoord, const int xCoord); //## - MOVED TO GAMECREATURE CLASS
	bool CheckPacmanIntersection(const int yCoord, const int xCoord);



	// -------------- GHOST ----------
	void InitializeGhosts(const int& ghostsNumber);
	void MoveGhost(int ghost);
	bool GhostStepCheck(const int yCoord, const int xCoord, int ghost); 
	bool CheckGhostIntersection(int ghostInd, int yCoord, int xCoord, BoardObjects gameObject);



	//------------FRUIT--------------
	void MoveFruit();
	bool FruitStepCheck(const int yCoord, const int xCoord);
	bool CheckFruitIntersection(Position nextPosition, BoardObjects gameObject);
	//---------- Playing the game ---------
	void PlayGame();
	void PauseGame();
	void ShowPlayerStatus();
	void userWon();
	void userLost();


	//Updated functions for inheritence
	//void MoveCreature(char nextDir, BoardObjects object);


};



