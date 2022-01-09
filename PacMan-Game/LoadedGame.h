#pragma once

#include "Game.h"
#include "GameFiles.h"


class LoadedGame : public Game
{
private:
	bool m_GameLoadSucceded;
	string m_GameResult ;
	GameType::eType m_GameType;
	GameFiles& m_GameFiles;
	int m_TimePoint;

private:
	enum { MIN_INDEX = 0, MAX_INDEX = 3};
	
	inline int num_char_to_int(char num) const {
		return num - '0';
	}

	inline int num_int_to_char(char num) const {
		return num + '0';
	}

public: 
	LoadedGame(string& boardPath, GameMode mode, GameType::eType gType, GameFiles& _GameFiles) :
		Game(boardPath, mode),
		m_GameType(gType),
		m_GameFiles(_GameFiles),
		m_GameLoadSucceded(true),
		m_TimePoint(0)
	{
		m_GameResult = NoResult;
	};

	LoadedGame(string& boardPath, GameMode mode, int lives, int score, GameType::eType gType, GameFiles& _GameFiles) :
		Game(boardPath, mode, lives, score),
		m_GameType(gType),
		m_GameFiles(_GameFiles),
		m_GameLoadSucceded(true),
		m_TimePoint(0)
		
	{
		m_GameResult = NoResult;
	};

	~LoadedGame() override {};

public:
	virtual void PlayGame();
	virtual void initialGhostPos();
	virtual void initialPacmanPos();
	virtual void MovePacman(char nextDir);
	virtual bool PacmanStepCheck(const int yCoord, const int xCoord);
	virtual void InitializeFruitPosition();
	virtual void MoveGhost(int ghost, char nextDir);
	virtual bool GhostStepCheck(const int yCoord, const int xCoord, int ghost);
	virtual void MoveFruit(char nextDir);
	virtual bool FruitStepCheck(const int yCoord, const int xCoord);
	virtual bool CheckFruitIntersection(Position nextPosition, BoardObjects gameObject);

public:
	void GetColorStatus();
	void ApplyGameFrame(stringstream& currentFrame, bool& loadSucceded);
	void GameCreatureValidator(BoardObjects& creature, string& readCreature) const;
	BoardObjects GetCreature(string& creature, stringstream& currentFrame) const;
	bool GetAction(string& action, stringstream& currentFrame) const;
	bool GhostNumberValidator(string& inputIndex, string& currentGhost) const;
	bool GetGhostNumber(string& creature, stringstream& currentFrame) const;
	bool GetAction(BoardObjects& game_creature, string& creature_data, string& nextAction, stringstream& currentFrame) const;
	void GetDirection(BoardObjects& creature, string& creature_data ,string& nextAction, stringstream& currentFrame) const;
	bool ValidateNextDirection(BoardObjects& creature, string& creature_data, string& nextAction) const;
	void GetFruitAction(string& creature_data, string& nextAction, stringstream& currentFrame) const;
	bool VerifyFruitDirection(string& nextAction) const;
	bool VerifyFruitDeActivation(string& nextAction) const;
	bool VerifyFruitInitialization(string& creatureData, string& nextAction) const;
	bool VerifyFruitValue(string& actionData) const;
	bool VerifyInitialPosition(string& actionData) const;
	bool PositionValidator(string& xCoord, string& yCoord) const;
	bool DirectionValidator(int& xCoord, int& yCoord, string& nextDirection) const;
	void ExecuteAction(BoardObjects& creatue, string& creatureData, string& action);
	void ExecuteFruitAction(string& action, string& actionData);
	void DeactivateFruit();
	void ActivateFruit(string& activation_data);
	void VerifyGameResult();
	void VerifyGameResult(string& result);
};
