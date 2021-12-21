#pragma once
#include "Menu.h"
#include "Game.h"
#include "FileActions.h"



class GameController
{


private:
	enum {GameLogo = 1, WinnigLogo = 2, GoodbyeLogo = 3};
	enum {AllFiles = '2', SpedificFile='1' };
	eUserChoice activateMenu();
	void printLogo(int logo);
	
	void printInstructions();
	void printGoodbyeMessage();
	eUserChoice ChooseScreenOrVector();
	bool ApplyUserColorsChoiceToGame(Game& game);

	

	
public:
	void Run();

};



