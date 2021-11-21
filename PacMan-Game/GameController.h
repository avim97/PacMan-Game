#pragma once
#include "Menu.h"
#include "Game.h"



class GameController
{


private:
	
	eUserChoice activateMenu();
	void printLogo(int logo);
	void startNewGame();
	void printInstructions();
	void printGoodbyeMessage();

	
public:
	void Run();

};



