#include "GameFactory.h"

Game* GameFactory::Create(string& boardPath, GameMode mode, GameType::eType type)
{
	switch (type)
	{
	case GameType::eType::SAVE:
			return new InteractiveGame(boardPath, mode);
			break;

	case GameType::eType::LOAD:
		return new LoadedGame(boardPath, mode, GameType::eType::LOAD);
		break;

	case GameType::eType::SILENT_LOAD:
		return new LoadedGame(boardPath, mode, GameType::eType::SILENT_LOAD);
		break;

	default:
		return new InteractiveGame(boardPath, mode);
		break;
	}
}

Game* GameFactory::Create(string& boardPath, GameMode mode, int lives, int score, GameType::eType type)
{
	switch (type)
	{
	case GameType::eType::SAVE:
		return new InteractiveGame(boardPath, mode, lives, score);
		break;

	case GameType::eType::LOAD:
		return new LoadedGame(boardPath, mode, lives, score,GameType::eType::LOAD);
		break;

	case GameType::eType::SILENT_LOAD:
		return new LoadedGame(boardPath, mode, lives, score,GameType::eType::SILENT_LOAD);
		break;

	default:
		return new InteractiveGame(boardPath, mode, lives, score);
		break;
	}
}

