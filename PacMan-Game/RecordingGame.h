#pragma once
#include "InteractiveGame.h"

class RecordingGame : public InteractiveGame
{
public:
	RecordingGame(string& boardPath, GameMode mode) :
		InteractiveGame(boardPath, mode)
	{
		srand((unsigned int)time(nullptr));
	};

	RecordingGame(string& boardPath, GameMode mode, int lives, int score) :
		InteractiveGame(boardPath, mode, lives, score)
	{
		srand((unsigned int)time(nullptr));
	};
	void PauseGame();
};
