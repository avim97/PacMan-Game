#include "GameController.h"

#include <iostream>
using std::cout;


void GameController::Run()
{
	eUserChoice userChoice = eUserChoice::UNDEFINED;
	do
	{
		printLogo(GameLogo);
		userChoice = activateMenu();
		switch (userChoice)
		{
		case eUserChoice::NewGame:			startNewGame();				break;

		case eUserChoice::Instructions:		printInstructions();		break;

		default:							printGoodbyeMessage();		break;

		}

		_getch();

	} while (userChoice != eUserChoice::Exit);


};

void GameController::startNewGame()
{
	string fileName;
	Game newGame(fileName);
	char colorStyle = 0;
	clrscr();

	cout << " Please choose: " << endl << " (1) Colorful " << endl << " (2) Not Colorful " << endl;

	while (colorStyle != '1' && colorStyle != '2')
	{
		colorStyle = _getch();

		if (colorStyle == '1') 
		{
			newGame.setColorStyle(true);
		}

		else if (colorStyle == '2')
		{
			newGame.setColorStyle(false);
			newGame.setDefaultColor();
		}

		else //wrong input- not 1 or 2
		{
			cout << "Invalid choice, please choose again." << endl;
		}
	}

	clrscr();
	
	newGame.printBoard();

	//newGame.initView();

	while (newGame.getGameStatus() == eGameStatus::RUNNING)
	{
		newGame.PlayGame();
	}

}


void GameController::printInstructions()
{
	clrscr();
	cout << endl;
	cout << " How do you win?" << endl;
	cout << " In order to win the Pacman needs to eat all the spreaded breadcrumbs" << endl;
	cout << " How do you lose?" << endl;
	cout << " You have 3 lives, if a ghost catches you 3 times the game will be over!" << endl;
	cout << " Keys: LEFT a or A, RIGHT d or D, UP w or W, Down x or X, STAY s or S" << endl;
	cout << "            -------------------------------------------              " << endl;
	cout << "           Press any key to go back to the main menu..." << endl;

	while (!_kbhit()) {};
	clrscr();
}

void GameController::printLogo(int logo)
{
	switch (logo) {
	case GameLogo:
		cout << "  _ __   __ _  ___ _ __ ___   __ _ _ __  " << endl;
		Sleep(200);
		cout << " | '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ " << endl;
		Sleep(200);
		cout << " | |_) | (_| | (__| | | | | | (_| | | | |" << endl;
		Sleep(200);
		cout << " | .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|" << endl;
		Sleep(200);
		cout << " |_|                                     " << endl;

		
		cout << "         ___            " << endl
			 << "        |||||           " <<  "       ||||||           \n"
			 << "       | *| *|          " <<  "      ||||| ||          \n"
			 << "       |||||||          " <<  "     |||||||            \n"
			 << "      |||||||||         " <<  "    |||||||      *    * \n"
			 << "     |||||||||||        " <<  "     |||||||            \n"
			 << "     |_|_|_|_|_|        " <<  "      ||||||||          \n"
			 << "     | | | | | |        " <<  "       ||||||           \n"


			<< "\033[37m" << endl;

		break;

	case GoodbyeLogo:
		cout << "  _____                 _ _                _   " << endl;
		cout << " / ____|               | | |              | |  " << endl;
		cout << "| |  __  ___   ___   __| | |__  _   _  ___| |  " << endl;
		cout << "| | |_ |/ _ \\ / _ \\ / _` | '_ \\| | | |/ _ \\ |  " << endl;
		cout << "| |__| | (_) | (_) | (_| | |_) | |_| |  __/_|  " << endl;
		cout << " \\_____|\\___/ \\___/ \\__,_|_.__/ \\__, |\\___(_)   " << endl;
		cout << "                                  _/ |               " << endl;
		cout << "                                 |___/               " << endl;
		break;

	}
	




}

eUserChoice GameController::activateMenu()
{
	Menu gameMenu;
	gameMenu.printMenu();
	while (gameMenu.getUserChoice() == eUserChoice::UNDEFINED)
	{
		gameMenu.requestInput();
	}

	return gameMenu.getUserChoice();
}

void GameController::printGoodbyeMessage()
{
	clrscr();
	printLogo(GoodbyeLogo);
}