#pragma once

#include "Menu.h"
#include "GameFiles.h"
#include "BoardFiles.h" //?
#include "GameType.h"
#include "GameFactory.h"
#include "InteractiveGame.h"
#include "RecordingGame.h"
#include "LoadedGame.h"

using std::cout;

class GameController
{

private:
	Menu m_Menu;
	GameMode m_GameMode;
	GameType::eType m_GameType;
	GameFiles m_GameFilesService;
	BoardFiles m_BoardFilesService;
	Game* m_Game;
	GameFactory m_Factory;

private:
	enum { GAME_LOGO = 1, WINNING_LOGO = 2, GOODBYE_LOGO = 3 };
	enum { ALL_FILES = '2', SPECIFIC_FILE = '1' };

	//User-Driven game functions (save/interactive)
private:
	GameMode RequestGameMode();
	void PrintLogo(int logo);	//will not be used in load silent mode
	void PrintInstructions();	//will not be used in load silent mode
	void PrintGoodbyeMessage(); //will not be used in load silent mode
	void PauseGame(Game* currentGame, bool issingleGame); //will not be used in load silent mode
	bool RequestColorMode(Game* game);
	void PlayUserDrivenGame(string& fileName, Game* game, bool isSingleGame); // was "GameRun" before
	void CreateNewUserDrivenGame(eUserChoice& userChoice);

public:
	// the three activate function below activates the different kinds of game
	~GameController() { delete m_Game; };
	void ActivateMachineDrivenGame();
	void ActivateUserDrivenGame();
	void Run(GameType::eType type);
};



