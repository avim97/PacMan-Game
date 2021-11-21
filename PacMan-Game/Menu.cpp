#include "Menu.h"

void Menu::menuPrint()
{
	printLogo(1);
	printLogo(2);
	cout << "         Welcome to PACMAN" << endl;
	cout << " please choose type in one of the option below: " << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
	
	char choice;
	do {
		
		choice = requestInput();
		checkInput(choice);
		

	} while (choice != (char)eUserChoice::Exit);


}

char Menu::requestInput()
{
	cout << "Please type in your choice now:" << endl;
	return _getch();
}

void Menu::checkInput(const char choice)
{
	switch ((char)choice)
	{
	case (char)eUserChoice::NewGame:
		startGame();
		break;

	case (char)eUserChoice::Color:
		system("CLS");
		colorChoice();
		
		break;

	case (char)eUserChoice::Instructions:
		system("CLS");
		gameDirectionsPrint();

		break;

	case (char)eUserChoice::Exit:
		cout << "\nThanks and goodbye!\n";
		break;

	default:
		cout << "\nIllegal choice, please try again." << endl;
		break;
	}
}

void Menu::startGame()
{
	system("CLS");
	GameController game;
	game.startNewGame();
}

void Menu::gameDirectionsPrint()
{
	std::cout << std::endl;
	std::cout << "How do you win?" << std::endl;
	std::cout << "In order to win the Pacman needs to eat all the spreaded breadcrumbs" << std::endl;
	std::cout << "How do you lose?" << std::endl;
	std::cout << "You have 3 lives, if a ghost catches you 3 times the game will be over!" << std::endl;
	std::cout << "Keys: LEFT a or A, RIGHT d or D, UP w or W, Down x or X, STAY s or S" << std::endl;
	std::cout << std::endl;
}

void Menu::colorChoice()
{

	//????
}

void Menu::printLogo(const int logo)
{
	switch (logo) {
	case 1:
		cout << "  _ __   __ _  ___ _ __ ___   __ _ _ __  " << endl;
		Sleep(300);
		cout << " | '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ " << endl;
		Sleep(300);
		cout << " | |_) | (_| | (__| | | | | | (_| | | | |" << endl;
		Sleep(300);
		cout << " | .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|" << endl;
		Sleep(300);
		cout << " |_|                                     " << endl;
		break;

	case 2:
	
		cout << "\033[1m\033[31m" << R"(
  ▒▒▒▒▒
 ▒─▄▒─▄▒
 ▒▒▒▒▒▒▒
 ▒▒▒▒▒▒▒
 ▒ ▒ ▒ ▒   
)"
<< "\033[1m\033[33m" << R"(
   ▄████▄
  ███▄█▀
 ▐████  █  █
  █████▄
   ▀████▀ 

)" << "\033[37m" << endl;
		break;

	}



}




