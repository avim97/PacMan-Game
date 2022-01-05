#include "Menu.h"


void Menu::Activate()
{
	Print();
	SetUserChoice(eUserChoice::UNDEFINED);
	while (m_UserChoice == eUserChoice::UNDEFINED)
	{
		RequestInput();
	}
}
void Menu::Print()
{
	cout << "               Welcome to PACMAN                 " << endl;
	cout << " Please choose type in one of the option below:  " << endl;
	cout << " (1) Start a new game                            " << endl;
	cout << " (8) Present instructions and keys               " << endl;
	cout << " (9) EXIT                                        " << endl << endl;
}

void Menu::RequestInput()
{
	char userChoice;
	cin.clear();
	userChoice = _getch();
	CheckInput(userChoice); //think about tranferring to exception class later
}

void Menu::CheckInput(const char choice)
{

	switch (choice)
	{
	case static_cast<char>(eUserChoice::NewGame):
		SetUserChoice(eUserChoice::NewGame);
		break;

	case static_cast<char>(eUserChoice::Instructions):
		SetUserChoice(eUserChoice::Instructions);
		break;

	case static_cast<char>(eUserChoice::Exit):
		SetUserChoice(eUserChoice::Exit);
		break;

	default:
		SetUserChoice(eUserChoice::UNDEFINED);
		cout << " Invalid Choice, please try again!" << endl;
		break;
	}
}









