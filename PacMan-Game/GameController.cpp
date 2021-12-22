#include "GameController.h"

#include <iostream>
using std::cout;


void GameController::Run()
{

	eUserChoice userChoice = eUserChoice::UNDEFINED;
	bool replay = true;
	while (userChoice != eUserChoice::Exit && replay)
	{
		replay = false;
		printLogo(GameLogo);

		userChoice = activateMenu();

		switch (userChoice)
		{
		case eUserChoice::NewGame:			if (ChooseScreenOrVector(userChoice)) { replay = true; } break;

		case eUserChoice::Instructions:		printInstructions();		break;

		default:							printGoodbyeMessage();		break;

		}

		//_getch();

	}


};


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
	clrscr();

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
			<< "        |||||           " << "       ||||||           \n"
			<< "       | *| *|          " << "      ||||| ||          \n"
			<< "       |||||||          " << "     |||||||            \n"
			<< "      |||||||||         " << "    |||||||      *    * \n"
			<< "     |||||||||||        " << "     |||||||            \n"
			<< "     |_|_|_|_|_|        " << "      ||||||||          \n"
			<< "     | | | | | |        " << "       ||||||           \n"


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

bool GameController::ChooseScreenOrVector(eUserChoice& userChoice) // add later user choice from the user as a reference to functions argument
{

	vector<string> filePaths;
	eGameStatus KeyPressed;
	if (!FileActions::DirFileList(filePaths))
	{
		userChoice = eUserChoice::UNDEFINED;
		return true;
	}



	else {

		clrscr();
		GameMode mode = GameModeChoice();
		clrscr();

		cout << "Please choose one of the following:" << endl;
		cout << "(1) Load my own file by name" << endl;
		cout << "(2) Load all existing files " << endl;
		char choice = _getch();
		switch (choice)
		{

		case SpedificFile:
		{
			string fileName;
			bool color = NULL;

			if (FileActions::SpecificFileNameSearch(filePaths, fileName))
			{
				Game newGame(fileName, mode);
				if (color == NULL)
					color = ApplyUserColorsChoiceToGame(newGame);
				if (!color)
					newGame.SetDefaultColor();
				clrscr();
				GameRun(fileName, mode, newGame);

				if (newGame.getGameStatus() == eGameStatus::LOST)
				{
					Game::userLost(color);
					return true;
				}
			}
			else
			{
				return true;
			}
				
			break;
		}
		case  AllFiles:
			int lives = 3, score = 0;
			bool color = NULL;
			for (string& fileName = filePaths[0]; !filePaths.empty() && lives > 0;)
			{
				Game newGame(fileName, mode, lives, score);
				filePaths.erase(filePaths.begin());
				if (color == NULL)
					color = ApplyUserColorsChoiceToGame(newGame);
				if (!color)
					newGame.SetDefaultColor();

				clrscr();
				newGame.printBoard();
				GameRun(fileName, mode,newGame);
				if (newGame.getGameStatus() == eGameStatus::LOST)
				{
					Game::userLost(color);
					return true;
				}
				if (newGame.getGameStatus() == eGameStatus::NEXT_BOARD)
				{
					if (filePaths.empty())
					{
						cout << "No other board found, press any key to exit " << endl;
						while (!_kbhit());
						clrscr();
						return false;
					}
				}
				if (newGame.getGameStatus() == eGameStatus::EXIT)
				{
					return true;
				}

				lives = newGame.getPacman().GetCurrentLives();
				score = newGame.GetTotalScore();
			}
			Game::userWon(color);
			return false;
		}
	}
}

bool GameController::ApplyUserColorsChoiceToGame(Game& game)
{
	char colorStyle = 0;
	clrscr();

	cout << " Please choose: " << endl << " (1) Colorful " << endl << " (2) Not Colorful " << endl;

	while (colorStyle != '1' && colorStyle != '2')
	{
		colorStyle = _getch();

		if (colorStyle == '1')
		{
			return true;
		}

		else if (colorStyle == '2')
		{
			//game.setDefaultColor();
			return false;

		}

		else //wrong input
		{
			cout << "Invalid choice, please choose again." << endl;
		}
	}

}
void GameController::GameRun(string& fileName, GameMode mode, Game& game)
{
	eGameStatus KeyPressed;

	clrscr();
	game.printBoard();
	while (game.getGameStatus() == eGameStatus::RUNNING)
	{
		game.PlayGame();
		KeyPressed = game.getGameStatus();
		if (KeyPressed == eGameStatus::ESC_PRESSED)
		{
			game.SetGameStatus(eGameStatus::RUNNING);
			PauseGame(game, true);
		}
	}

}

void GameController::PauseGame(Game& currentGame, bool isSingleGame)
{

	clrscr();
	printLogo(GameLogo);

	cout << "  The game Paused, please choose:" << endl;
	cout << "(1)   Back to main menu " << endl;
	if (!isSingleGame)
	{
		cout << "(2)   Play next board " << endl;
	}
	;
	cout << "(Esc) Continue Playing " << endl;


	bool choice = false;
	while (!choice)
	{
		char userchoice = _getch();
		switch (userchoice) {
		case '1':
			currentGame.SetGameStatus(eGameStatus::EXIT);
			clrscr();
			choice = true;
			break;

		case '2':
			currentGame.SetGameStatus(eGameStatus::NEXT_BOARD);
			clrscr();
			choice = true;
			break;

		case 27:
			clrscr();
			currentGame.printBoard(true);
			choice = true;
			break;

		default:
			cout << "Wrong choice, press any key and try again." << endl;
			break;
		}
	}



}
GameMode GameController::GameModeChoice()
{
	clrscr();
	cout << "Please choose game difficulty:" << endl;
	cout << "(1) Novice" << endl;
	cout << "(2) Good" << endl;
	cout << "(3) Best" << endl;
	bool validchoice = false;
	while (!validchoice)
	{
		char choice;
		choice = _getch();
		switch (choice)
		{
		case static_cast<char>(GameMode::NOVICE) + '0':
			return GameMode::NOVICE;
			validchoice = true;
			break;

		case static_cast<char>(GameMode::GOOD) + '0':
			return GameMode::GOOD;
			validchoice = true;
			break;

		case static_cast<char>(GameMode::BEST) + '0':
			return GameMode::BEST;
			validchoice = true;
			break;
		default:
			cout << "wrong choice, please try again.";
			break;
		}
	}



}