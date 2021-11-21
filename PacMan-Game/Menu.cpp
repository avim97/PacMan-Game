#include "Menu.h"



void Menu::printMenu()
{
	cout << "               Welcome to PACMAN                 " << endl;
	cout << " Please choose type in one of the option below:  " << endl;
	cout << " (1) Start a new game                            " << endl;
	cout << " (8) Present instructions and keys               " << endl;
	cout << " (9) EXIT                                        " << endl;
	do {
		setInput();
	} while (userChoice != eUserChoice::Exit);
}

void Menu::setInput()
{
	cout << " Please choose:" << endl;
	checkInput(_getch());
}

eUserChoice Menu::checkInput(const char choice)
{
	eUserChoice userChoice;

	switch (choice)
	{
	case (char)eUserChoice::NewGame:
		userChoice = eUserChoice::NewGame;
		break;

	case (char)eUserChoice::Instructions:
		userChoice = eUserChoice::Instructions;
		break;

	case (char)eUserChoice::Exit:
		userChoice = eUserChoice::Exit;
		break;

	default:
		userChoice = eUserChoice::UNDEFINED;
		cout << " Invalid Choice, please try again!" << endl;
		break;
	}

	return userChoice;
}









