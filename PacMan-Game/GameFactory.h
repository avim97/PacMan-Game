#pragma once
#include "RecordingGame.h"
#include "InteractiveGame.h"
#include "LoadedGame.h"

class GameFactory
{
	Game* Create(string& boardPath, GameMode mode, int lives, int score, GameType::eType type);
};

