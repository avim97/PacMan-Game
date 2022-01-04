#pragma once
#include "InteractiveGame.h"

class RecordingGame : public Game
{
public:
	RecordingGame(string& boardPath, GameMode mode) :
		Game(boardPath, mode)
	{
		srand((unsigned int)time(nullptr));
	};

	RecordingGame(string& boardPath, GameMode mode, int lives, int score) :
		Game(boardPath, mode, lives, score)
	{
		srand((unsigned int)time(nullptr));
	};
	void RecordSteps(bool ghostsMoved, bool fruitMoved);
	virtual void PlayGame();
};
