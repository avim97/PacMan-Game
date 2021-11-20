#pragma once
#include "GameController.h"
#include "eUserChoice.h"
#include <stdlib.h>


class Menu {
private:
	char userInput;


public:

	void printLogo(const int logo);
	void menuPrint();
	char requestInput();
	void checkInput(const char choice);
	void startGame();
	void gameDirectionsPrint();
	void colorChoice();

};
