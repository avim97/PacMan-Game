#pragma once
#include "Menu.h"
#include "Game.h"
#include "FileActions.h"



class GameController
{


private:
	enum { GameLogo = 1, WinnigLogo = 2, GoodbyeLogo = 3 };
	enum { AllFiles = '2', SpedificFile = '1' };
	eUserChoice ActivateMenu();
	void PrintLogo(int logo);
	void PrintInstructions();
	void printGoodbyeMessage();
	void ChooseScreenOrVector(eUserChoice& userChoice);
	bool ApplyUserColorsChoiceToGame(Game& game);
	void PauseGame(Game& currentGame, bool issingleGame);


public:
	void Run();
	GameMode GameModeChoice();
	void GameRun(string& fileName, GameMode mode, Game& game, bool isSingleGame);
};



