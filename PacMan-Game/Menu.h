#pragma once
#include "eUserChoice.h"
#include <stdlib.h>
#include "io_utils.h"
#include <conio.h>
#include <iostream>
using namespace std;

class Menu {
private:
	char userInput;


public:
	void printMenu();
	char requestInput();
	
	eUserChoice checkInput(const char choice);

};
