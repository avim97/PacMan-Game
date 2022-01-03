#pragma once
#include "RecordingGame.h"
#include "InteractiveGame.h"
#include "LoadedGame.h"

class GameFactory
{
public:
	Game* Create(string& boardPath, GameMode mode, GameType::eType type);
	Game* Create(string& boardPath, GameMode mode, int lives, int score, GameType::eType type);
};

