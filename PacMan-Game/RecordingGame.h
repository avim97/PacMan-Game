#pragma once
#include "InteractiveGame.h"
#include "GameFiles.h"


class RecordingGame : public Game
{

private:
	GameFiles& m_GameFiles;

public:
	RecordingGame(string& boardPath, GameMode mode, int lives, int score, GameFiles& GameFiles) :
		Game(boardPath, mode, lives, score),
		m_GameFiles(GameFiles)
	{};

public:
	virtual void PlayGame();

public:
	void RecordSteps(bool &ghostsMoved, bool &fruitMoved);
	void UpdateResultFile(int& frameNumber);
	void UpdateResultFile(int& frameNumber, eGameStatus result);
	void CloseRecordingFiles() { m_GameFiles.CloseFiles(); };
	void OpenRecordingFiles() { m_GameFiles.CreateRecordingFiles(); };
	void PauseRecording();
	
};
