#pragma once
#include "Game.h"

class InteractiveGame : public Game
{
protected:


public:
	InteractiveGame(string& boardPath, GameMode mode):
		Game(boardPath, mode)
	{};

	InteractiveGame(string& boardPath, GameMode mode, int lives, int score):
	Game(boardPath, mode, lives, score)
	{};
	void PauseGame();
};
