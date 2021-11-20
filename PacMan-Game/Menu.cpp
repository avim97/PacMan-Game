#include "Menu.h"

void Menu::menuPrint()
{
	printLogo(1);
	printLogo(2);
	cout << "         Welcome to PACMAN" << endl;
	cout << " please choose one of the option below: " << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
	

}

void Menu::requestInput()
{
}

void Menu::checkInput()
{
}

void Menu::startGame()
{
}

void Menu::gameDirectionsPrint()
{
}

void Menu::colorChoice()
{
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

)" << "\033[37m" << endl ;
		break;

	}



}




