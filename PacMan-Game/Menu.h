#pragma once
#include "eUserChoice.h"
#include "io_utils.h"


using namespace std;

class Menu {
private:
	eUserChoice userChoice;


public:
	void printMenu();
	void setInput();
	eUserChoice checkInput(const char choice);

};
