#pragma once
#include "Menu.h"
#include "Game.h"



class GameController
{


private:
	enum {GameLogo = 1, WinnigLogo = 2, GoodbyeLogo = 3};
	eUserChoice activateMenu();
	void printLogo(int logo);
	void startNewGame();
	void printInstructions();
	void printGoodbyeMessage();

	
public:
	void Run();

};



