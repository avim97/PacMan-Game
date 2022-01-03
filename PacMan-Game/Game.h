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
	eGameStatus m_gameStatus;
	bool m_IsColorful;
	int m_TotalScore;
	GameMode m_GameMode;

protected:
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
		/*srand((unsigned int)time(nullptr));*/ InitializeGhostsVector(m_Board.getGhostInitPos());
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
		/*srand((unsigned int)time(nullptr));*/ InitializeGhostsVector(m_Board.getGhostInitPos());
	};


	virtual ~Game();
	void PrintBoard() { m_Board.PrintBoard(); } //DONE
	void PrintBoard(bool wasPaused) { m_Board.PrintBoard(wasPaused); gotoxy(m_Pacman.GetXcoord(), m_Pacman.GetYcoord()); m_Pacman.Draw(); } //DONE


	void initView(); //DONE
	virtual void initialGhostPos(); //DONE
	virtual void initialPacmanPos(); //DONE
	eGameStatus getGameStatus() { return m_gameStatus; }; //DONE
	bool CheckBoardEdge(int xCoord, int yCoord); //DONE

	//------------- COLORS -------------
	void SetColorStyle(bool isColorful); //DONE
	void SetDefaultColor(); //DONE
	bool GetColorStyle() { return m_IsColorful; }; //DONE

	// ----------- PACMAN---------
	bool CheckTunnel(const int yCoord, const int xCoord); //DONE
	bool PacmanStepCheck(const int yCoord, const int xCoord); //DONE
	void CrossTunnel(const int yCoord, const int xCoord); //DONE
	virtual void MovePacman(char nextDir); //DONE
	void EraseFood(const int yCoord, const int xCoord); //DONE
	bool CheckPacmanIntersection(const int yCoord, const int xCoord); //DONE


	// -------------- GHOST ----------
	virtual void InitializeFruitPosition(); //DONE
	void InitializeGhostsVector(const vector<Position>& ghostsMoves); //DONE
	virtual void MoveGhost(int ghost, int& ghostsMoves); //DONE
	virtual bool GhostStepCheck(const int yCoord, const int xCoord, int ghost); //DONE
	bool CheckGhostIntersection(int ghostInd, int yCoord, int xCoord, BoardObjects gameObject); //DONE
	void LoadGhostsPositions(PositionsVector& positions, GhostsVector ghosts, int currentGhost); //DONE
	bool DirectionValidator(Direction::eDirection& lastDirection, int ghost, int& ghostMoves); //MOVE TO SAVE AND INTERACTIVE MODE !!

	//------------FRUIT--------------
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



