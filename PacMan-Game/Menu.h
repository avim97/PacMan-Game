#pragma once
#include "GameController.h"

class Menu {
private:
	char userInput;
	enum { START = '1', COLOUR = '2', KEYS = '8', EXIT = '9' };

public:

	void printLogo(const int logo);
	void menuPrint();
	void requestInput();
	void checkInput();
	void startGame();
	void gameDirectionsPrint();
	void colorChoice();

};
