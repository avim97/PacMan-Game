#include "GameFactory.h"

Game* GameFactory::Create(string& boardPath, GameMode mode, GameType::eType type, GameFiles& fileService)
{
	switch (type)
	{
	case GameType::eType::SAVE:
			return new RecordingGame(boardPath, mode, fileService);
			break;

	case GameType::eType::LOAD:
		return new LoadedGame(boardPath, mode, GameType::eType::LOAD, fileService);
		break;

	case GameType::eType::SILENT_LOAD:
		return new LoadedGame(boardPath, mode, GameType::eType::SILENT_LOAD, fileService);
		break;

	default:
		return new InteractiveGame(boardPath, mode);
		break;
	}
}

Game* GameFactory::Create(string& boardPath, GameMode mode, int lives, int score, GameType::eType type, GameFiles& fileService)
{
	switch (type)
	{
	case GameType::eType::SAVE:
		return new RecordingGame(boardPath, mode, lives, score, fileService);
		break;

	case GameType::eType::LOAD:
		return new LoadedGame(boardPath, mode, lives, score,GameType::eType::LOAD, fileService);
		break;

	case GameType::eType::SILENT_LOAD:
		return new LoadedGame(boardPath, mode, lives, score,GameType::eType::SILENT_LOAD, fileService);
		break;

	default:
		return new InteractiveGame(boardPath, mode, lives, score);
		break;
	}
}

