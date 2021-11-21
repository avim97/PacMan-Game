#include "GameController.h"

#include <iostream>
using std::cout;

 
void GameController::Run()
{
	

	//int userChoice;


	//cin >> userChoice;

	//switch (static_cast<eUserChoice>(userChoice))
	//{
	//case eUserChoice::NewGame:			startNewGame();				break;

	//case eUserChoice::Instructions:		printInstructions();		break;

	//case eUserChoice::Exit:	make a function here that says goodbye;		break;

	//default:	/*print wrong choice message (and show the menu again) ;*/						break;


	//}


};

void GameController::startNewGame()
{
	Game newGame;

	clrscr();

	newGame.printBoard();
	
	newGame.initView();

	while (newGame.getGameStatus() == eGameStatus::RUNNING)
	{
		newGame.PlayGame();
	}



}


void GameController::printInstructions()
{
	cout << endl;
	cout << "How do you win?" << endl;
	cout << "In order to win the Pacman needs to eat all the spreaded breadcrumbs" << endl;
	cout << "How do you lose?" << endl;
	cout << "You have 3 lives, if a ghost catches you 3 times the game will be over!" << endl;
	cout << "Keys: LEFT a or A, RIGHT d or D, UP w or W, Down x or X, STAY s or S" << endl;
	cout << endl;
}

void GameController::printLogo(int logo)
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
		cout << "\033[1m\033[34m" << "         ___            " << endl
		     << "\033[1m\033[34m" << "        |||||           " << "\033[1m\033[33m" << "       ||||||           \n"
			 << "\033[1m\033[34m" << "       | *| *|          " << "\033[1m\033[33m" << "      ||||| ||          \n"
			 << "\033[1m\033[34m" << "       |||||||          " << "\033[1m\033[33m" << "     |||||||            \n"
			 << "\033[1m\033[34m" << "      |||||||||         " << "\033[1m\033[33m" << "    |||||||      *    * \n"
		   	 << "\033[1m\033[34m" << "     |||||||||||        " << "\033[1m\033[33m" << "     |||||||            \n"
			 << "\033[1m\033[34m" << "     |_|_|_|_|_|        " << "\033[1m\033[33m" << "      ||||||||          \n"
			 << "\033[1m\033[34m" << "     | | | | | |        " << "\033[1m\033[33m" << "       ||||||           \n"


			<< "\033[37m" << endl;

		break;

	}
}

eUserChoice GameController::activateMenu()
{
	Menu menu;

}