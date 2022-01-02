#pragma once
#include "Menu.h"
#include "Game.h"
#include "FileActions.h" //change this later to BoardFiles.h
#include "GameFiles.h"
#include "GameType.h"

class GameController
{

private:
	Menu m_Menu;
	GameMode m_GameType;

private:
	enum { GAME_LOGO = 1, WINNING_LOGO = 2, GOODBYE_LOGO = 3 };
	enum { ALL_FILES = '2', SPECIFIC_FILE = '1' };
	eUserChoice ActivateMenu(); //will not be used in load silent mode , THINK ABOUT TRANFERRING MENU METHODS TO MENU CLASS....
	void ChooseScreenOrVector(eUserChoice& userChoice);  
	void PlayUserDrivenGame(string& fileName, GameMode mode, Game& game, bool isSingleGame); // was "GameRun" before
	GameMode RequestGameMode();

	//User-driven game (save/interactive)
private:
	//tranfer functions below to ActivateInteractive or ActivateRecording method (?)
	void PrintLogo(int logo);	//will not be used in load silent mode
	void PrintInstructions();	//will not be used in load silent mode
	void PrintGoodbyeMessage(); //will not be used in load silent mode
	void PauseGame(Game& currentGame, bool issingleGame); //will not be used in load silent mode
	bool RequestColorMode(Game& game);
	//

public:
	// the three activate function below activates the different kinds of game
	void ActivateLoadGame() {};
	void ActivateRecordingGame();
	//
	void Run(GameType::eType type);
};



