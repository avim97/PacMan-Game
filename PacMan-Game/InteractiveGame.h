#pragma once
#include "Game.h"

class InteractiveGame : public Game
{

public:
	InteractiveGame(string& boardPath, GameMode mode):
		Game(boardPath, mode)
	{
		srand((unsigned int)time(nullptr));
	};

	InteractiveGame(string& boardPath, GameMode mode, int lives, int score):
	Game(boardPath, mode, lives, score)
	{
		srand((unsigned int)time(nullptr));
	};
	void PauseGame();
};
