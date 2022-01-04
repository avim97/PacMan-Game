#pragma once
#include "InteractiveGame.h"
#include "GameFiles.h"

class RecordingGame : public Game
{
private:
	GameFiles& m_GameFiles;

public:
	RecordingGame(string& boardPath, GameMode mode, GameFiles& GameFiles) :
		Game(boardPath, mode),
		m_GameFiles(GameFiles)
		
	{
		srand((unsigned int)time(nullptr));
		InitializeGhostsVector(m_Board.getGhostInitPos());
	};

	RecordingGame(string& boardPath, GameMode mode, int lives, int score, GameFiles& GameFiles) :
		Game(boardPath, mode, lives, score),
		m_GameFiles(GameFiles)
	{
		m_Pacman.UpdateLife(lives);
		InitializeGhostsVector(m_Board.getGhostInitPos());
		srand((unsigned int)time(nullptr));
	};
	void RecordSteps(bool &ghostsMoved, bool &fruitMoved);
	void UpdateResultFile(int& frameNumber);
	virtual void PlayGame();
	
};
