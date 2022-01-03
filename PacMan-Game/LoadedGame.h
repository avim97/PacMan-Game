#pragma once
#include "Game.h"

class LoadedGame: public Game
{
private:
	GameType::eType m_GameType;

public:
	LoadedGame(string& boardPath, GameMode mode, GameType::eType gType):
		Game(boardPath, mode),
		m_GameType(gType)
	{};

	LoadedGame(string& boardPath, GameMode mode, int lives, int score, GameType::eType gType) :
		Game(boardPath, mode, lives, score),
		m_GameType(gType)
	{};

	~LoadedGame() override {};
	virtual void PlayGame();
	virtual void initialGhostPos();
	virtual void initialPacmanPos();
	virtual void MovePacman(char nextDir);
	virtual bool PacmanStepCheck(const int yCoord, const int xCoord);
	virtual void InitializeFruitPosition();
	virtual void MoveGhost(int ghost, int& ghostsMoves);
	virtual bool GhostStepCheck(const int yCoord, const int xCoord, int ghost);
	virtual void MoveFruit();
	virtual bool FruitStepCheck(const int yCoord, const int xCoord);
	virtual bool CheckFruitIntersection(Position nextPosition, BoardObjects gameObject);
};

