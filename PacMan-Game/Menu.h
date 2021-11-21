#pragma once
#include "eUserChoice.h"
#include "io_utils.h"


using namespace std;

class Menu {
private:
	eUserChoice userChoice;


public:
	Menu() : userChoice(eUserChoice::UNDEFINED) { printMenu(); };
	void printMenu();
	void requestInput();
	void checkInput(const char choice);
	eUserChoice getUserChoice() { return userChoice; };
	void setUserChoice(eUserChoice choice) { userChoice = choice; };
};
