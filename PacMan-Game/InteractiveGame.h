#pragma once
#include "Game.h"

class InteractiveGame : public Game
{

public:
	InteractiveGame(string& boardPath, GameMode mode):
		Game(boardPath, mode)
	{
		srand((unsigned int)time(nullptr));
		InitializeGhostsVector(m_Board.getGhostInitPos());
	};

	InteractiveGame(string& boardPath, GameMode mode, int lives, int score):
	Game(boardPath, mode, lives, score)
	{
		m_Pacman.UpdateLife(lives);
		InitializeGhostsVector(m_Board.getGhostInitPos());
		srand((unsigned int)time(nullptr));
	};
	void PauseGame();
};
