#pragma once

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "GameType.h" //tranfer this later to Game class when will used inheritence ....
#include "eGameStatus.h"
#include <vector>
#include <cmath>


using std::vector;
typedef vector<Ghost*> GhostsVector;


class Game
{

private:
	bool m_IsColorful;
	int m_TotalScore;

protected:
	enum { ESC = 27 };

protected:
	GameMode m_GameMode;
	eGameStatus m_gameStatus;
	Board m_Board;
	GhostsVector m_Ghosts;
	Pacman m_Pacman;
	Fruit m_Fruit;
	

public:
	Game(string& boardPath, GameMode mode) :
		m_Board(boardPath),
		m_Pacman(m_Board.getPacmanInitPos()),
		m_Fruit(m_Board.GetRandomPosition()),
		m_gameStatus(eGameStatus::RUNNING),
		m_IsColorful(true),
		m_TotalScore(0),
		m_GameMode(mode)
	{
		InitializeGhostsVector(m_Board.getGhostInitPos());
		srand((unsigned int)time(nullptr));
	};

	Game(string& boardPath, GameMode mode, int lives, int score) :
		m_Board(boardPath),
		m_Pacman(m_Board.getPacmanInitPos()),
		m_Fruit(m_Board.GetRandomPosition()),
		m_gameStatus(eGameStatus::RUNNING),
		m_IsColorful(true),
		m_TotalScore(score),
		m_GameMode(mode)
	{
		m_Pacman.UpdateLife(lives);
		InitializeGhostsVector(m_Board.getGhostInitPos());
		srand((unsigned int)time(nullptr));
	};


	virtual ~Game();
	void PrintBoard() { m_Board.PrintBoard(); } 
	void PrintBoard(bool wasPaused);


	void initView(); 
	virtual void initialGhostPos(); 
	virtual void initialPacmanPos(); 
	eGameStatus getGameStatus() { return m_gameStatus; }; 
	bool CheckBoardEdge(int xCoord, int yCoord)const; 

	//------------- COLORS -------------
	void SetColorStyle(bool isColorful); 
	void SetDefaultColor(); 
	bool GetColorStyle() { return m_IsColorful; }; //DONE

	// ----------- PACMAN---------
	virtual void MovePacman(char nextDir); //DONE
	bool CheckTunnel(const int yCoord, const int xCoord); //DONE
	bool PacmanStepCheck(const int yCoord, const int xCoord); //DONE
	void CrossTunnel(const int yCoord, const int xCoord); //DONE
	void EraseFood(const int yCoord, const int xCoord); //DONE
	bool CheckPacmanIntersection(const int yCoord, const int xCoord); //DONE


	// -------------- GHOST ----------
	virtual void MoveGhost(int ghost, int& ghostsMoves); //DONE
	virtual bool GhostStepCheck(const int yCoord, const int xCoord, int ghost); //DONE
	bool CheckGhostIntersection(int ghostInd, int yCoord, int xCoord, BoardObjects gameObject); //DONE
	void LoadGhostsPositions(PositionsVector& positions, GhostsVector ghosts, int currentGhost); //DONE
	bool DirectionValidator(Direction::eDirection& lastDirection, int ghost, int& ghostMoves); //MOVE TO SAVE AND INTERACTIVE MODE !!
	void InitializeGhostsVector(const vector<Position>& ghostsMoves); //DONE

	//------------FRUIT--------------
	virtual void InitializeFruitPosition();
	virtual void MoveFruit(); //DONE
	virtual bool FruitStepCheck(const int yCoord, const int xCoord); //DONE
	virtual bool CheckFruitIntersection(Position nextPosition, BoardObjects gameObject); //DONE


	//---------- Playing the game ---------
	virtual void PlayGame(); //DONE
	static void userWon(bool color); //DONE
	static void userLost(bool color); //DONE
	int GetTotalScore(); //DONE
	int GetCurrentLives() const { return m_Pacman.GetCurrentLives(); } //DONE
	void SetGameStatus(eGameStatus status) { this->m_gameStatus = status; } //DONE


};



