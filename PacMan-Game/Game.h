#pragma once

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include <vector>
#include "eGameStatus.h"
#include <cmath>

using std::vector;
typedef vector<Ghost*> GhostsVector;


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
	Game(string &boardPath) : 
		m_Board(boardPath),
		m_Pacman(),
		m_Fruit(m_Board.GetRandomPosition()),
		m_gameStatus(eGameStatus::RUNNING),
		m_IsColorful(true) 
	{
		m_Pacman.SetInitialPosition(m_Board.getPacmanInitPos());
		m_Pacman.SetPosition(m_Board.getPacmanInitPos());

		srand((unsigned int)time(nullptr)); InitializeGhostsVector(m_Board.getGhostInitPos());
	};
	~Game();
	void printBoard() { m_Board.printBoard(); initView();}
	void initView();
	void initialGhostPos();
	void initialPacmanPos();
	eGameStatus getGameStatus() { return m_gameStatus; };
	bool CheckBoardEdge(int xCoord, int yCoord);

	//------------- COLORS -------------
	void setColorStyle(bool isColorful); 
	bool getColorStyle() { return m_IsColorful; };
	void SetDefaultColor();

	// ----------- PACMAN---------
	bool CheckTunnel(const int yCoord, const int xCoord); //## - MOVED TO GAMECREATURE CLASS
	bool PacmanStepCheck(const int yCoord, const int xCoord); //##
	void CrossTunnel(const int yCoord, const int xCoord); //## - MOVED IT PACMAN CLASS
	void MovePacman(char nextDir); 
	void eraseFood(const int yCoord, const int xCoord); //## - MOVED TO GAMECREATURE CLASS
	bool CheckPacmanIntersection(const int yCoord, const int xCoord);

	// -------------- GHOST ----------
	void InitializeGhostsVector(const vector<Position>& ghostsMoves);
	void InitialFruitPosition();
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

};



