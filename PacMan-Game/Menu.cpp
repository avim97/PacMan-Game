#include "Menu.h"


void Menu::printMenu()
{
	cout << "               Welcome to PACMAN                 " << endl;
	cout << " Please choose type in one of the option below:  " << endl;
	cout << " (1) Start a new game                            " << endl;
	cout << " (8) Present instructions and keys               " << endl;
	cout << " (9) EXIT                                        " << endl;

	 while (userChoice != eUserChoice::UNDEFINED)
	{
		requestInput();
	}
}

void Menu::requestInput()
{
	char userChoice;
	cin.clear();
	cout << " Please choose:" << endl;
	userChoice = _getch();
	checkInput(userChoice);
}

void Menu::checkInput(const char choice)
{
	//eUserChoice userChoice;

	switch (choice)
	{
	case static_cast<char>(eUserChoice::NewGame):
		setUserChoice(eUserChoice::NewGame);
		break;

	case static_cast<char>(eUserChoice::Instructions):
		setUserChoice(eUserChoice::Instructions);
		break;

	case static_cast<char>(eUserChoice::Exit):
		setUserChoice(eUserChoice::Exit);
		break;

	default:
		setUserChoice(eUserChoice::UNDEFINED);
		cout << " Invalid Choice, please try again!" << endl;
		break;
	}
}









